#include "pch.h"
#include "r2_fmod_util.h"

#include <iostream>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2_Assert.h"

namespace r2_fmod_util
{
	void CreateSystem( FMOD::System** out_fmod_system )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		// Create FMOD
		fmod_result = FMOD::System_Create( out_fmod_system );
		ERROR_CHECK( fmod_result );

		// Init FMOD
		fmod_result = ( *out_fmod_system )->init( 32, FMOD_INIT_NORMAL, 0 );
		ERROR_CHECK( fmod_result );
	}
	void ReleaseSystem( FMOD::System** const out_fmod_system )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		// Close
		fmod_result = ( *out_fmod_system )->close();
		ERROR_CHECK( fmod_result );

		// Release
		fmod_result = ( *out_fmod_system )->release();
		ERROR_CHECK( fmod_result );
	}

	void PrintChannelInfo( FMOD::Channel* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool playing = false;
		bool paused = false;
		bool bLoop = false;
		float volume = 0.0f;

		if( fmod_channel )
		{
			fmod_result = fmod_channel->isPlaying( &playing );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}

			fmod_result = fmod_channel->getPaused( &paused );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}

			fmod_result = fmod_channel->getPosition( &ms, FMOD_TIMEUNIT_MS );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}

			FMOD::Sound* current_sound = nullptr;
			fmod_channel->getCurrentSound( &current_sound );
			if( current_sound )
			{
				fmod_result = current_sound->getLength( &lenms, FMOD_TIMEUNIT_MS );
				if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
				{
					R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
				}
			}

			FMOD_MODE fmod_mode = 0u;
			fmod_result = fmod_channel->getMode( &fmod_mode );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}
			bLoop = FMOD_LOOP_NORMAL & fmod_mode;

			fmod_result = fmod_channel->getVolume( &volume );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}

			
		}

		std::cout << "Length : " << lenms / 1000 / 60 << " : " << lenms / 1000 % 60 << " : " << lenms / 10 % 100 << r2::linefeed;
		std::cout << "Time : " << ms / 1000 / 60 << " : " << ms / 1000 % 60 << " : " << ms / 10 % 100 << r2::linefeed;
		std::cout << ( paused ? "Paused " : playing ? "Playing" : "Stopped" ) << r2::linefeed;
		std::cout << "Loop : " << ( bLoop ? "ON" : "OFF" ) << r2::linefeed;
		std::cout << "Volume : " << volume << r2::linefeed;
	}

	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system )
	{
		int channelsplaying = 0;
		fmod_system->getChannelsPlaying( &channelsplaying, NULL );

		std::cout << "Channels Playing : " << channelsplaying << r2::linefeed;
	}


	void ERROR_CHECK( const FMOD_RESULT fmod_result )
	{
		if( FMOD_OK != fmod_result )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}
	}
}