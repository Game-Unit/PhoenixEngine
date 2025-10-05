#include "Debug.h"

#include <iostream>

void Core::Debug::Log(std::string log)
{
	std::cout << D_GREEN << log << D_RESET << std::endl;
}

void Core::Debug::LogWarning(std::string log)
{
	std::cout << D_YELLOW << log << D_RESET << std::endl;
}

void Core::Debug::LogError(std::string log)
{
	std::cout << D_RED << log << D_RESET << std::endl;
}

void Core::Debug::LogCustom(std::string log, const char color)
{
	std::cout << color << log << D_RESET << std::endl;
}
