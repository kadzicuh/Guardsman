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


#include "Utils.h"

String Utils::UserName()
{
    TCHAR dataBuffer[UNLEN + 1];
    DWORD dwSize{ UNLEN + 1 };

    GetUserName(dataBuffer, &dwSize);
    return String(dataBuffer);
}

String Utils::GetFileExt(String file)
{
    return file.substr(file.find_last_of(_T(".")) + 1);
}

BOOL Utils::Contains(const std::vector<String>& v, String ext)
{
    if (std::find(v.begin(), v.end(), ext) != v.end())
        return TRUE;
    else
        return FALSE;
}

VOID Utils::Decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv, String file)
{
    std::ifstream in(file, std::ios::binary);
    std::ofstream out(file.substr(0, file.find_last_of(_T("."))), std::ios::binary);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption cipher;
    cipher.SetKeyWithIV(key, key.size(), iv);

    CryptoPP::FileSource f(in, true,
        new CryptoPP::StreamTransformationFilter(cipher,
            new CryptoPP::FileSink(out)));
}