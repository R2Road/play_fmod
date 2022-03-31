#include "pch.h"
#include "fmod_basic_test.h"

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"
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

			DECLARATION_MAIN( FMOD::System* fmod_system = nullptr );
			DECLARATION_MAIN( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Create" << r2::linefeed2;

				// Create FMOD
				PROCESS_MAIN( fmod_result = FMOD::System_Create( &fmod_system ) );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Init" << r2::linefeed2;

				// Init FMOD
				PROCESS_MAIN( fmod_result = fmod_system->init( 32, FMOD_INIT_NORMAL, 0 ) );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Close" << r2::linefeed2;

				// Close
				PROCESS_MAIN( fmod_result = fmod_system->close() );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Release" << r2::linefeed2;

				// Release
				PROCESS_MAIN( fmod_result = fmod_system->release() );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
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

			std::cout << r2::split;

			DECLARATION_MAIN( FMOD::System* fmod_system = nullptr );
			PROCESS_MAIN( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2::split;

			//
			// Version Check
			//
			{
				std::cout << r2::tab << "+ Version Check" << r2::linefeed2;

				DECLARATION_MAIN( unsigned int version = 0 );
				DECLARATION_MAIN( const FMOD_RESULT fmod_result = fmod_system->getVersion( &version ) );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::linefeed;

				std::cout << "FMOD lib version " << std::hex << version << std::dec << r2::linefeed;

				std::cout << r2::linefeed;

				EXPECT_TRUE( version == FMOD_VERSION );
			}

			std::cout << r2::split;

			PROCESS_MAIN( r2_fmod_util::ReleaseSystem( &fmod_system ) );

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}