#pragma once

#include <util/ArrayAccessor.h>
#include <util/BufferView.h>
#include <util/UniqueArray.h>

class StorageDevice;

class StorageDeviceStream
{
private:
    StorageDevice* storage_device;

public:
    inline StorageDeviceStream(StorageDevice* storage_device) : storage_device(storage_device) {}

    StorageDeviceStream& InsertBuffer(const void* buffer, size_t len);
    StorageDeviceStream& operator<<(const BufferView<void>& buffer);
    StorageDeviceStream& operator<<(const ArrayAccessor<void>& buffer);
    StorageDeviceStream& operator<<(const char* strbuff);
    StorageDeviceStream& operator<<(char* strbuff);
    StorageDeviceStream& operator<<(char c);

    template<typename T>
    StorageDeviceStream& operator<<(const T& item)
    {
        char buff[32];
        if constexpr (std::is_same_v<T, int64_t>)
            snprintf(buff, 32, "%lli", item);
        else if constexpr (std::is_same_v<T, uint64_t>)
            snprintf(buff, 32, "%llu", item);
        else if constexpr (std::is_unsigned_v<T>)
            snprintf(buff, 32, "%u", item);
        else if constexpr (std::is_integral_v<T>)
            snprintf(buff, 32, "%d", item);
        else if constexpr (std::is_floating_point_v<T>)
            snprintf(buff, 32, "%f", item);
        else
            snprintf(buff, 32, "%s", item);

        buff[31] = '\0';
        *this << (char*)buff;

        return *this;
    }

    StorageDeviceStream& ExtractBuffer(void* buffer, size_t length);
    StorageDeviceStream& operator>>(ArrayAccessor<void>& buffer);
    StorageDeviceStream& operator>>(char* strbuff);
    StorageDeviceStream& operator>>(char& c);
};

struct DirectoryEntry
{
    char name[256];
    uint32_t attributes_mask;
    bool is_directory;
};

enum FileAccess
{
    READ = 1 << 0,
    WRITE = 1 << 1,
    OPEN_EXISTING = 1 << 2,
    CREATE_OVERWRITE = 1 << 3,
    CREATE_NEW = 1 << 4,
    OPEN_OVERWRITE = 1 << 5,
    OPEN_APPEND = 1 << 6
};

uint32_t posix_to_fileaccess_mask(const char* posix);

class StorageDevice
{
protected:
    StorageDeviceStream stream;

    bool is_file_open = false;
    bool is_mounted = false;

    virtual uint32_t TranslateFileAccessFlags(FileAccess access) = 0;

public:
    inline StorageDevice() : stream(this) {}
    virtual ~StorageDevice() = default;

    virtual UniqueArray<DirectoryEntry> PeekDirectory(const char* dir_path) = 0;
    virtual size_t GetTotalCountInDirectory(const char* dir_path) = 0;
    virtual size_t GetFileCountInDirectory(const char* dir_path) = 0;
    virtual size_t GetDirectoryCountInDirectory(const char* dir_path) = 0;
    virtual DirectoryEntry GetDirectoryEntry(const char* path) = 0;

    virtual bool ChangeDirectory(const char* path) = 0;
    virtual bool CreateDirectory(const char* dir_path) = 0;
    virtual bool Move(const char* path, const char* new_path) = 0; // Move and Rename do the same thing
    virtual bool Rename(const char* name, const char* new_name) = 0;

    virtual bool Mount() = 0;
    virtual bool Unmount() = 0;
    virtual bool OpenFile(const char* file_path, uint8_t permissions_mask) = 0;
    virtual bool CloseFile() = 0;
    
    virtual bool Seek(uint64_t index) = 0;
    virtual bool SeekStart() = 0;
    virtual bool SeekEnd() = 0;
    virtual bool SeekStep(int64_t d_index) = 0;

    virtual uint64_t GetFileSize(const char* path) const = 0;
    virtual uint64_t GetFileSize() const = 0;
    virtual uint64_t GetFreeSpace() const = 0;
    virtual uint64_t GetTotalSpace() const = 0;
    virtual float GetSpaceUsedPercentage() const = 0;

    virtual size_t ReadBuffer(void* buffer, size_t max_bytes) = 0;
    virtual char ReadCharacter() = 0;
    virtual size_t ReadAll(UniqueArray<char>& buffer) = 0;
    virtual size_t ReadLine(UniqueArray<char>& buffer, bool from_start_of_line = false) = 0;

    virtual size_t WriteBuffer(const void* buffer, size_t max_bytes) = 0;
    virtual size_t WriteString(const char* str) = 0;
    virtual size_t WriteCharacter(char c) = 0;

    virtual size_t AppendBuffer(const void* buffer, size_t max_bytes, bool keep_index = true) = 0;
    virtual size_t AppendString(const char* str, bool keep_index = true) = 0;
    virtual size_t AppendCharacter(char c, bool keep_index = true) = 0;

    virtual size_t FindFirstBuffer(const void* buffer, size_t max_bytes) = 0;
    virtual size_t FindFirstString(const char* str) = 0;
    virtual size_t FindFirstCharacter(char c) = 0;
    virtual size_t FindLastBuffer(const void* buffer, size_t max_bytes) = 0;
    virtual size_t FindLastString(const char* str) = 0;
    virtual size_t FindLastCharacter(char c) = 0;

    bool FindAndReplaceFirstBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes);
    bool FindAndReplaceFirstString(const char* old_str, const char* new_str);
    bool FindAndReplaceFirstCharacter(char old_c, char new_c);
    bool FindAndReplaceLastBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes);
    bool FindAndReplaceLastString(const char* old_str, const char* new_str);
    bool FindAndReplaceLastCharacter(char old_c, char new_c);

    virtual bool ClearFile(uint64_t begin_index, uint64_t end_index) = 0;
    virtual bool ClearFile(uint64_t begin_index = 0) = 0;

    virtual bool Delete(const char* file_path) = 0;
    virtual bool Delete() = 0;

    inline bool IsFileOpen() const
    {
        return is_file_open;
    }
    inline bool IsMounted() const
    {
        return is_mounted;
    }
    
    virtual bool Exists(const char* path) const = 0;

    inline StorageDeviceStream& GetStream()
    {
        return stream;
    }
};