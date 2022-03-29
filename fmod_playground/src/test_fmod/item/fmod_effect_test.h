#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace fmod_effect_test
{
	class Echo : public r2cm::iItem, public r2::SingleTon<Echo>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Fade : public r2cm::iItem, public r2::SingleTon<Fade>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class FadeStartFadeEnd : public r2cm::iItem, public r2::SingleTon<FadeStartFadeEnd>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PitchControl : public r2cm::iItem, public r2::SingleTon<PitchControl>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}