#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace etc_test
{
	class Test1 : public r2::iTest, public r2::SingleTon<Test1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}