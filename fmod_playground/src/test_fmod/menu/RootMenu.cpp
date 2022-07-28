#include "pch.h"
#include "RootMenu.h"

#include <sstream>
#include <string>

#include "fmod_common.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_Menu.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test_fmod/item/fmod_basic_test.h"
#include "test_fmod/item/fmod_load_test.h"
#include "test_fmod/item/fmod_play_test.h"
#include "test_fmod/item/fmod_effect_test.h"
#include "test_fmod/item/fmod_channel_group_test.h"
#include "test_fmod/item/fmod_sound_analysis_test.h"
#include "test_fmod/item/etc_test.h"

#include "test_fmod/menu/FMOD_Play_Menu.h"

const char* RootMenu::GetTitle()
{
	static const std::string ret =
	(
		std::stringstream()
		<< "Root Menu"
		<< " : <FMOD : v" << std::hex << FMOD_VERSION << ">"
		<< " : <" << r2cm::VersionInfo.String4Version << ">"
	).str();
	return ret.c_str();
}

r2cm::MenuUp RootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> To do : FMOD Studio È°¿ë"
	) );

	{
		ret->AddItem( '1', fmod_basic_test::SystemCreateAndRelease::GetInstance() );
		ret->AddItem( '2', fmod_basic_test::VersionCheck::GetInstance() );
		ret->AddItem( '3', fmod_load_test::Basic::GetInstance() );
		ret->AddMenu<FMOD_Play_Menu>( '4' );


		ret->AddLineFeed();


		ret->AddItem( '9', fmod_load_test::Memory::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', fmod_effect_test::Echo::GetInstance() );
		ret->AddItem( 'w', fmod_effect_test::Fade::GetInstance() );
		ret->AddItem( 'e', fmod_effect_test::FadeStartFadeEnd::GetInstance() );
		ret->AddItem( 'r', fmod_effect_test::PitchControl::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'a', fmod_channel_group_test::Basic::GetInstance() );
		ret->AddItem( 's', fmod_channel_group_test::Group::GetInstance() );
		ret->AddItem( 'd', fmod_channel_group_test::Volume::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'z', fmod_sound_analysis_test::Frequency::GetInstance() );


		ret->AddSplit();


		ret->AddItem( 32, etc_test::Test1::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction { return r2cm::eItemLeaveAction::Exit; }
		);
	}

	return ret;
}