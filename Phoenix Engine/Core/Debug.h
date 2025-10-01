#pragma once

#include <string>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

namespace Core
{

	class Debug
	{
	public:
		static void Log(std::string log);
		static void LogWarning(std::string log);
		static void LogError(std::string log);
		static void LogCustom(std::string log, const char color);
	};

}