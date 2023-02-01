#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class FMOD_Play_Menu
{
private:
	FMOD_Play_Menu() = delete;

public:
	static const char* GetTitle() { return "FMOD Play Menu"; };
	static r2cm::MenuUp Create( r2cm::Director& director );
};