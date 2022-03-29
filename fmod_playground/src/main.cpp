#include "pch.h"
#include <Windows.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "r2cm/r2cm_Director.h"
#include "test_fmod/menu/RootMenu.h"

int main()
{
	//
	// Environment : Title
	//
	SetConsoleTitle( TEXT( "fmod_playground" ) );

	//
	// Environment : Size
	//
	system( "mode con lines=60 cols=120" );

	//
	// Environment : Position
	//
	{
		HWND hWnd = GetConsoleWindow();
		RECT rectClient;
		GetClientRect( hWnd, &rectClient );
		MoveWindow( hWnd, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE );
	}

	//
	// Setup
	//
	r2cm::Director director;
	director.Setup( RootMenu::Create( director ) );

	//
	// Process
	//
	director.Run();

	return 0;
}
