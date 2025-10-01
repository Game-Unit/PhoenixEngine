#include "Debug.h"

#include <iostream>

void Core::Debug::Log(std::string log)
{
	std::cout << GREEN << log << RESET << std::endl;
}

void Core::Debug::LogWarning(std::string log)
{
	std::cout << YELLOW << log << RESET << std::endl;
}

void Core::Debug::LogError(std::string log)
{
	std::cout << RED << log << RESET << std::endl;
}

void Core::Debug::LogCustom(std::string log, const char color)
{
	std::cout << color << log << RESET << std::endl;
}
