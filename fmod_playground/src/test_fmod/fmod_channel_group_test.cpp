#include "pch.h"
#include "fmod_channel_group_test.h"

#include <algorithm>
#include <conio.h>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "base/r2_Assert.h"
#include "base/r2_FrameManager.h"
#include "base/r2_eTestResult.h"
#include "utility/r2_fmod_util.h"

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

			//
			// Master Channel Group
			//
			{
				FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;
				fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Get Master Channel Group" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );" << r2::linefeed;
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc Group::GetTitleFunction() const
	{
		return []()->const char* { return "FMOD : Channel Group - Group"; };
	}
	r2::iTest::DoFunc Group::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			FMOD::System* fmod_system = nullptr;
			FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

			FMOD::ChannelGroup* fmod_master_channelgroup = nullptr;

			FMOD::ChannelGroup* groupA = nullptr;
			FMOD::ChannelGroup* groupB = nullptr;

			r2_fmod_util::CreateSystem( &fmod_system );

			//
			// Master Channel Group
			//
			{
				fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Get Master Channel Group" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_system->getMasterChannelGroup( &fmod_master_channelgroup );" << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Create Channel Group
			//
			{
				fmod_result = fmod_system->createChannelGroup( "Group A", &groupA );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_system->createChannelGroup( "Group B", &groupB );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Create Channel Group" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_system->createChannelGroup( \"Group A\", &groupA )" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_system->createChannelGroup( \"Group A\", &groupB )" << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Add Channel Group
			//
			{
				fmod_result = fmod_master_channelgroup->addGroup( groupA );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = fmod_master_channelgroup->addGroup( groupB );
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Add Channel Group" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_master_channelgroup->addGroup( groupA );" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = fmod_master_channelgroup->addGroup( groupB );" << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Add Channel Group
			//
			{
				fmod_result = groupA->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				fmod_result = groupB->release();
				r2_fmod_util::ERROR_CHECK( fmod_result );

				std::cout << r2::tab << "+ Release Channel Group" << r2::linefeed << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = groupA->release();" << r2::linefeed;
				std::cout << r2::tab2 << "fmod_result = groupB->release();" << r2::linefeed;
			}

			r2_fmod_util::ReleaseSystem( &fmod_system );

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}