#include "pch.h"
#include "RootMenu.h"

#include <sstream>
#include <string>

#include "fmod_common.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test_fmod/item/fmod_basic_test.h"
#include "test_fmod/item/fmod_play_test.h"
#include "test_fmod/item/fmod_effect_test.h"
#include "test_fmod/item/fmod_channel_group_test.h"
#include "test_fmod/item/fmod_sound_analysis_test.h"
#include "test_fmod/item/etc_test.h"

#include "test_fmod/menu/FMOD_Load_Menu.h"
#include "test_fmod/menu/FMOD_Play_Menu.h"

r2cm::TitleFunctionT RootMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
			(
				std::stringstream()
				<< "Root Menu"
				<< " : <FMOD : v" << std::hex << FMOD_VERSION << ">"
				<< " : <" << r2cm::VersionInfo.String4Version << ">"
				).str();
		return ret.c_str();
	};
}
r2cm::DescriptionFunctionT RootMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}

r2cm::WriteFunctionT RootMenu::GetWriteFunction() const
{
	return []( r2cm::MenuProcessor* ret )
	{
		ret->AddItem( '1', fmod_basic_test::SystemCreateAndRelease() );
		ret->AddItem( '2', fmod_basic_test::VersionCheck() );



		ret->AddLineFeed();



		ret->AddMenu( '3', FMOD_Load_Menu() );
		ret->AddMenu( '4', FMOD_Play_Menu() );
		


		ret->AddLineFeed();



		ret->AddItem( 'q', fmod_effect_test::Echo() );
		ret->AddItem( 'w', fmod_effect_test::Fade() );
		ret->AddItem( 'e', fmod_effect_test::FadeStartFadeEnd() );
		ret->AddItem( 'r', fmod_effect_test::PitchControl() );



		ret->AddLineFeed();



		ret->AddItem( 'a', fmod_channel_group_test::Basic() );
		ret->AddItem( 's', fmod_channel_group_test::Group() );
		ret->AddItem( 'd', fmod_channel_group_test::Volume() );



		ret->AddLineFeed();



		ret->AddItem( 'z', fmod_sound_analysis_test::Frequency() );



		ret->AddSplit();



		ret->AddItem( 32, etc_test::Test1() );



		ret->AddSplit();



		ret->AddExit( 27 );
	};
}