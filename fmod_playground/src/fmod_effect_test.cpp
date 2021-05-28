#include "pch.h"
#include "fmod_effect_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2_Assert.h"
#include "r2_fmod_util.h"
#include "r2_FrameManager.h"
#include "r2_eTestResult.h"

namespace fmod_effect_test
{
	r2::iTest::TitleFunc Echo::GetTitleFunction() const
	{
		return []()->const char* { return "FMOD : Effect - Echo"; };
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
			//
			//
			FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;
			FMOD::DSP* fsm_dsp_echo = nullptr;
			{
				// Channel Group
				fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// DSP
				fmod_result = fmod_system->createDSPByType( FMOD_DSP_TYPE_ECHO, &fsm_dsp_echo );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// Add
				fmod_result = fmod_master_channelgroup->addDSP( 0, fsm_dsp_echo );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fsm_dsp_echo->setBypass( true );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			//
			// Play Sound
			//
			FMOD::Channel* fmod_channel = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_current_sound, 0, false, &fmod_channel );
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

						case 27: // ESC
							process = false;
							break;
						}
					}

					if( frame_manager.Update() )
					{
						system( "cls" );

						std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
						std::cout << "[1] " << "Effect ON/OFF" << r2::linefeed;

						std::cout << r2::split;

						bool is_by_pass = false;
						fmod_result = fsm_dsp_echo->getBypass( &is_by_pass );
						r2_fmod_util::ERROR_CHECK( fmod_result );
						std::cout << "Echo " << ( is_by_pass ? "OFF" : "ON" ) << r2::linefeed;

						std::cout << r2::split;

						fmod_result = fmod_result = fmod_system->update();
						r2_fmod_util::ERROR_CHECK( fmod_result );

						r2_fmod_util::PrintChannelInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
			}

			//
			// Channel Group + DSP
			//
			{
				fmod_result = fmod_master_channelgroup->removeDSP( fsm_dsp_echo );
				r2_fmod_util::ERROR_CHECK( fmod_result );

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
}