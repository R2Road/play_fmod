#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class FMOD_Load_Menu
{
private:
	FMOD_Load_Menu() = delete;

public:
	static const char* GetTitle() { return "FMOD Load Menu"; };
	static r2cm::MenuUp Create( r2cm::Director& director );
};