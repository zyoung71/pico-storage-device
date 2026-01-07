#include <storage/StorageDevice.h>

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

StorageDeviceStream& StorageDeviceStream::InsertBuffer(const void* buffer, size_t length)
{
    storage_device->WriteBuffer(buffer, length);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(const BufferView<void>& buffer)
{
    storage_device->WriteBuffer(buffer.buffer, buffer.length);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(const ArrayAccessor<void>& buffer)
{
    storage_device->WriteBuffer(buffer.data, buffer.length);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(const char* strbuff)
{
    storage_device->WriteString(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char* strbuff)
{
    storage_device->WriteString(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char c)
{
    storage_device->WriteCharacter(c);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::ExtractBuffer(void* buffer, size_t length)
{
    storage_device->ReadBuffer(buffer, length);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator>>(ArrayAccessor<void>& buffer)
{
    storage_device->ReadBuffer(buffer.data, buffer.length);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator>>(char* strbuff)
{
    size_t len = strlen(strbuff);
    storage_device->ReadBuffer(strbuff, len);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator>>(char& c)
{
    c = storage_device->ReadCharacter();
    return *this;
}

bool StorageDevice::FindAndReplaceFirstBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (Seek(FindFirstBuffer(old_buffer, old_bytes)))
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool StorageDevice::FindAndReplaceFirstString(const char* old_str, const char* new_str)
{
    if (Seek(FindFirstString(old_str)))
    {
        return WriteString(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplaceFirstCharacter(char old_c, char new_c)
{
    if (Seek(FindFirstCharacter(old_c)))
    {
        return WriteCharacter(new_c);
    }
    return false;
}

bool StorageDevice::FindAndReplaceLastBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (Seek(FindLastBuffer(old_buffer, old_bytes)))
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool StorageDevice::FindAndReplaceLastString(const char* old_str, const char* new_str)
{
    if (Seek(FindLastString(old_str)))
    {
        return WriteString(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplaceLastCharacter(char old_c, char new_c)
{
    if (Seek(FindLastCharacter(old_c)))
    {
        return WriteCharacter(new_c);
    }
    return false;
}