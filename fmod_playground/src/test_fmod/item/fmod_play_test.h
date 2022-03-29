#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace fmod_play_test
{
	class PlaySound : public r2::iTest, public r2::SingleTon<PlaySound>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PlayStream: public r2::iTest, public r2::SingleTon<PlayStream>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PlayAndCallback: public r2::iTest, public r2::SingleTon<PlayAndCallback>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VolumeControl : public r2::iTest, public r2::SingleTon<VolumeControl>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PositionControl : public r2::iTest, public r2::SingleTon<PositionControl>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}