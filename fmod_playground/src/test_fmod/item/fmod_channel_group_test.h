#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace fmod_channel_group_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};



	class Group : public r2cm::iItem, public r2::SingleTon<Group>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};



	class Volume : public r2cm::iItem, public r2::SingleTon<Volume>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}