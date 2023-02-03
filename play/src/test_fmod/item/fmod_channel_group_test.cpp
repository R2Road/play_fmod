#include "pch.h"
#include "fmod_channel_group_test.h"

#include <algorithm>
#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_FrameManager.h"
#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"
#include "utility/r2_fmod_util.h"

namespace fmod_channel_group_test
{
	r2cm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char* { return "Channel Group - Basic"; };
	}
	r2cm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eDoLeaveAction
		{
			std::cout << r2cm::split;

			//
			//
			//
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Master Channel Group
			//
			{
				std::cout << r2cm::tab << "+ Get Master Channel Group" << r2cm::linefeed2;

				DECLARATION_MAIN( FMOD::ChannelGroup* fmod_master_channelgroup = nullptr );
				PROCESS_MAIN( fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			//
			//
			r2_fmod_util::ReleaseSystem( &fmod_system );

			std::cout << r2cm::split;

			return r2cm::eDoLeaveAction::Pause;
		};
	}



	r2cm::TitleFunctionT Group::GetTitleFunction() const
	{
		return []()->const char* { return "Channel Group - Group"; };
	}
	r2cm::DoFunctionT Group::GetDoFunction() const
	{
		return []()->r2cm::eDoLeaveAction
		{
			//
			//
			//
			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
			r2_fmod_util::CreateSystem( &fmod_system );

			std::cout << r2cm::split;

			//
			//
			//
			DECLARATION_MAIN( FMOD::ChannelGroup* fmod_master_channelgroup = nullptr );
			DECLARATION_MAIN( FMOD::ChannelGroup* groupA = nullptr );
			DECLARATION_MAIN( FMOD::ChannelGroup* groupB = nullptr );

			std::cout << r2cm::split;

			//
			// Master Channel Group
			//
			{
				std::cout << r2cm::tab << "+ Get Master Channel Group" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			//
			// Create Channel Group
			//
			{
				std::cout << r2cm::tab << "+ Create Channel Group" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_system->createChannelGroup( "Group A", &groupA ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				PROCESS_MAIN( fmod_result = fmod_system->createChannelGroup( "Group B", &groupB ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			//
			// Add Channel Group
			//
			{
				std::cout << r2cm::tab << "+ Add Channel Group" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_master_channelgroup->addGroup( groupA ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				PROCESS_MAIN( fmod_result = fmod_master_channelgroup->addGroup( groupB ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

			//
			// Release Channel Group
			//
			{
				std::cout << r2cm::tab << "+ Release Channel Group" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = groupA->release() );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				PROCESS_MAIN( fmod_result = groupB->release() );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			//
			//
			r2_fmod_util::ReleaseSystem( &fmod_system );

			std::cout << r2cm::split;

			return r2cm::eDoLeaveAction::Pause;
		};
	}



	r2cm::TitleFunctionT Volume::GetTitleFunction() const
	{
		return []()->const char* { return "Channel Group - Volume"; };
	}
	r2cm::DoFunctionT Volume::GetDoFunction() const
	{
		return []()->r2cm::eDoLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << "[1/2] " << "Group A Volume Up/Down" << r2cm::linefeed;
			std::cout << "[q/w] " << "Group B Volume Up/Down" << r2cm::linefeed;
			std::cout << "[a/s] " << "Master Channel Group Volume Up/Down" << r2cm::linefeed;

			std::cout << r2cm::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			FMOD::ChannelGroup* fmod_master_channel_group = nullptr;
			{
				fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channel_group );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			FMOD::ChannelGroup* groupA = nullptr;
			FMOD::ChannelGroup* groupB = nullptr;
			{
				fmod_result = fmod_system->createChannelGroup( "Group A", &groupA );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_system->createChannelGroup( "Group B", &groupB );
				r2_fmod_util::ERROR_CHECK( fmod_result );


				fmod_result = fmod_master_channel_group->addGroup( groupA );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_master_channel_group->addGroup( groupB );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			FMOD::Sound* fmod_sound_1 = nullptr;
			FMOD::Sound* fmod_sound_2 = nullptr;
			{
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound_1 );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_system->createStream( "resources/melodic_adventure_theme_and_rhythmic_variation_c64_style.ogg", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound_2 );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Play Sound
			//
			FMOD::Channel* fmod_channel_1 = nullptr;
			FMOD::Channel* fmod_channel_2 = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_sound_1, 0, false, &fmod_channel_1 );
				r2_fmod_util::ERROR_CHECK( fmod_result );
				fmod_channel_1->setChannelGroup( groupA );

				fmod_result = fmod_system->playSound( fmod_sound_2, 0, false, &fmod_channel_2 );
				r2_fmod_util::ERROR_CHECK( fmod_result );
				fmod_channel_2->setChannelGroup( groupB );
			}

			//
			// Update Loop
			//
			{
				r2::FrameManager frame_manager( 30u );
				frame_manager.Reset();

				float master_volume = 1.0f;
				float group_a_volume = 1.0f;
				float group_b_volume = 1.0f;

				const auto pivot_point = r2cm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{

					if( frame_manager.Update() )
					{
						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_point );

						std::cout << r2cm::tab << "Group A : ";
						r2_fmod_util::PrintChannelVolumeInfo( groupA );
						std::cout << r2cm::linefeed;

						std::cout << r2cm::split;

						std::cout << r2cm::tab << "Group B : ";
						r2_fmod_util::PrintChannelVolumeInfo( groupB );
						std::cout << r2cm::linefeed;

						std::cout << r2cm::split;

						std::cout << r2cm::tab << "Master : ";
						r2_fmod_util::PrintChannelVolumeInfo( fmod_master_channel_group );
						std::cout << r2cm::linefeed;

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
							group_a_volume -= 0.1f;
							group_a_volume = std::max( 0.0f, group_a_volume );

							fmod_result = groupA->setVolume( group_a_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						case '2':
							group_a_volume += 0.1f;
							group_a_volume = std::min( 1.0f, group_a_volume );

							fmod_result = groupA->setVolume( group_a_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;

						case 'q':
							group_b_volume -= 0.1f;
							group_b_volume = std::max( 0.0f, group_b_volume );

							fmod_result = groupB->setVolume( group_b_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						case 'w':
							group_b_volume += 0.1f;
							group_b_volume = std::min( 1.0f, group_b_volume );

							fmod_result = groupB->setVolume( group_b_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;

						case 'a':
							master_volume -= 0.1f;
							master_volume = std::max( 0.0f, master_volume );

							fmod_result = fmod_master_channel_group->setVolume( master_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						case 's':
							master_volume += 0.1f;
							master_volume = std::min( 1.0f, master_volume );

							fmod_result = fmod_master_channel_group->setVolume( master_volume );
							r2_fmod_util::ERROR_CHECK( fmod_result );
							break;
						}
					}
					
				} while( 27 != input );
			}

			//
			// Release
			//
			{
				// Sound
				fmod_result = fmod_sound_1->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_sound_2->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// Channel Group
				fmod_result = groupA->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = groupB->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eDoLeaveAction::None;
		};
	}
}