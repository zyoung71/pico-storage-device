#include <storage/StorageDevice.h>
#include <util/Char16.h>

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
    storage_device->WriteStringUTF8(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(const char16_t* strbuff)
{
    storage_device->WriteStringUTF16(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char* strbuff)
{
    storage_device->WriteStringUTF8(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char16_t* strbuff)
{
    storage_device->WriteStringUTF16(strbuff);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char c)
{
    storage_device->WriteCharacterUTF8(c);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator<<(char16_t c)
{
    storage_device->WriteCharacterUTF16(c);
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

StorageDeviceStream& StorageDeviceStream::operator>>(char16_t* strbuff)
{
    size_t len = strlen16(strbuff);
    storage_device->ReadBuffer(strbuff, len * 2);
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator>>(char& c)
{
    c = storage_device->ReadCharacterUTF8();
    return *this;
}

StorageDeviceStream& StorageDeviceStream::operator>>(char16_t& c)
{
    c = storage_device->ReadCharacterUTF16();
    return *this;
}

bool StorageDevice::FindAndReplaceNextBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (FindNextBuffer(old_buffer, old_bytes, false) >= 0)
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool StorageDevice::FindAndReplaceNextStringUTF8(const char* old_str, const char* new_str)
{
    if (FindNextStringUTF8(old_str, false) >= 0)
    {
        return WriteStringUTF8(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplaceNextStringUTF16(const char16_t* old_str, const char16_t* new_str)
{
    if (FindNextStringUTF16(old_str, false) >= 0)
    {
        return WriteStringUTF16(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplaceNextCharacterUTF8(char old_c, char new_c)
{
    if (FindNextCharacterUTF8(old_c, false) >= 0)
    {
        return WriteCharacterUTF8(new_c);
    }
    return false;
}

bool StorageDevice::FindAndReplaceNextCharacterUTF16(char16_t old_c, char16_t new_c)
{
    if (FindNextCharacterUTF16(old_c, false) >= 0)
    {
        return WriteCharacterUTF16(new_c);
    }
    return false;
}

bool StorageDevice::FindAndReplacePreviousBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (FindPreviousBuffer(old_buffer, old_bytes, false) >= 0)
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool StorageDevice::FindAndReplacePreviousStringUTF8(const char* old_str, const char* new_str)
{
    if (FindPreviousStringUTF8(old_str, false) >= 0)
    {
        return WriteStringUTF8(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplacePreviousStringUTF16(const char16_t* old_str, const char16_t* new_str)
{
    if (FindPreviousStringUTF16(old_str, false) >= 0)
    {
        return WriteStringUTF16(new_str);
    }
    return false;
}

bool StorageDevice::FindAndReplacePreviousCharacterUTF8(char old_c, char new_c)
{
    if (FindPreviousCharacterUTF8(old_c, false) >= 0)
    {
        return WriteCharacterUTF8(new_c);
    }
    return false;
}

bool StorageDevice::FindAndReplacePreviousCharacterUTF16(char16_t old_c, char16_t new_c)
{
    if (FindPreviousCharacterUTF16(old_c, false) >= 0)
    {
        return WriteCharacterUTF16(new_c);
    }
    return false;
}