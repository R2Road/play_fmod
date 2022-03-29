#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace fmod_channel_group_test
{
	class Basic : public r2::iTest, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};



	class Group : public r2::iTest, public r2::SingleTon<Group>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};



	class Volume : public r2::iTest, public r2::SingleTon<Volume>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}