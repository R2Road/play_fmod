#include "pch.h"
#include "r2_RootMenu.h"

#include "r2_Director.h"
#include "r2_eTestResult.h"

#include "fmod_basic_test.h"
#include "fmod_2_test.h"
#include "fmod_3_test.h"

namespace r2
{
	MenuUp RootMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle()
			, "> Add Some One"
		) );

		{
			ret->AddChild( '1', fmod_basic_test::Basic::GetInstance() );
			ret->AddChild( '2', fmod_basic_test::VersionCheck::GetInstance() );

			ret->AddLineFeed();

			ret->AddChild( '3', fmod_test::PlaySound::GetInstance() );
			ret->AddChild( '4', fmod_test::PlayStream::GetInstance() );
			ret->AddChild( '5', fmod_test::PlayAndCallback::GetInstance() );
			ret->AddChild( '6', fmod_test::VolumeControl::GetInstance() );

			ret->AddLineFeed();

			ret->AddChild( '7', fmod_test::Effect::GetInstance() );

			ret->AddSplit();

			ret->AddChild(
				27
				, []()->const char* { return "Exit"; }
				, []()->eTestResult { return eTestResult::Exit; }
			);

			ret->AddSplit();
		}

		return ret;
	}
}