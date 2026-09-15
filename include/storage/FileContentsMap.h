#pragma once

#include "StorageDevice.h"

class FileContentsMap
{
protected:
    StorageDevice* storage_dev;

public:
    inline FileContentsMap(StorageDevice* storage_dev) : storage_dev(storage_dev) {}

    UniqueArray<char> GetValueUTF8(const char* key);
    UniqueArray<char16_t> GetValueUTF16(const char16_t* key);
};