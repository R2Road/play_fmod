#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace test_basic
{
	class SystemCreateAndRelease : public r2cm::iItem, public r2::SingleTon<SystemCreateAndRelease>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class VersionCheck : public r2cm::iItem, public r2::SingleTon<VersionCheck>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}