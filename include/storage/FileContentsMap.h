#pragma once

#include "StorageDevice.h"

class FileContentsMap
{
protected:
    StorageDevice* storage_dev;

public:
    inline FileContentsMap(StorageDevice* storage_dev) : storage_dev(storage_dev) {}

    UniqueArray<char> GetValue(const char* key);
};