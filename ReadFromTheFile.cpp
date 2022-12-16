#include <iostream>
#include <string>
#include <fstream>

size_t GetSizeOfFile(const std::wstring& path)
{
    struct _stat fileinfo;
    _wstat(path.c_str(), &fileinfo);
    return fileinfo.st_size;
}

std::wstring LoadUtf8FileToString(const std::wstring& filename)
{
    // stores file contents
    std::wstring buffer;            
    FILE* f = _wfopen(filename.c_str(), L"rtS, ccs=UTF-8");

    // Failed to open file
    if (f == NULL)
    {
        // ...handle some error...
        std::wcout << L"Проверьте местонахождения файла с вопросами.\nФайд должен находится рядом с " << "\n";
        return buffer;
    }

    size_t filesize = GetSizeOfFile(filename);

    // Read entire file contents in to memory
    if (filesize > 0)
    {
        buffer.resize(filesize);
        size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
        buffer.resize(wchars_read);
        buffer.shrink_to_fit();
    }

    fclose(f);

    return buffer;
}

int main()
{   
    setlocale(LC_ALL, "Russian");
    std::wstring mytext = LoadUtf8FileToString(L"Questions.txt");
    std::wcout << mytext << "\n";
    std::cin.get();
    return 0;
}