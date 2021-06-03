#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace fmod_effect_test
{
	class Echo : public r2::iTest, public r2::SingleTon<Echo>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}