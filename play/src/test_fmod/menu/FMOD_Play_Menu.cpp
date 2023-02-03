#include "pch.h"
#include "FMOD_Play_Menu.h"

#include "r2cm/r2cm_Director.h"

#include "test_fmod/item/fmod_play_test.h"

#include "RootMenu.h"

r2cm::TitleFunctionT FMOD_Play_Menu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "FMOD Play Menu";
	};
}
r2cm::DescriptionFunctionT FMOD_Play_Menu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2cm::WriteFunctionT FMOD_Play_Menu::GetWriteFunction() const
{
	return []( r2cm::MenuProcessor* ret )
	{
		ret->AddItem( '1', fmod_play_test::PlaySound_Basic() );
		ret->AddItem( '2', fmod_play_test::PlaySound_Demo() );



		ret->AddLineFeed();



		ret->AddItem( '3', fmod_play_test::PlayStream_Basic() );
		ret->AddItem( '4', fmod_play_test::PlayStream_Demo() );



		ret->AddLineFeed();



		ret->AddItem( 'q', fmod_play_test::PlayAndCallback() );
		ret->AddItem( 'w', fmod_play_test::VolumeControl() );
		ret->AddItem( 'e', fmod_play_test::PositionControl() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}