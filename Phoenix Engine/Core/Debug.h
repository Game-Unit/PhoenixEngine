#pragma once

#include <string>

#define D_RESET   "\033[0m"
#define D_GREEN   "\033[32m"
#define D_YELLOW  "\033[33m"
#define D_RED     "\033[31m"

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