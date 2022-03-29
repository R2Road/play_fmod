#include "pch.h"
#include "fmod_load_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "base/r2_eTestResult.h"

#include "base/r2_Assert.h"
#include "r2/r2_FrameManager.h"
#include "utility/r2_fmod_util.h"

namespace fmod_load_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound Load - Basic";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			std::cout << r2::split;

			//
			// Audio Load
			//
			FMOD::Sound* fmod_sound = nullptr;
			{
				// Load
				fmod_result = fmod_system->createSound( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				// Setup
				fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Load" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "FMOD::Sound* fmod_sound = nullptr;" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->createSound( \"resources/TremLoadingloopl.wav\", FMOD_DEFAULT, 0, &fmod_sound );" << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Audio Release
			//
			{
				fmod_result = fmod_sound->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Release" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_sound->release();" << r2::linefeed;
			}

			std::cout << r2::split;

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc Memory::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound Load - Memory";
		};
	}
	r2::iTest::DoFunc Memory::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			std::cout << r2::split;

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

				std::cout << r2::tab << "+ Variable" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "void* buff = 0;" << r2::linefeed;
				std::cout << r2::tab2 << "int length = 0;" << r2::linefeed;
				std::cout << r2::tab2 << "FMOD_CREATESOUNDEXINFO exinfo;" << r2::linefeed;
				std::cout << r2::linefeed;

				std::cout << r2::tab << "+ Load" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "r2_fmod_util::Common_LoadFileMemory( \"resources/TremLoadingloopl.wav\", &buff, &length );" << r2::linefeed;
				std::cout << r2::tab2 << "memset( &exinfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );" << r2::linefeed;
				std::cout << r2::tab2 << "exinfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );" << r2::linefeed;
				std::cout << r2::tab2 << "exinfo.length = length;" << r2::linefeed;
				std::cout << r2::linefeed;

				std::cout << r2::tab << "+ Release" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "r2_fmod_util::Common_UnloadFileMemory( buff );" << r2::linefeed;
				std::cout << r2::linefeed;

				std::cout << r2::tab << "+ Note" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "If loading as a stream, the memory must stay active so do not free it!" << r2::linefeed;
			}

			FMOD::Channel* fmod_channel = nullptr;
			{
				fmod_result = fmod_system->playSound( fmod_sound, 0, false, &fmod_channel );
				r2_fmod_util::ERROR_CHECK( fmod_result );
			}

			std::cout << r2::split;

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

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}
}