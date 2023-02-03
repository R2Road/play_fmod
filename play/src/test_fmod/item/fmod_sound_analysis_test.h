#pragma once

#include "r2cm/r2cm_iItem.h"

namespace fmod_sound_analysis_test
{
	class Frequency : public r2cm::iItem
	{
	public:
		r2cm::TitleFunctionT GetTitleFunction() const override;
		r2cm::DoFunctionT GetDoFunction() const override;
	};
}