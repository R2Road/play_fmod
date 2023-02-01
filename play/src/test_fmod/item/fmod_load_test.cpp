#include "pch.h"
#include "fmod_load_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_FrameManager.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "utility/r2_fmod_util.h"

namespace fmod_load_test
{
	r2cm::iItem::TitleFunctionT LoadSound::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Load Sound";
		};
	}
	r2cm::iItem::DoFunctionT LoadSound::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( FMOD::System* fmod_system = nullptr );
			DECLARATION_SUB( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );
			PROCESS_SUB( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::Sound* fmod_sound = nullptr );

			std::cout << r2cm::split;

			//
			// Audio Load
			//
			{
				std::cout << r2cm::tab << "+ Load" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_system->createSound( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound ) );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Setup" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF ) );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			//
			// Audio Release
			//
			{
				std::cout << r2cm::tab << "+ Release" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_sound->release() );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			PROCESS_SUB( r2_fmod_util::ReleaseSystem( &fmod_system ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LoadStream::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Load Stream";
		};
	}
	r2cm::iItem::DoFunctionT LoadStream::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( FMOD::System* fmod_system = nullptr );
			DECLARATION_SUB( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );
			PROCESS_SUB( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::Sound* fmod_sound = nullptr );

			std::cout << r2cm::split;

			//
			// Audio Load
			//
			{
				std::cout << r2cm::tab << "+ Load" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_system->createStream( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound ) );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Setup" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF ) );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			//
			// Audio Release
			//
			{
				std::cout << r2cm::tab << "+ Release" << r2cm::linefeed2;

				PROCESS_MAIN( fmod_result = fmod_sound->release() );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
			}

			std::cout << r2cm::split;

			PROCESS_SUB( r2_fmod_util::ReleaseSystem( &fmod_system ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Memory::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound Load - Memory";
		};
	}
	r2cm::iItem::DoFunctionT Memory::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			std::cout << r2cm::split;

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
				void* buff = 0;
				int length = 0;
				FMOD_CREATESOUNDEXINFO exinfo;

				// Memory
				r2_fmod_util::Common_LoadFileMemory( "resources/TremLoadingloopl.wav", &buff, &length );
				memset( &exinfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );
				exinfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );
				exinfo.length = length;

				// Create
				fmod_result = fmod_system->createSound( (const char *)buff, FMOD_OPENMEMORY | FMOD_LOOP_OFF, &exinfo, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// Release
				r2_fmod_util::Common_UnloadFileMemory( buff );
				// don't need the original memory any more.
				// Note!
				// If loading as a stream, the memory must stay active so do not free it!

				std::cout << r2cm::tab << "+ Variable" << r2cm::linefeed << r2cm::linefeed;
				std::cout << r2cm::tab2 << "void* buff = 0;" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "int length = 0;" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "FMOD_CREATESOUNDEXINFO exinfo;" << r2cm::linefeed;
				std::cout << r2cm::linefeed;

				std::cout << r2cm::tab << "+ Load" << r2cm::linefeed << r2cm::linefeed;
				std::cout << r2cm::tab2 << "r2_fmod_util::Common_LoadFileMemory( \"resources/TremLoadingloopl.wav\", &buff, &length );" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "memset( &exinfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "exinfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "exinfo.length = length;" << r2cm::linefeed;
				std::cout << r2cm::linefeed;

				std::cout << r2cm::tab << "+ Release" << r2cm::linefeed << r2cm::linefeed;
				std::cout << r2cm::tab2 << "r2_fmod_util::Common_UnloadFileMemory( buff );" << r2cm::linefeed;
				std::cout << r2cm::linefeed;

				std::cout << r2cm::tab << "+ Note" << r2cm::linefeed << r2cm::linefeed;
				std::cout << r2cm::tab2 << "If loading as a stream, the memory must stay active so do not free it!" << r2cm::linefeed;
			}

			FMOD::Channel* fmod_channel = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2cm::split;

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

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}