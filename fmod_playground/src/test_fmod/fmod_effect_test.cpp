#include "pch.h"
#include "fmod_effect_test.h"

#include <conio.h>
#include <numeric>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "base/r2_Assert.h"
#include "base/r2_FrameManager.h"
#include "base/r2_eTestResult.h"
#include "utility/r2_fmod_util.h"

namespace fmod_effect_test
{
	r2::iTest::TitleFunc Echo::GetTitleFunction() const
	{
		return []()->const char* { return "Effect - Echo"; };
	}
	r2::iTest::DoFunc Echo::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Preload Audio + Setup
			//
			FMOD::Sound* fmod_sound = nullptr;
			FMOD::Sound* fmod_current_sound = nullptr;
			{
				// Preload Audio
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				int sub_sound_count = 0;
				fmod_result = fmod_sound->getNumSubSounds( &sub_sound_count );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				if( 0 < sub_sound_count )
				{
					fmod_sound->getSubSound( 0, &fmod_current_sound );
					r2_fmod_util::ERROR_CHECK( fmod_result );
				}
				else
				{
					fmod_current_sound = fmod_sound;
				}
			}

			//
			// DSP
			//
			FMOD::DSP* fsm_dsp_echo = nullptr;
			{ 
				fmod_result = fmod_system->createDSPByType( FMOD_DSP_TYPE_ECHO, &fsm_dsp_echo );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fsm_dsp_echo->setBypass( false );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Play Sound + Apply Effect
			//
			FMOD::Channel* fmod_channel = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_current_sound, 0, false, &fmod_channel );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_channel->addDSP( 0, fsm_dsp_echo );
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
						case '1':
						{
							bool is_by_pass = false;
							fmod_result = fsm_dsp_echo->getBypass( &is_by_pass );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_result = fsm_dsp_echo->setBypass( !is_by_pass );
							r2_fmod_util::ERROR_CHECK( fmod_result );
						}
						break;

						case 32:
						{
							bool bPaused = false;
							fmod_result = fmod_channel->getPaused( &bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_result = fmod_channel->setPaused( !bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );
						}
						break;

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
						std::cout << "[1] Effect ON/OFF" << r2::linefeed;
						std::cout << "[SPACE] : Pause" << r2::linefeed;

						std::cout << r2::split;

						bool is_by_pass = false;
						fmod_result = fsm_dsp_echo->getBypass( &is_by_pass );
						r2_fmod_util::ERROR_CHECK( fmod_result );
						std::cout << "Echo " << ( is_by_pass ? "OFF" : "ON" ) << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );
						r2_fmod_util::PrintChannelDSPClock( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
			}

			//
			// DSP release
			//
			{
				fmod_channel->removeDSP( fsm_dsp_echo );

				fmod_result = fsm_dsp_echo->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Audio Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}



