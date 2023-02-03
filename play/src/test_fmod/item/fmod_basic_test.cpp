#include "pch.h"
#include "fmod_basic_test.h"

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Inspector.h"

#include "utility/r2_fmod_util.h"

namespace fmod_basic_test
{
	r2cm::TitleFunctionT SystemCreateAndRelease::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "System Create And Release";
		};
	}
	r2cm::DoFunctionT SystemCreateAndRelease::GetDoFunction() const
	{
		return []()->r2cm::eDoLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::System* fmod_system = nullptr );
			DECLARATION_MAIN( FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Create" << r2cm::linefeed2;

				// Create FMOD
				PROCESS_MAIN( fmod_result = FMOD::System_Create( &fmod_system ) );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Init" << r2cm::linefeed2;

				// Init FMOD
				PROCESS_MAIN( fmod_result = fmod_system->init( 32, FMOD_INIT_NORMAL, 0 ) );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Close" << r2cm::linefeed2;

				// Close
				PROCESS_MAIN( fmod_result = fmod_system->close() );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Release" << r2cm::linefeed2;

				// Release
				PROCESS_MAIN( fmod_result = fmod_system->release() );
				EXPECT_TRUE( FMOD_RESULT::FMOD_OK == fmod_result );
			}

			std::cout << r2cm::split;

			return r2cm::eDoLeaveAction::Pause;
		};
	}



	r2cm::TitleFunctionT VersionCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Version Check";
		};
	}
	r2cm::DoFunctionT VersionCheck::GetDoFunction() const
	{
		return []()->r2cm::eDoLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( FMOD::System* fmod_system = nullptr );
			PROCESS_MAIN( r2_fmod_util::CreateSystem( &fmod_system ) );

			std::cout << r2cm::split;

			//
			// Version Check
			//
			{
				std::cout << r2cm::tab << "+ Version Check" << r2cm::linefeed2;

				DECLARATION_MAIN( unsigned int version = 0 );
				DECLARATION_MAIN( const FMOD_RESULT fmod_result = fmod_system->getVersion( &version ) );
				EXPECT_TRUE( r2_fmod_util::ERROR_CHECK( fmod_result ) );
				EXPECT_TRUE( version == FMOD_VERSION );
				OUTPUT_VALUE( version );

				std::cout << r2cm::linefeed2;

				PROCESS_MAIN( std::cout << std::hex << version << std::dec );

				std::cout << r2cm::linefeed3;

				std::cout << "FMOD lib version : " << std::hex << version << std::dec << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			PROCESS_MAIN( r2_fmod_util::ReleaseSystem( &fmod_system ) );

			std::cout << r2cm::split;

			return r2cm::eDoLeaveAction::Pause;
		};
	}
}