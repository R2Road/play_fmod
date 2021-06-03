#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace fmod_basic_test
{
	class SystemCreateAndRelease : public r2::iTest, public r2::SingleTon<SystemCreateAndRelease>
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