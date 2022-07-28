#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class RootMenu
{
private:
	RootMenu() = delete;

public:
	static const char* GetTitle();
	static r2cm::MenuUp Create( r2cm::Director& director );
};