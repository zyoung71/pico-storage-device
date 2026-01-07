#include <storage/FileContentsMap.h>

#include <cstring>

UniqueArray<char> FileContentsMap::GetValue(const char* key)
{
    storage_dev->SeekStart();
    int64_t idx = storage_dev->FindNextString(key);
    if (idx >= 0)
    {
        storage_dev->Seek(idx + strlen(key) + 1); // move past key and equals sign
        UniqueArray<char> ret;
        storage_dev->ReadLine(ret, false);
        return std::move(ret);
    }
    return nullptr;
}