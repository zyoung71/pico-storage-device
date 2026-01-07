#include <storage/StorageDevice.h>

#include <string.h>

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
}

StorageDeviceStream& StorageDeviceStream::operator>>(char& c)
{
    c = storage_device->ReadCharacter();
    return *this;
}