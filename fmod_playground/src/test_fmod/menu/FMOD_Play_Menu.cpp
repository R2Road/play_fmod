#include "pch.h"
#include "FMOD_Play_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_Menu.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test_fmod/item/fmod_play_test.h"

#include "RootMenu.h"

r2cm::MenuUp FMOD_Play_Menu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', fmod_play_test::PlaySound_Basic::GetInstance() );
		ret->AddItem( '2', fmod_play_test::PlaySound_Demo::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( '3', fmod_play_test::PlayStream_Basic::GetInstance() );
		ret->AddItem( '4', fmod_play_test::PlayStream_Demo::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( 'q', fmod_play_test::PlayAndCallback::GetInstance() );
		ret->AddItem( 'w', fmod_play_test::VolumeControl::GetInstance() );
		ret->AddItem( 'e', fmod_play_test::PositionControl::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<RootMenu>( 27 );
	}

	return ret;
}