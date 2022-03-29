#include "pch.h"
#include "fmod_basic_test.h"

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2cm/r2cm_eTestEndAction.h"

#include "r2/r2_Assert.h"
#include "utility/r2_fmod_util.h"

namespace fmod_basic_test
{
	r2cm::iItem::TitleFuncT SystemCreateAndRelease::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "System Create And Release";
		};
	}
	r2cm::iItem::DoFuncT SystemCreateAndRelease::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
			
			std::cout << r2::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

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
					std::cerr << FMOD_ErrorString( fmod_result );
					assert( false );
				}

				// Init FMOD
				fmod_result = fmod_system->init( 32, FMOD_INIT_NORMAL, 0 );
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					std::cerr << FMOD_ErrorString( fmod_result );
					assert( false );
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
					std::cerr << FMOD_ErrorString( fmod_result );
					assert( false );
				}

				// Release
				fmod_result = fmod_system->release();
				if( FMOD_RESULT::FMOD_OK != fmod_result )
				{
					std::cerr << FMOD_ErrorString( fmod_result );
					assert( false );
				}

				//
				std::cout << r2::tab << "+ Shut Down" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->close();" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->release();" << r2::linefeed;
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::None;
		};
	}



	r2cm::iItem::TitleFuncT VersionCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Version Check";
		};
	}
	r2cm::iItem::DoFuncT VersionCheck::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			FMOD::System* fmod_system = nullptr;
			r2_fmod_util::CreateSystem( &fmod_system );

			std::cout << r2::split;

			//
			// Version Check
			//
			{
				unsigned int version = 0;
				const FMOD_RESULT fmod_result = fmod_system->getVersion( &version );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "FMOD lib version " << std::hex << version << std::dec;
				if( version < FMOD_VERSION )
				{
					std::cout << "doesn't match header version " << FMOD_VERSION;
				}

				std::cout << r2::linefeed;
			}

			std::cout << r2::split;

			r2_fmod_util::ReleaseSystem( &fmod_system );

			return r2cm::eTestEndAction::None;
		};
	}
}