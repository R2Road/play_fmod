#include "pch.h"
#include "fmod_play_test.h"

#include <algorithm>
#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_FrameManager.h"
#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"
#include "utility/r2_fmod_util.h"

namespace fmod_play_test
{
	r2cm::iItem::TitleFunctionT PlaySound_Basic::GetTitleFunction() const
	{
		return []()->const char* { return "Play Sound : Basic"; };
	}
	r2cm::iItem::DoFunctionT PlaySound_Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			//
			// System
			//
			DECLARATION_SUB( FMOD::System* fmod_system = nullptr );
			DECLARATION_SUB( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );
			PROCESS_SUB( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			//
			// Sound : Create
			//
			DECLARATION_MAIN( FMOD::Sound* fmod_sound = nullptr );

			PROCESS_MAIN( fmod_result = fmod_system->createSound( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound ) );
			r2_fmod_util::ERROR_CHECK( fmod_result );

			PROCESS_MAIN( fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF ) );    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
			r2_fmod_util::ERROR_CHECK( fmod_result );	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */

			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::Channel* fmod_channel = nullptr );
			{
				PROCESS_MAIN( fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2cm::linefeed2;

				std::cout << "[Any Key] " << "End" << r2cm::linefeed;
				_getch();

				std::cout << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_channel->stop() );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( fmod_result = fmod_sound->release() );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2cm::linefeed;

				PROCESS_SUB( r2_fmod_util::ReleaseSystem( &fmod_system ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PlaySound_Demo::GetTitleFunction() const
	{
		return []()->const char* { return "Play Sound : Demo"; };
	}
	r2cm::iItem::DoFunctionT PlaySound_Demo::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			//
			// System
			//
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

			std::cout << r2cm::split;

			{
				std::cout << "[1] " << "Play" << r2cm::linefeed;
				std::cout << "[2] " << "Stop" << r2cm::linefeed;
				std::cout << "[3] " << "Loop ON/OFF" << r2cm::linefeed2;

				std::cout << r2cm::tab << "createSound 로 만들어진 Sound 는 Play 이후에는 Loop 속성이 변경되지 않는다." << r2cm::linefeed;
				std::cout << r2cm::tab << "createStream 으로 만들어진 Sound 는 Loop 속성이 즉각 반영된다." << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			//
			// Update Loop
			//
			{
				FMOD::Channel* fmod_channel = nullptr;
				r2::FrameManager frame_manager( 30u );
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

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2cm::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
						switch( input )
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
						case '3':
							{
								FMOD_MODE fmod_mode = 0u;
								fmod_result = fmod_sound->getMode( &fmod_mode );
								r2_fmod_util::ERROR_CHECK( fmod_result );

								fmod_result = fmod_sound->setMode( FMOD_LOOP_NORMAL & fmod_mode ? FMOD_LOOP_OFF : FMOD_LOOP_NORMAL );
								r2_fmod_util::ERROR_CHECK( fmod_result );
							}
							break;
						}
					}

				} while( 27 != input );
			}

			//
			// Sound : Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// System : Release
			//
			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;
		};
	}



	r2cm::iItem::TitleFunctionT PlayStream_Basic::GetTitleFunction() const
	{
		return []()->const char* { return "Play Stream : Basic"; };
	}
	r2cm::iItem::DoFunctionT PlayStream_Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( FMOD::System* fmod_system = nullptr );
			DECLARATION_SUB( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );
			PROCESS_SUB( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			//
			// Audio Load
			//
			DECLARATION_MAIN( FMOD::Sound* fmod_sound = nullptr );

			PROCESS_MAIN( fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound ) );
			r2_fmod_util::ERROR_CHECK( fmod_result );

			PROCESS_MAIN( fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF ) );    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
			r2_fmod_util::ERROR_CHECK( fmod_result );	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */

			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::Channel* fmod_channel = nullptr );
			{
				PROCESS_MAIN( fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2cm::linefeed2;

				std::cout << "[Any Key] " << "End" << r2cm::linefeed;
				_getch();

				std::cout << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_channel->stop() );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( fmod_result = fmod_sound->release() );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2cm::linefeed;

				PROCESS_SUB( r2_fmod_util::ReleaseSystem( &fmod_system ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PlayStream_Demo::GetTitleFunction() const
	{
		return []()->const char* { return "Play Stream : Demo"; };
	}
	r2cm::iItem::DoFunctionT PlayStream_Demo::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			//
			// System
			//
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Sound : Create
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

			std::cout << r2cm::split;

			{
				std::cout << "[1] " << "Play" << r2cm::linefeed;
				std::cout << "[2] " << "Stop" << r2cm::linefeed;
				std::cout << "[3] " << "Loop ON/OFF" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			//
			// Update Loop
			//
			{
				FMOD::Channel* fmod_channel = nullptr;
				r2::FrameManager frame_manager( 30u );
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

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2cm::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
						switch( input )
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
						}
					}

				} while( 27 != input );
			}

			//
			// Sound : Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// System : Release
			//
			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;
		};
	}



	FMOD_RESULT F_CALLBACK TempCallback( FMOD_CHANNELCONTROL* /*channelcontrol*/, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE /*callbacktype*/, void* /*commanddata1*/, void* /*commanddata2*/ )
	{
		std::cout << "Call - TempCallback" << r2cm::linefeed;

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
	r2cm::iItem::TitleFunctionT PlayAndCallback::GetTitleFunction() const
	{
		return []()->const char* { return "Play And Callback"; };
	}
	r2cm::iItem::DoFunctionT PlayAndCallback::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( FMOD::System* fmod_system = nullptr );
			DECLARATION_SUB( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );
			DECLARATION_SUB( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			//
			// Audio Load
			//
			DECLARATION_SUB( FMOD::Sound* fmod_sound = nullptr );
			{
				PROCESS_SUB( fmod_result = fmod_system->createSound( "resources/gmae.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &fmod_sound ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			//
			// Process
			//
			{
				DECLARATION_MAIN( FMOD::Channel* fmod_channel = nullptr );
				PROCESS_MAIN( fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				PROCESS_MAIN( fmod_channel->setCallback( TempCallback ) );
			}

			std::cout << r2cm::split;

			std::cout << r2cm::tab << "Wait 4 Callback : [Any Key] End" << r2cm::linefeed2;
			bool input = false;
			do
			{

				fmod_result = fmod_result = fmod_system->update();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				input = _kbhit();

			} while( !input );

			std::cout << r2cm::split;

			//
			// Audio Release
			//
			{
				PROCESS_SUB( fmod_result = fmod_sound->release() );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			//
			// System : Release
			//
			PROCESS_SUB( r2_fmod_util::ReleaseSystem( &fmod_system ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT VolumeControl::GetTitleFunction() const
	{
		return []()->const char* { return "Volume Control"; };
	}
	r2cm::iItem::DoFunctionT VolumeControl::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			std::cout << "[1] " << "Volume Up" << r2cm::linefeed;
			std::cout << "[2] " << "Volume Down" << r2cm::linefeed;

			std::cout << r2cm::split;

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

				const auto pivot_point = r2cm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{

					if( frame_manager.Update() )
					{
						r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_point );

						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2cm::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
						switch( input )
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
						}
					}
					
				} while( 27 != input );
			}

			//
			// Audio Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;
		};
	}



	r2cm::iItem::TitleFunctionT PositionControl::GetTitleFunction() const
	{
		return []()->const char* { return "Position Control"; };
	}
	r2cm::iItem::DoFunctionT PositionControl::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			std::cout << "[1] " << "Move First" << r2cm::linefeed;
			std::cout << "[2] " << "Move Half" << r2cm::linefeed;

			std::cout << r2cm::split;

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

				const auto pivot_point = r2cm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{

					if( frame_manager.Update() )
					{
						r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_point );

						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						r2_fmod_util::PrintSampleRateInfo( fmod_system );

						std::cout << r2cm::split;

						r2_fmod_util::PrintSoundInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelInfo( fmod_channel );
						r2_fmod_util::PrintChannelVolumeInfo( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
						switch( input )
						{
						case '1':
							fmod_result = fmod_channel->setPosition( 0u, FMOD_TIMEUNIT_MS );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						case '2':
							fmod_result = fmod_channel->setPosition( 10000u, FMOD_TIMEUNIT_MS );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						}
					}

				} while( 27 != input );
			}

			//
			// Audio Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;
		};
	}
}