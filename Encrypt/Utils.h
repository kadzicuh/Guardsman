#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

namespace Utils
{
    VOID Readme(String path);
    BOOL DirectoryExists(String dir);
}

#endif // !UTILS_H_
