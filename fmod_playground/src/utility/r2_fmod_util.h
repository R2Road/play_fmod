#pragma once

#include "fmod_common.h"

namespace FMOD
{
	class Channel;
	class ChannelControl;
	class System;
}

namespace r2_fmod_util
{
	void CreateSystem( FMOD::System** out_fmod_system );
	void ReleaseSystem( FMOD::System** const out_fmod_system );

	void PrintChannelInfo( FMOD::Channel* const fmod_channel );
	void PrintChannelVolumeInfo( FMOD::ChannelControl* const fmod_channel );
	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system );



	void ERROR_CHECK( const FMOD_RESULT fmod_result );
}