#pragma once

#include "r2_iTest.h"
#include "r2_Singleton.h"

namespace fmod_test
{
	class PlaySound : public r2::iTest, public r2::SingleTon<PlaySound>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}