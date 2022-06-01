#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>
#include <vector>
#include <string>

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

namespace Utils
{
	void readme(String file);
}

#endif // !UTILS_H_
