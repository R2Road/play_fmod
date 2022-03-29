#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace fmod_sound_analysis_test
{
	class Frequency : public r2cm::iItem, public r2::SingleTon<Frequency>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}