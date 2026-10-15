#pragma once

#include "File.hpp"

class FileContentsMap
{
protected:
    File* file;

public:
    inline FileContentsMap(File* file) : file(file) {}

    UniqueArray<char> GetValue(const char* key);
};