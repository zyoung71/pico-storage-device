#pragma once

#include "File.hpp"
#include <memory>

struct DirectoryEntry
{
    char name[256];
    uint64_t file_size;
    uint32_t date_modified;
    uint32_t time_modified;
    bool is_readonly; // i dont like using individual booleans but i dont have a choice if i wanna keep compatibility
    bool is_hidden;
    bool is_system;
    bool is_archive;
    bool is_directory;
};

enum FileAccess
{
    READ = 1 << 0,
    WRITE = 1 << 1,
    OPEN_EXISTING = 1 << 2,
    OPEN_OVERWRITE = 1 << 3,
    OPEN_APPEND = 1 << 4,
    CREATE_NEW = 1 << 5,
    CREATE_OVERWRITE = 1 << 6
};

uint32_t posix_to_fileaccess_mask(const char* posix);

class StorageDevice
{
public:
    virtual ~StorageDevice() = default;

    virtual UniqueArray<DirectoryEntry> PeekDirectory(const char* dir_path) const = 0;
    virtual size_t GetTotalCountInDirectory(const char* dir_path) const = 0;
    virtual size_t GetFileCountInDirectory(const char* dir_path) const = 0;
    virtual size_t GetDirectoryCountInDirectory(const char* dir_path) const = 0;
    virtual DirectoryEntry GetDirectoryEntry(const char* path) const = 0;

    virtual bool ChangeDirectory(const char* path) = 0;
    virtual bool CreateDirectory(const char* dir_path) = 0;
    virtual bool Move(const char* path, const char* new_path) = 0; // Move and Rename do the same thing
    virtual bool Rename(const char* name, const char* new_name) = 0;

    virtual bool Mount() = 0;
    virtual bool Unmount() = 0;
    virtual bool IsMounted() const = 0;

    virtual std::unique_ptr<File> OpenFile(const char* file_path, uint32_t access_mask) = 0;
    
    virtual bool Exists(const char* path) const = 0;

    virtual uint64_t GetFileSize(const char* path) const = 0;
    virtual uint64_t GetFreeSpace() const = 0;
    virtual uint64_t GetTotalSpace() const = 0;
    virtual float GetSpaceUsedPercentage() const = 0;

    virtual bool Delete(const char* file_path) = 0;

    inline static void CloseFile(const std::unique_ptr<File>& file)
    {
        file->Close();
    }
    
};