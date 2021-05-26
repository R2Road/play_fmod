#pragma once

#include "r2_iTest.h"
#include "r2_Singleton.h"

namespace fmod_test
{
	class Basic : public r2::iTest, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VersionCheck : public r2::iTest, public r2::SingleTon<VersionCheck>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}