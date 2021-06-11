#include "pch.h"
#include "fmod_sound_analysis_test.h"

#include <conio.h>
#include <iomanip>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "base/r2_FrameManager.h"
#include "base/r2_eTestResult.h"
#include "utility/r2_fmod_util.h"

//
// # Ref
// 1. https://qa.fmod.com/t/problem-getting-spectrum-in-newer-fmod-versions/11624
//

namespace fmod_sound_analysis_test
{
	r2::iTest::TitleFunc Frequency::GetTitleFunction() const
	{
		return []()->const char* { return "Sound Analysis - Frequency"; };
	}
	r2::iTest::DoFunc Frequency::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
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
				r2::FrameManager frame_manager( 30u );
				frame_manager.Reset();

				bool process = true;
				while( process )
				{
					if( _kbhit() )
					{
						switch( _getch() )
						{
						case 27: // ESC
							process = false;
							break;
						}
					}

					if( frame_manager.Update() )
					{
						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						system( "cls" );

						std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

						std::cout << r2::split;

						{
							const auto backup_precision = std::cout.precision();

							std::setprecision( 4 );

							FMOD_DSP_PARAMETER_FFT* fft = nullptr;
							unsigned int binlength;
							fsm_dsp_fft->getParameterData( FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, 0 );
							for( int channel = 0; /*fft->numchannels*/ 1 > channel; channel++ )
							{
								for( int bin = 0; /*fft->length*/ 10 > bin; ++bin )
								{
									float freqVal = fft->spectrum[channel][bin];
									std::cout << freqVal << r2::linefeed;
								}
							}

							std::setprecision( backup_precision );
						}

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );

						std::cout << r2::split;
					}
				}
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

			return r2::eTestResult::RunTest_Without_Pause;


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