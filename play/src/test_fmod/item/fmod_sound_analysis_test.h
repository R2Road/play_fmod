#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace fmod_sound_analysis_test
{
	class Frequency : public r2cm::iItem, public r2cm::SingleTon<Frequency>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}