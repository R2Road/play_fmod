#include "pch.h"
#include "RootMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test_fmod/item/test_basic.h"
#include "test_fmod/item/fmod_load_test.h"
#include "test_fmod/item/fmod_play_test.h"
#include "test_fmod/item/fmod_effect_test.h"
#include "test_fmod/item/fmod_channel_group_test.h"
#include "test_fmod/item/fmod_sound_analysis_test.h"
#include "test_fmod/item/etc_test.h"

r2cm::MenuUp RootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', test_basic::SystemCreateAndRelease::GetInstance() );
		ret->AddItem( '2', test_basic::VersionCheck::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( '3', fmod_load_test::Basic::GetInstance() );
		ret->AddItem( '4', fmod_play_test::PlaySound::GetInstance() );
		ret->AddItem( '5', fmod_play_test::PlayStream::GetInstance() );
		ret->AddItem( '6', fmod_play_test::PlayAndCallback::GetInstance() );
		ret->AddItem( '7', fmod_play_test::VolumeControl::GetInstance() );
		ret->AddItem( '8', fmod_play_test::PositionControl::GetInstance() );


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