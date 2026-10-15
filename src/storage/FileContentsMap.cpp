#include <storage/FileContentsMap.hpp>

#include <cstring>

UniqueArray<char> FileContentsMap::GetValue(const char* key)
{
    if (file->IsFileOpen())
    {
        file->SeekStart();
        int64_t idx = file->FindNextString(key);
        if (idx >= 0)
        {
            file->Seek(idx + strlen(key) + 1); // move past key and equals sign
            UniqueArray<char> ret;
            file->ReadLine(ret, false);
            return std::move(ret);
        }
    }
    return nullptr;
}