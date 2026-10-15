#pragma once

#include <cstdint>
#include <array>

#include <util/ArrayAccessor.hpp>
#include <util/BufferView.hpp>
#include <util/UniqueArray.hpp>

class File;

class FileStream
{
private:
    File* file;

public:
    inline FileStream(File* file) : file(file) {}
    FileStream(const FileStream&) = delete; // streams are meant to be accessed as references

    FileStream& InsertBuffer(const void* buffer, size_t len);
    FileStream& operator<<(const BufferView<void>& buffer);
    FileStream& operator<<(const ArrayAccessor<void>& buffer);
    FileStream& operator<<(const char* strbuff);
    FileStream& operator<<(char* strbuff);
    FileStream& operator<<(char c);

    template<typename T>
    FileStream& operator<<(const T& item)
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

    FileStream& ExtractBuffer(void* buffer, size_t length);
    FileStream& operator>>(ArrayAccessor<void>& buffer);
    FileStream& operator>>(char& c);

    template<size_t arr_size>
    FileStream& operator>>(std::array<char, arr_size>& strbuff);
};

class File
{
private:
    FileStream stream;

public:
    virtual ~File() = default;

    inline FileStream& GetStream()
    {
        return stream;
    }

    virtual uint64_t GetFileSize() const = 0;

    virtual bool Seek(uint64_t index) = 0;
    virtual bool SeekStart() = 0;
    virtual bool SeekEnd() = 0;
    virtual bool SeekStep(int64_t d_index) = 0;

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

    virtual int64_t FindNextBuffer(const void* buffer, size_t max_bytes, bool keep_index = true) = 0;
    virtual int64_t FindNextString(const char* str, bool keep_index = true) = 0;
    virtual int64_t FindNextCharacter(char c, bool keep_index = true) = 0;

    virtual int64_t FindPreviousBuffer(const void* buffer, size_t max_bytes, bool keep_index = true) = 0;
    virtual int64_t FindPreviousString(const char* str, bool keep_index = true) = 0;
    virtual int64_t FindPreviousCharacter(char c, bool keep_index = true) = 0;

    bool FindAndReplaceNextBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes);
    bool FindAndReplaceNextString(const char* old_str, const char* new_str);
    bool FindAndReplaceNextCharacter(char old_c, char new_c);

    bool FindAndReplacePreviousBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes);
    bool FindAndReplacePreviousString(const char* old_str, const char* new_str);
    bool FindAndReplacePreviousCharacter(char old_c, char new_c);

    virtual bool ClearFile(uint64_t begin_index, uint64_t end_index) = 0;
    virtual bool ClearFile(uint64_t begin_index = 0) = 0;

    virtual bool Delete() = 0;
    virtual void Close() = 0;

    virtual bool IsFileOpen() const = 0;
};

template<size_t arr_size>
FileStream& FileStream::operator>>(std::array<char, arr_size>& strbuff)
{
    file->ReadBuffer(strbuff.data(), arr_size);
}