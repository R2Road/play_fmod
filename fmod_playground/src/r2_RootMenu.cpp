#include "pch.h"
#include "r2_RootMenu.h"

#include "r2_Director.h"
#include "r2_eTestResult.h"

#include "fmod_test.h"

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
			ret->AddChild( '1', fmod_test::Basic::GetInstance() );

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