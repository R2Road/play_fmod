#include "pch.h"
#include "fmod_channel_group_test.h"

#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2_Assert.h"
#include "r2_fmod_util.h"
#include "r2_FrameManager.h"
#include "r2_eTestResult.h"

namespace fmod_channel_group_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char* { return "FMOD : Channel Group - Basic"; };
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			r2_fmod_util::CreateSystem( &fmod_system );

			{
				//
				// Channel Group
				//
				FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;
				fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				//
				std::cout << r2::tab << "+ Initialize" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );" << r2::linefeed;
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}