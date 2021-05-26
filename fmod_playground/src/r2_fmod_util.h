#pragma once

namespace FMOD
{
	class Channel;
	class System;
}

namespace r2_fmod_util
{
	void PrintChannelInfo( FMOD::Channel* const fmod_channel );
	void PrintChannelsPlayingInfo( FMOD::System* const fmod_system );
}