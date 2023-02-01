#include "pch.h"
#include "fmod_sound_analysis_test.h"

#include <conio.h>
#include <iomanip>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_FrameManager.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"
#include "utility/r2_fmod_util.h"

//
// # Ref
// 1. https://qa.fmod.com/t/problem-getting-spectrum-in-newer-fmod-versions/11624
// 2. https://qa.fmod.com/t/how-to-get-spectrum-data-including-amplitudes-with-fmod-dsp-parameter-fft/12183
// 3. https://katyscode.wordpress.com/2013/01/16/cutting-your-teeth-on-fmod-part-4-frequency-analysis-graphic-equalizer-beat-detection-and-bpm-estimation/
// 4. https://github.com/AnttiVainio/FMOD-music-visualizer
//

namespace fmod_sound_analysis_test
{
	r2cm::iItem::TitleFunctionT Frequency::GetTitleFunction() const
	{
		return []()->const char* { return "Sound Analysis - Frequency"; };
	}
	r2cm::iItem::DoFunctionT Frequency::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			FMOD::Sound* fmod_sound = nullptr;
			{
				r2_fmod_util::ERROR_CHECK( fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound ) );
			}

			//
			// Create DSP
			//
			FMOD::DSP* fsm_dsp_fft = nullptr;
			{ 
				r2_fmod_util::ERROR_CHECK( fmod_system->createDSPByType( FMOD_DSP_TYPE_FFT, &fsm_dsp_fft ) );

				r2_fmod_util::ERROR_CHECK( fsm_dsp_fft->setParameterInt( FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_TRIANGLE ) );

				int windowsize = 256;
				r2_fmod_util::ERROR_CHECK( fsm_dsp_fft->setParameterInt( FMOD_DSP_FFT_WINDOWSIZE, windowsize ) );
			}

			//
			// Play Sound
			//
			FMOD::Channel* fmod_channel = nullptr;
			{
				r2_fmod_util::ERROR_CHECK( fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );
			}

			//
			// Apply DSP
			//
			{
				fmod_result = fmod_channel->addDSP( 0, fsm_dsp_fft );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Update Loop
			//
			{
				r2::FrameManager frame_manager( 10u );
				frame_manager.Reset();

				const auto pivot_point = r2cm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{

					if( frame_manager.Update() )
					{
						r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_point );

						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						{
							FMOD_DSP_PARAMETER_FFT* fft = nullptr;

							fsm_dsp_fft->getParameterData( FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, 0 );
							for( int channel = 0; fft->numchannels > channel; channel++ )
							{
								for( int bin = 0; fft->length > bin; ++bin )
								{
									float freqVal = fft->spectrum[channel][bin];
									std::cout << static_cast<int>( freqVal * 10000 ) << r2cm::tab;

									if( 0 == ( bin + 1 ) % 14 )
									{
										std::cout << r2cm::linefeed;
									}
								}

								std::cout << r2cm::linefeed2;
							}
						}

						std::cout << r2cm::linefeed;

						{
							const auto backup_precision = std::cout.precision();

							float dfft = 0.f;

							fsm_dsp_fft->getParameterFloat( FMOD_DSP_FFT_DOMINANT_FREQ, &dfft, 0, 0 );
							std::cout << dfft << r2cm::linefeed;
						}

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelTimeInfo( fmod_channel );

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
					}

				} while( 27 != input );
			}

			//
			// DSP release
			//
			{
				r2_fmod_util::ERROR_CHECK( fmod_channel->removeDSP( fsm_dsp_fft ) );

				r2_fmod_util::ERROR_CHECK( fsm_dsp_fft->release() );
			}

			//
			// Audio Release
			//
			{
				r2_fmod_util::ERROR_CHECK( fmod_sound->release() );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;


			//{
			//	fmod::system     *system;
			//	fmod::sound      *sound1; 
			//	fmod::channel    *channel = 0; 
			//	fmod::channelgroup *mastergroup; 
			//	fmod::channelcontrol *control; 
			//	fmod::dsp         *mydsp, *dsphead, *dspchannelmixer; 
			//	fmod::dspconnection *conection; 
			//	fmod_result       result; 
			//	unsigned int      version; 
			//	result = fmod::system_create( &system ); 
			//	result = system->getversion( &version );  
			//	result = system->init( 32, fmod_init_normal, null ); 
			//	result = system->createsound( "mysong.mp3", fmod_default, 0, &sound1 ); 
			//	result = sound1->setmode( fmod_loop_normal ); 
			//	result = system->playsound( sound1, 0, true, &channel );  

			//	/* create dsp effect. */ 
			//	result = system->getmasterchannelgroup( &mastergroup ); 
			//	result = system->createdspbytype( fmod_dsp_type_fft, &mydsp );  
			//	result = system->getmasterchannelgroup( &mastergroup ); 
			//	result = mastergroup->adddsp( 0, mydsp );   
			//	result = mydsp->setbypass( true ); 
			//	result = mydsp->setactive( true );  
			//	char s[256]; unsigned int len; 
			//	float freq[32];  float fft = 0; 
			//	std::vector<float> fftheights; 
			//	float m_spectrum_data[fft_num_bins];  
			//	while( 1 ) { 
			//		//program loop  
			//		unsigned int ms = 0; 
			//		unsigned int lenms = 0; 
			//		bool         playing = 0; 
			//		bool         paused = 0; 
			//		int          channelsplaying = 0;   
			//		if (channel)   
			//		{     
			//			fmod::sound *currentsound = 0;    
			//			result = channel->setpaused(false);     
			//			result = channel->setmute(false);    
			//			result = channel->isplaying(&playing);    
			//			result = channel->getpaused(&paused);     
			//			result = channel->setvolume(0.5);     
			//			result = channel->getposition(&ms, fmod_timeunit_ms);     
			//			channel->getcurrentsound(&currentsound);     
			//			if (currentsound)     
			//			{      
			//				result = currentsound->getlength(&lenms, fmod_timeunit_ms);       
			//			}   
			//		}    
			//		
			//		system->getchannelsplaying(&channelsplaying);     
			//		fmod_dsp_parameter_fft *fftparameter;   
			//		float val;   char s[256];   
			//		unsigned int len;   
			//		float *data = 0;   
			//		float freq[32];   
			//		int rate, chan, nyquist;  
			//		int windowsize = 1024;    
			//		result = system->getsoftwareformat(&rate, 0, 0);     
			//		result = mydsp->setparameterint(fmod_dsp_fft_windowtype, fmod_dsp_fft_window_triangle);    
			//		result = mydsp->setparameterint(fmod_dsp_fft_windowsize, windowsize);    
			//		result = mydsp->getparameterfloat(fmod_dsp_fft_dominant_freq, &val, 0, 0);    
			//		result = mydsp->getparameterdata(fmod_dsp_fft_spectrumdata, (void **)&fftparameter, &len, s, 256);    
			//		nyquist = windowsize / 2;    
			//		(chan = 0; chan < 2; chan++)   
			//		{     
			//			float average = 0.0f;     
			//			float power = 0.0f;      
			//			(int = 0; < nyquist - 1; ++i)     
			//			{       
			//				float hz = * (rate * 0.5f) / (nyquist - 1);       
			//				int index = + (16384 * chan);        
			//				if (fftparameter->spectrum[chan][i] > 0.0001f) 
			//					// arbitrary cutoff filter out noise       
			//				{         
			//					average += data[index] * hz;         
			//					power += data[index];       
			//				}     
			//			}      
			//			if (power > 0.001f)    
			//			{       
			//				freq[chan] = average / power;     
			//			}     
			//			else     
			//			{       
			//				freq[chan] = 0;     
			//			}   
			//		}   
			//		
			//		printf("\ndom freq = %d : %.02f %.02f\n", (int)val, freq[0], freq[1]); }
			//}
		};
	}
}