#include "pch.h"
#include "FMOD_Load_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_iMenu.h"

#include "test_fmod/item/fmod_load_test.h"

#include "RootMenu.h"

r2cm::TitleFunctionT FMOD_Load_Menu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "FMOD Load Menu";
	};
}
r2cm::DescriptionFunctionT FMOD_Load_Menu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2cm::WriteFunctionT FMOD_Load_Menu::GetWriteFunction() const
{
	return []( r2cm::MenuProcessor* ret )
	{
		ret->AddItem( '1', fmod_load_test::LoadSound() );
		ret->AddItem( '2', fmod_load_test::LoadStream() );
		ret->AddItem( '3', fmod_load_test::Memory() );



		ret->AddSplit();



		ret->AddMenu( 27, RootMenu() );
	};
}