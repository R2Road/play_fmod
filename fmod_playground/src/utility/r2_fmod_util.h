#pragma once

#include "fmod_common.h"

namespace FMOD
{
	class Channel;
	class ChannelControl;
	class Sound;
	class System;
}

namespace r2_fmod_util
{
	void CreateSystem( FMOD::System** out_fmod_system );
	void ReleaseSystem( FMOD::System** const out_fmod_system );

	// Copy from fmod api/core/example/common.h or common_platform.h
	void Common_LoadFileMemory( const char *name, void **buff, int *length );
	void Common_UnloadFileMemory( void *buff );

	void PrintSampleRateInfo( FMOD::System* const fmod_system );

	void PrintSoundInfo( FMOD::Channel* const fmod_channel );
	void PrintSoundInfo( FMOD::Sound* const fmod_sound );
	void PrintChannelInfo( FMOD::Channel* const fmod_channel );
	void PrintChannelVolumeInfo( FMOD::ChannelControl* const fmod_channel );
	void PrintChannelPitchInfo( FMOD::ChannelControl* const fmod_channel );
	void PrintChannelDSPClock( FMOD::ChannelControl* const fmod_channel );

	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system );



	void ERROR_CHECK( const FMOD_RESULT fmod_result );
}