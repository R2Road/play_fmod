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
		FMOD_RESULT fmod_result;

		// Create FMOD
		fmod_result = FMOD::System_Create( out_fmod_system );
		if( FMOD_RESULT::FMOD_OK != fmod_result )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}

		// Init FMOD
		fmod_result = ( *out_fmod_system )->init( 32, FMOD_INIT_NORMAL, 0 );
		if( FMOD_RESULT::FMOD_OK != fmod_result )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}
	}
	void ReleaseSystem( FMOD::System** const out_fmod_system )
	{
		FMOD_RESULT fmod_result;

		// Close
		fmod_result = ( *out_fmod_system )->close();
		if( FMOD_RESULT::FMOD_OK != fmod_result )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}

		// Release
		fmod_result = ( *out_fmod_system )->release();
		if( FMOD_RESULT::FMOD_OK != fmod_result )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}
	}

	void PrintChannelInfo( FMOD::Channel* const fmod_channel )
	{
		FMOD_RESULT fmod_result;

		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool         playing = 0;
		bool         paused = 0;
		int          channelsplaying = 0;

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

			FMOD::Sound *currentsound = 0;

			fmod_channel->getCurrentSound( &currentsound );
			if( currentsound )
			{
				fmod_result = currentsound->getLength( &lenms, FMOD_TIMEUNIT_MS );
				if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
				{
					R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
				}
			}
		}

		std::cout << "Length : " << lenms / 1000 / 60 << " : " << lenms / 1000 % 60 << " : " << lenms / 10 % 100 << r2::linefeed;
		std::cout << "Time : " << ms / 1000 / 60 << " : " << ms / 1000 % 60 << " : " << ms / 10 % 100 << r2::linefeed;
		std::cout << ( paused ? "Paused " : playing ? "Playing" : "Stopped" ) << r2::linefeed;
		std::cout << "Channels Playing : " << channelsplaying << r2::linefeed;
	}

	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system )
	{
		int channelsplaying = 0;
		fmod_system->getChannelsPlaying( &channelsplaying, NULL );

		std::cout << "Channels Playing : " << channelsplaying << r2::linefeed;
	}
}