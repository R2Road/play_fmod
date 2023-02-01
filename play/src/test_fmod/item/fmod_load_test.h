#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace fmod_load_test
{
	class LoadSound : public r2cm::iItem, public r2cm::SingleTon<LoadSound>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LoadStream : public r2cm::iItem, public r2cm::SingleTon<LoadStream>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Memory : public r2cm::iItem, public r2cm::SingleTon<Memory>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}