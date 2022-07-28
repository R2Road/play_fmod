#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace fmod_effect_test
{
	class Echo : public r2cm::iItem, public r2cm::SingleTon<Echo>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Fade : public r2cm::iItem, public r2cm::SingleTon<Fade>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FadeStartFadeEnd : public r2cm::iItem, public r2cm::SingleTon<FadeStartFadeEnd>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PitchControl : public r2cm::iItem, public r2cm::SingleTon<PitchControl>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}