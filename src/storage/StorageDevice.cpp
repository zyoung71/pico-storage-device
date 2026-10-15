#include <storage/StorageDevice.hpp>

#include <string.h>

uint32_t posix_to_fileaccess_mask(const char* posix)
{
    if (strncmp(posix, "r", 4) == 0)
        return READ;

    if (strncmp(posix, "r+", 4) == 0)
        return READ | WRITE;

    if (strncmp(posix, "w", 4) == 0)
        return CREATE_OVERWRITE | WRITE;

    if (strncmp(posix, "w+", 4) == 0)
        return CREATE_OVERWRITE | WRITE | READ;
    
    if (strncmp(posix, "a", 4) == 0)
        return OPEN_APPEND | WRITE;

    if (strncmp(posix, "a+", 4) == 0)
        return OPEN_APPEND | WRITE | READ;

    if (strncmp(posix, "wx", 4) == 0)
        return CREATE_NEW | WRITE;

    if (strncmp(posix, "w+x", 4) == 0)
        return CREATE_NEW | WRITE | READ;

    return OPEN_APPEND | WRITE | READ;
}