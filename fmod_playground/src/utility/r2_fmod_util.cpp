#include "pch.h"
#include "r2_fmod_util.h"

#include <cstdio>
#include <iostream>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "r2/r2_Assert.h"

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



	void Common_LoadFileMemory( const char *name, void **buff, int *length )
	{
		FILE *file = NULL;
		fopen_s( &file, name, "rb" );

		fseek( file, 0, SEEK_END );
		long len = ftell( file );
		fseek( file, 0, SEEK_SET );

		void *mem = malloc( len );
		fread( mem, 1, len, file );

		fclose( file );

		*buff = mem;
		*length = len;
	}
	void Common_UnloadFileMemory( void *buff )
	{
		free( buff );
	}



	void PrintSampleRateInfo( FMOD::System* const fmod_system )
	{
		int sample_rate = 0u;

		if( fmod_system )
		{
			r2_fmod_util::ERROR_CHECK( fmod_system->getSoftwareFormat( &sample_rate, nullptr, nullptr ) );
		}

		std::cout << "Sample Rate : " << sample_rate << r2::linefeed;
	}



	void PrintSoundInfo( FMOD::Channel* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		FMOD::Sound* current_sound = nullptr;
		fmod_result = fmod_channel->getCurrentSound( &current_sound );
		r2_fmod_util::ERROR_CHECK( fmod_result );

		PrintSoundInfo( current_sound );
	}
	void PrintSoundInfo( FMOD::Sound* const fmod_sound )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		FMOD_SOUND_TYPE sound_type = FMOD_SOUND_TYPE::FMOD_SOUND_TYPE_UNKNOWN;
		FMOD_SOUND_FORMAT sound_format = FMOD_SOUND_FORMAT::FMOD_SOUND_FORMAT_NONE;
		int channels = 0;
		int bits = 0;

		if( fmod_sound )
		{
			fmod_result = fmod_sound->getFormat( &sound_type, &sound_format, &channels, &bits );
			r2_fmod_util::ERROR_CHECK( fmod_result );
		}

		std::cout << "Sound Type : " << sound_type << r2::linefeed;
		std::cout << "Sound Format : " << sound_format << r2::linefeed;
		std::cout << "Channels : " << channels << r2::linefeed;
		std::cout << "Bits : " << bits << r2::linefeed;
	}



	void PrintChannelInfo( FMOD::Channel* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool playing = false;
		bool paused = false;
		bool bLoop = false;

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
		}

		std::cout << ( paused ? "Paused " : ( playing ? "Playing" : "Stopped" ) ) << r2::linefeed;
		std::cout << "Loop : " << ( bLoop ? "ON" : "OFF" ) << r2::linefeed;
		
		PrintChannelTimeInfo( fmod_channel );
	}

	void PrintChannelTimeInfo( FMOD::Channel* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;

		unsigned int ms = 0;
		unsigned int lenms = 0;

		if( fmod_channel )
		{
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
		}

		std::cout << "Length : " << lenms / 1000 / 60 << " : " << lenms / 1000 % 60 << " : " << lenms / 10 % 100 << r2::linefeed;
		std::cout << "Time : " << ms / 1000 / 60 << " : " << ms / 1000 % 60 << " : " << ms / 10 % 100 << r2::linefeed;
	}
	void PrintChannelVolumeInfo( FMOD::ChannelControl* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
		float volume = 0.0f;

		if( fmod_channel )
		{
			fmod_result = fmod_channel->getVolume( &volume );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}
		}

		std::cout << "Volume : " << volume << r2::linefeed;
	}
	void PrintChannelPitchInfo( FMOD::ChannelControl* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
		float pitch = 0.0f;

		if( fmod_channel )
		{
			fmod_result = fmod_channel->getPitch( &pitch );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}
		}

		std::cout << "Pitch : " << pitch << r2::linefeed;
	}
	void PrintChannelDSPClock( FMOD::ChannelControl* const fmod_channel )
	{
		FMOD_RESULT fmod_result = FMOD_RESULT::FMOD_OK;
		unsigned long long dspclock = 0u;
		unsigned long long parent_dspclock = 0u;

		if( fmod_channel )
		{
			fmod_result = fmod_channel->getDSPClock( &dspclock, &parent_dspclock );
			if( ( fmod_result != FMOD_OK ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
			{
				R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
			}
		}

		std::cout << "DSP Clock : " << dspclock << r2::linefeed;
		std::cout << "Parent DSP Clock : " << parent_dspclock << r2::linefeed;
	}



	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system )
	{
		int channelsplaying = 0;
		fmod_system->getChannelsPlaying( &channelsplaying, NULL );

		std::cout << "Channels Playing : " << channelsplaying << r2::linefeed;
	}


	void ERROR_CHECK( const FMOD_RESULT fmod_result )
	{
		if( ( FMOD_OK != fmod_result ) && ( fmod_result != FMOD_ERR_INVALID_HANDLE ) && ( fmod_result != FMOD_ERR_CHANNEL_STOLEN ) )
		{
			R2ASSERT( false, FMOD_ErrorString( fmod_result ) );
		}
	}
}