	r2::iTest::TitleFunc Fade::GetTitleFunction() const
	{
		return []()->const char* { return "Effect - Fade"; };
	}
	r2::iTest::DoFunc Fade::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Preload Audio + Setup
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
				// Create
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Play Sound
			//
			FMOD::Channel* fmod_channel = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel );
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
						case '1':
						{
							int sample_rate = 0u;
							fmod_system->getSoftwareFormat( &sample_rate, nullptr, nullptr );

							unsigned long long dspclock = 0u;
							fmod_result = fmod_channel->getDSPClock( &dspclock, nullptr );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_channel->addFadePoint( dspclock, 1.f );
							fmod_channel->addFadePoint( dspclock + ( sample_rate * 3 ), 0.f );
						}
						break;
						case '2':
						{
							int sample_rate = 0u;
							fmod_system->getSoftwareFormat( &sample_rate, nullptr, nullptr );

							unsigned long long dspclock = 0u;
							fmod_result = fmod_channel->getDSPClock( &dspclock, nullptr );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_channel->addFadePoint( dspclock, 0.f );
							fmod_channel->addFadePoint( dspclock + ( sample_rate * 3 ), 1.f );
						}
						break;

						case 32:
						{
							bool bPaused = false;
							fmod_result = fmod_channel->getPaused( &bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_result = fmod_channel->setPaused( !bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );
						}
						break;

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
						std::cout << "[1] Fade Out" << r2::linefeed;
						std::cout << "[2] Fade In" << r2::linefeed;
						std::cout << "[SPACE] : Pause" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );
						r2_fmod_util::PrintChannelDSPClock( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;

						std::cout << "Note : Fade Point Works Only Once" << r2::linefeed;

						std::cout << r2::split;
					}
				}
			}

			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}



	r2::iTest::TitleFunc FadeStartFadeEnd::GetTitleFunction() const
	{
		return []()->const char* { return "Effect - Fade Start and Fade End"; };
	}
	r2::iTest::DoFunc FadeStartFadeEnd::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			r2_fmod_util::CreateSystem( &fmod_system );

			FMOD::Sound* fmod_sound = nullptr;
			r2_fmod_util::ERROR_CHECK( fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &fmod_sound ) );

			{
				r2::FrameManager frame_manager( 30u );
				frame_manager.Reset();

				FMOD::Channel* fmod_channel = nullptr;

				unsigned int n = 0;
				unsigned long long* d = 0ll;
				float* v = nullptr;

				bool process = true;
				while( process )
				{
					if( _kbhit() )
					{
						switch( _getch() )
						{
						case 32:
						{
							if( fmod_channel )
							{			
								fmod_channel->stop();
							}

							r2_fmod_util::ERROR_CHECK( fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );

							unsigned long long dspclock = 0u;
							r2_fmod_util::ERROR_CHECK( fmod_channel->getDSPClock( nullptr, &dspclock ) );

							int sample_rate = 0u;
							r2_fmod_util::ERROR_CHECK( fmod_system->getSoftwareFormat( &sample_rate, nullptr, nullptr ) );

							// Head
							{
								fmod_channel->addFadePoint( dspclock, 0.f );
								fmod_channel->addFadePoint( dspclock + ( sample_rate * 5.f ), 1.f );
							}

							// Tail
							{
								unsigned int lenms = 0;
								r2_fmod_util::ERROR_CHECK( fmod_sound->getLength( &lenms, FMOD_TIMEUNIT_MS ) );


								unsigned int ms = 0;
								r2_fmod_util::ERROR_CHECK( fmod_channel->getPosition( &ms, FMOD_TIMEUNIT_MS ) );

								const auto remain_sec = ( lenms - ms ) * 0.001f;
								const auto target_sec = remain_sec - 5.f;

								fmod_channel->addFadePoint( dspclock + ( sample_rate * target_sec ), 1.f );
								fmod_channel->addFadePoint( dspclock + ( sample_rate * remain_sec ), 0.f );
							}
						}
						break;

						case 27: // ESC
							process = false;
							break;
						}
					}

					if( frame_manager.Update() )
					{
						r2_fmod_util::ERROR_CHECK( fmod_system->update() );

						system( "cls" );

						std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
						std::cout << "[SPACE] Play" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelDSPClock( fmod_channel );

						std::cout << r2::split;

						if( fmod_channel )
						{
							fmod_channel->getFadePoints( &n, d, v );
						}
						std::cout << "P : " << n << r2::linefeed;

						std::cout << r2::split;
					}
				}
			}

			{
				r2_fmod_util::ERROR_CHECK( fmod_sound->release() );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}




	r2::iTest::TitleFunc PitchControl::GetTitleFunction() const
	{
		return []()->const char* { return "Effect - Pitch Control"; };
	}
	r2::iTest::DoFunc PitchControl::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			FMOD::Sound* fmod_sound = nullptr;
			r2_fmod_util::ERROR_CHECK( fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound ) );

			FMOD::Channel* fmod_channel = nullptr;
			r2_fmod_util::ERROR_CHECK( fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );

			//
			// Update Loop
			//
			{
				const float change_amount = 0.1f;

				r2::FrameManager frame_manager( 30u );
				frame_manager.Reset();

				bool process = true;
				while( process )
				{
					if( _kbhit() )
					{
						switch( _getch() )
						{
						case '1':
						{
							float pitch = 0.f;
							r2_fmod_util::ERROR_CHECK( fmod_channel->getPitch( &pitch ) );

							pitch += change_amount;

							r2_fmod_util::ERROR_CHECK( fmod_channel->setPitch( pitch ) );
						}
						break;
						case '2':
						{
							float pitch = 0.f;
							r2_fmod_util::ERROR_CHECK( fmod_channel->getPitch( &pitch ) );

							pitch -= change_amount;
							if( pitch < 0.f )
							{
								pitch = 0.f;
							}

							r2_fmod_util::ERROR_CHECK( fmod_channel->setPitch( pitch ) );
						}
						break;

						case 32:
						{
							bool bPaused = false;
							fmod_result = fmod_channel->getPaused( &bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_result = fmod_channel->setPaused( !bPaused );
							r2_fmod_util::ERROR_CHECK( fmod_result );
						}
						break;

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
						std::cout << "[1/2] Pitch Up/Down" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintChannelPitchInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );
						r2_fmod_util::PrintChannelDSPClock( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
			}

			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}
}