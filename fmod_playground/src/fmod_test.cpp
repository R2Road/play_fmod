#include "pch.h"
#include "fmod_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2_fmod_util.h"
#include "r2_FrameManager.h"
#include "r2_eTestResult.h"

namespace fmod_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "FMOD : Basic";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
			
			std::cout << r2::split;

			FMOD::System* fmod_system;
			FMOD_RESULT fmod_result;

			std::cout << r2::tab << "+ Variable" << r2::linefeed << r2::linefeed;
			std::cout << r2::tab2 << "FMOD::System* fmod_system;" << r2::linefeed;
			std::cout << r2::tab2 << "FMOD_RESULT fmod_result;" << r2::linefeed;
			std::cout << r2::linefeed;

			//
			// Initialize
			//
			{
				// Create FMOD
				fmod_result = FMOD::System_Create( &fmod_system );
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				// Init FMOD
				fmod_result = fmod_system->init( 32, FMOD_INIT_NORMAL, 0 );
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				//
				std::cout << r2::tab << "+ Initialize" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = FMOD::System_Create( &fmod_system );" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->init( 32, FMOD_INIT_NORMAL, 0 );" << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Shut Down
			//
			{
				// Close
				fmod_result = fmod_system->close();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				// Release
				fmod_result = fmod_system->release();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				//
				std::cout << r2::tab << "+ Shut Down" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->close();" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->release();" << r2::linefeed;
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc VersionCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "FMOD : Version Check";
		};
	}
	r2::iTest::DoFunc VersionCheck::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			FMOD::System* fmod_system;
			FMOD_RESULT fmod_result;

			//
			// Initialize
			//
			{
				r2_fmod_util::CreateSystem( &fmod_system );
			}

			std::cout << r2::split;

			//
			// Version Check
			//
			{
				unsigned int version;
				fmod_result = fmod_system->getVersion( &version );
				FMOD_ErrorString( fmod_result );

				std::cout << "\t" << "FMOD lib version " << std::hex << version;

				if( version < FMOD_VERSION )
				{
					std::cout << "doesn't match header version " << FMOD_VERSION;
				}

				std::cout << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Shut Down
			//
			{
				// Close
				fmod_result = fmod_system->close();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				// Release
				fmod_result = fmod_system->release();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}
			}

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc PlaySound::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "FMOD : Play Sound";
		};
	}
	r2::iTest::DoFunc PlaySound::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			FMOD::System* fmod_system;
			FMOD::Sound* fmod_sound;
			FMOD::Channel* fmod_channel = 0;
			FMOD_RESULT fmod_result;

			//
			// Initialize
			//
			{
				r2_fmod_util::CreateSystem( &fmod_system );
			}

			//
			// Preload Audio + Setup
			//
			{
				// Preload Audio
				fmod_result = fmod_system->createSound( "resources/TremLoadingloopl.wav", FMOD_DEFAULT, 0, &fmod_sound );
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				// Loop Flag
				fmod_result = fmod_sound->setMode( FMOD_LOOP_OFF );    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
				if( FMOD_RESULT::FMOD_OK != fmod_result )	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}
			}

			//
			// Update Loop
			//
			{
				r2::FrameManager frame_manager;
				frame_manager.SetFPS( 30 );
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
							if( FMOD_RESULT::FMOD_OK != fmod_result )
							{
								FMOD_ErrorString( fmod_result );
								return r2::eTestResult::RunTest;
							}
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
						system( "cls" );

						std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
						std::cout << "[1] " << "Play" << r2::linefeed;
						std::cout << "[2] " << "Stop" << r2::linefeed;

						std::cout << r2::split;

						fmod_result = fmod_system->update();
						FMOD_ErrorString( fmod_result );

						r2_fmod_util::PrintChannelInfo( fmod_channel );

						std::cout << r2::split;

						r2_fmod_util::PrintChannelsPlayingInfo( fmod_system );

						std::cout << r2::split;
					}
				}
			}

			//
			// Shut Down
			//
			{
				fmod_result = fmod_sound->release();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				fmod_result = fmod_system->close();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}

				fmod_result = fmod_system->release();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					FMOD_ErrorString( fmod_result );
					return r2::eTestResult::RunTest;
				}
			}

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}
}