#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace test_basic
{
	class SystemCreateAndRelease : public r2cm::iItem, public r2cm::SingleTon<SystemCreateAndRelease>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class VersionCheck : public r2cm::iItem, public r2cm::SingleTon<VersionCheck>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}