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


#include "SearchEngine.h"

std::vector<String> ext
{
    _T("Guardsman")
};

VOID SearchEngine::FindFile(String dir)
{
    dir += _T("\\");
    WIN32_FIND_DATA FindData;
    HANDLE hFind{ FindFirstFile((dir + _T("*")).c_str(), &FindData) };

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!lstrcmp(FindData.cFileName, _T(".")) ||
                !lstrcmp(FindData.cFileName, _T("..")) ||
                FindData.cFileName[0] == _T('.'))
                continue;

            String Path{ dir + FindData.cFileName };

            if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
                if (Utils::Contains(ext, Utils::GetFileExt(Path)))
                {
                    //Utils::Decrypt(key, iv, Path);
                    //DeleteFile(Path.c_str());
                }

            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
                FindFile(Path);
        } while (FindNextFile(hFind, &FindData));

        FindClose(hFind);
    }
}

VOID SearchEngine::Start()
{
    /*
        TCHAR username[UNLEN + 1];
        DWORD dwSize{ UNLEN + 1 };

        GetUserName(username, &dwSize);

        std::vector<String> drives
        {
            _T("C:\\Users\\") + String(username),
            _T("K:"), _T("L:"), _T("M:"), _T("N:"), _T("O:"),
            _T("D:"), _T("A:"), _T("B:"), _T("F:"), _T("Q:"),
            _T("G:"), _T("H:"), _T("R:"), _T("S:"), _T("J:"),
            _T("U:"), _T("W:"), _T("V:"), _T("X:"), _T("T:"),
            _T("Y:"), _T("Z:"), _T("E:"), _T("P:"), _T("I:")
        };
    */

    std::vector<String> drives{ Utils::GetLogicalDrives() };

    for (const auto& drive : drives)
        if (std::filesystem::exists(drive))
            if (GetDriveType(drive.c_str()) == DRIVE_FIXED ||
                GetDriveType(drive.c_str()) == DRIVE_REMOVABLE ||
                GetDriveType(drive.c_str()) == DRIVE_REMOTE ||
                GetDriveType(drive.c_str()) == DRIVE_NO_ROOT_DIR)
                FindFile(drive);
}