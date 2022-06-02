#include "Utils.h"

BOOL Utils::DirectoryExists(String dir)
{
    DWORD dwAttrib{ GetFileAttributes(dir.c_str()) };

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

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