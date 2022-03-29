#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace fmod_play_test
{
	class PlaySound : public r2cm::iItem, public r2::SingleTon<PlaySound>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PlayStream: public r2cm::iItem, public r2::SingleTon<PlayStream>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PlayAndCallback: public r2cm::iItem, public r2::SingleTon<PlayAndCallback>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class VolumeControl : public r2cm::iItem, public r2::SingleTon<VolumeControl>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PositionControl : public r2cm::iItem, public r2::SingleTon<PositionControl>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}