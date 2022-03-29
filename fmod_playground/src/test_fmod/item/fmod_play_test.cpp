#include "pch.h"
#include "fmod_play_test.h"

#include <algorithm>
#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_Assert.h"
#include "r2/r2_FrameManager.h"
#include "base/r2_eTestResult.h"
#include "utility/r2_fmod_util.h"

namespace fmod_play_test
{
	r2::iTest::TitleFunc PlaySound::GetTitleFunction() const
	{
		return []()->const char* { return "Play Sound"; };
	}
	r2::iTest::DoFunc PlaySound::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
			
			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
				// Load
				fmod_result = fmod_system->createSound( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// Setup
				fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF );    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
				r2_fmod_util::ERROR_CHECK( fmod_result );	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
			}

			//
			// Update Loop
			//
			{
				FMOD::Channel* fmod_channel = nullptr;
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
							fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;

						case '2':
							if( fmod_channel )
							{
								fmod_channel->stop();
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
						std::cout << "[1] " << "Play" << r2::linefeed;
						std::cout << "[2] " << "Stop" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
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



	r2::iTest::TitleFunc PlayStream::GetTitleFunction() const
	{
		return []()->const char* { return "Play Stream"; };
	}
	r2::iTest::DoFunc PlayStream::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			FMOD::Sound* fmod_current_sound = nullptr;
			{
				// Load
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &fmod_sound );
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
			// Update Loop
			//
			{
				FMOD::Channel* fmod_channel = nullptr;
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
							fmod_result = fmod_system->playSound( fmod_current_sound, 0, false, &fmod_channel );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;

						case '2':
							if( fmod_channel )
							{
								fmod_channel->stop();
							}
							break;

						case '3':
							{
								FMOD_MODE fmod_mode = 0u;
								fmod_result = fmod_sound->getMode( &fmod_mode );
								r2_fmod_util::ERROR_CHECK( fmod_result );

								fmod_result = fmod_sound->setMode( FMOD_LOOP_NORMAL & fmod_mode ? FMOD_LOOP_OFF : FMOD_LOOP_NORMAL );
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
						std::cout << "[1] " << "Play" << r2::linefeed;
						std::cout << "[2] " << "Stop" << r2::linefeed;
						std::cout << "[3] " << "Loop ON/OFF" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
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



	FMOD_RESULT F_CALLBACK TempCallback( FMOD_CHANNELCONTROL* /*channelcontrol*/, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE /*callbacktype*/, void* /*commanddata1*/, void* /*commanddata2*/ )
	{
		std::cout << "Call - TempCallback" << r2::linefeed;

		if( controltype == FMOD_CHANNELCONTROL_TYPE::FMOD_CHANNELCONTROL_CHANNEL )
		{
			//FMOD::Channel *channel = ( FMOD::Channel * )channelcontrol;
			// Channel specific functions here...
		}
		else
		{
			//FMOD::ChannelGroup *group = ( FMOD::ChannelGroup * )channelcontrol;
			// ChannelGroup specific functions here...
		}

		system( "pause" );

		return FMOD_RESULT::FMOD_OK;
	}
	r2::iTest::TitleFunc PlayAndCallback::GetTitleFunction() const
	{
		return []()->const char* { return "Play And Callback"; };
	}
	r2::iTest::DoFunc PlayAndCallback::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Update Loop
			//
			{
				FMOD::Channel* fmod_channel = nullptr;
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
							fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							fmod_channel->setCallback( TempCallback );

							break;

						case '2':
							if( fmod_channel )
							{
								fmod_channel->stop();
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
						std::cout << "[1] " << "Play" << r2::linefeed;
						std::cout << "[2] " << "Stop" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
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



	r2::iTest::TitleFunc VolumeControl::GetTitleFunction() const
	{
		return []()->const char* { return "Volume Control"; };
	}
	r2::iTest::DoFunc VolumeControl::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
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

				float volume = 1.0f;

				bool process = true;
				while( process )
				{
					if( _kbhit() )
					{
						switch( _getch() )
						{
						case '1':
							volume += 0.1f;
							volume = std::min( 1.0f, volume );

							fmod_result = fmod_channel->setVolume( volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;

						case '2':
							volume -= 0.1f;
							volume = std::max( 0.0f, volume );

							fmod_result = fmod_channel->setVolume( volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
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
						std::cout << "[1] " << "Volume Up" << r2::linefeed;
						std::cout << "[2] " << "Volume Down" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
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



	r2::iTest::TitleFunc PositionControl::GetTitleFunction() const
	{
		return []()->const char* { return "Position Control"; };
	}
	r2::iTest::DoFunc PositionControl::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
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
							fmod_result = fmod_channel->setPosition( 0u, FMOD_TIMEUNIT_MS );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						case '2':
							fmod_result = fmod_channel->setPosition( 10000u, FMOD_TIMEUNIT_MS );
							r2_fmod_util::ERROR_CHECK( fmod_result );
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
						std::cout << "[1] " << "Move First" << r2::linefeed;
						std::cout << "[2] " << "Move Half" << r2::linefeed;

						std::cout << r2::split;

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
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
}