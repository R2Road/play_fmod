#include "pch.h"
#include "FMOD_Load_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_Menu.h"

#include "test_fmod/item/fmod_load_test.h"

#include "RootMenu.h"

r2cm::MenuUp FMOD_Load_Menu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', fmod_load_test::LoadSound::GetInstance() );
		ret->AddItem( '2', fmod_load_test::LoadStream::GetInstance() );
		ret->AddItem( '3', fmod_load_test::Memory::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<RootMenu>( 27 );
	}

	return ret;
}