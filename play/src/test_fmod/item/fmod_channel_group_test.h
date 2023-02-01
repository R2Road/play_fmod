#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace fmod_channel_group_test
{
	class Basic : public r2cm::iItem, public r2cm::SingleTon<Basic>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};



	class Group : public r2cm::iItem, public r2cm::SingleTon<Group>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};



	class Volume : public r2cm::iItem, public r2cm::SingleTon<Volume>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}