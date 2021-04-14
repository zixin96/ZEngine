#pragma once

#include <string>

namespace ZZX
{
	class FileDialogs
	{
	public:
		// these return empty string if canceled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}
