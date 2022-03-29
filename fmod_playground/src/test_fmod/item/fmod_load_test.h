#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace fmod_load_test
{
	class Basic : public r2::iTest, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};



	class Memory : public r2::iTest, public r2::SingleTon<Memory>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}