#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace fmod_sound_analysis_test
{
	class Frequency : public r2::iTest, public r2::SingleTon<Frequency>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}