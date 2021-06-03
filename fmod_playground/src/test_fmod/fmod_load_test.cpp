#include "pch.h"
#include "fmod_load_test.h"

#include "fmod.hpp"
#include "fmod_errors.h"

#include "base/r2_eTestResult.h"

#include "base/r2_Assert.h"
#include "utility/r2_fmod_util.h"

namespace fmod_load_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "FMOD : Sound Load - Basic";
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
}