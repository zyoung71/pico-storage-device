#include "util/Char16.h"
#include <storage/FileContentsMap.h>

#include <cstring>

UniqueArray<char> FileContentsMap::GetValueUTF8(const char* key)
{
    if (storage_dev->IsFileOpen())
    {
        storage_dev->SeekStart();
        int64_t idx = storage_dev->FindNextStringUTF8(key);
        if (idx >= 0)
        {
            storage_dev->Seek(idx + strlen(key) + 1); // move past key and equals sign
            UniqueArray<char> ret;
            storage_dev->ReadLineUTF8(ret, false);
            return std::move(ret);
        }
    }
    return nullptr;
}

UniqueArray<char16_t> FileContentsMap::GetValueUTF16(const char16_t* key)
{
    if (storage_dev->IsFileOpen())
    {
        storage_dev->SeekStart();
        int64_t idx = storage_dev->FindNextStringUTF16(key);
        if (idx >= 0)
        {
            storage_dev->Seek(idx + strlen16(key) + 1); // move past key and equals sign
            UniqueArray<char16_t> ret;
            storage_dev->ReadLineUTF16(ret, false);
            return std::move(ret);
        }
    }
    return nullptr;
}