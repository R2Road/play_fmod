#include "pch.h"
#include "etc_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_FrameManager.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"
#include "utility/r2_fmod_util.h"

namespace etc_test
{
	r2cm::iItem::TitleFunctionT Test1::GetTitleFunction() const
	{
		return []()->const char* { return "ETC : Test 1"; };
	}
	r2cm::iItem::DoFunctionT Test1::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			std::cout << "[1] " "Fade Out" << r2cm::linefeed;
			std::cout << "[2] " "Fade In" << r2cm::linefeed;

			std::cout << r2cm::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			FMOD::Sound* fmod_sound = nullptr;
			{
				// Create
				fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

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
						r2_fmod_util::PrintChannelDSPClock( fmod_channel );

						std::cout << r2cm::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2cm::split;

						std::cout << "Note : Fade Point Works Only Once" << r2cm::linefeed;

						std::cout << r2cm::split;
					}

					if( _kbhit() )
					{
						input = _getch();
						switch( input )
						{
						case '1':
						{
							FMOD::Sound* current_sound = nullptr;
							fmod_result = fmod_channel->getCurrentSound( &current_sound );
							r2_fmod_util::ERROR_CHECK( fmod_result );

							FMOD_SOUND_TYPE sound_type;
							FMOD_SOUND_FORMAT sound_format;
							int channels;
							int bits;
							fmod_result = current_sound->getFormat( &sound_type, &sound_format, &channels, &bits );
							r2_fmod_util::ERROR_CHECK( fmod_result );

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
						}
					}
					
				} while( 27 != input );
			}

			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eItemLeaveAction::None;
		};
	}
}