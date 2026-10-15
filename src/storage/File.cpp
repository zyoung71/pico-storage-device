#include <storage/File.hpp>

FileStream& FileStream::InsertBuffer(const void* buffer, size_t length)
{
    file->WriteBuffer(buffer, length);
    return *this;
}

FileStream& FileStream::operator<<(const BufferView<void>& buffer)
{
    file->WriteBuffer(buffer.buffer, buffer.length);
    return *this;
}

FileStream& FileStream::operator<<(const ArrayAccessor<void>& buffer)
{
    file->WriteBuffer(buffer.data, buffer.length);
    return *this;
}

FileStream& FileStream::operator<<(const char* strbuff)
{
    file->WriteString(strbuff);
    return *this;
}

FileStream& FileStream::operator<<(char* strbuff)
{
    file->WriteString(strbuff);
    return *this;
}

FileStream& FileStream::operator<<(char c)
{
    file->WriteCharacter(c);
    return *this;
}

FileStream& FileStream::ExtractBuffer(void* buffer, size_t length)
{
    file->ReadBuffer(buffer, length);
    return *this;
}

FileStream& FileStream::operator>>(ArrayAccessor<void>& buffer)
{
    file->ReadBuffer(buffer.data, buffer.length);
    return *this;
}

FileStream& FileStream::operator>>(char& c)
{
    c = file->ReadCharacter();
    return *this;
}

bool File::FindAndReplaceNextBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (FindNextBuffer(old_buffer, old_bytes, false) >= 0)
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool File::FindAndReplaceNextString(const char* old_str, const char* new_str)
{
    if (FindNextString(old_str, false) >= 0)
    {
        return WriteString(new_str);
    }
    return false;
}

bool File::FindAndReplaceNextCharacter(char old_c, char new_c)
{
    if (FindNextCharacter(old_c, false) >= 0)
    {
        return WriteCharacter(new_c);
    }
    return false;
}

bool File::FindAndReplacePreviousBuffer(const void* old_buffer, const void* new_buffer, size_t old_bytes, size_t new_bytes)
{
    if (FindPreviousBuffer(old_buffer, old_bytes, false) >= 0)
    {
        return WriteBuffer(new_buffer, new_bytes);
    }
    return false;
}

bool File::FindAndReplacePreviousString(const char* old_str, const char* new_str)
{
    if (FindPreviousString(old_str, false) >= 0)
    {
        return WriteString(new_str);
    }
    return false;
}

bool File::FindAndReplacePreviousCharacter(char old_c, char new_c)
{
    if (FindPreviousCharacter(old_c, false) >= 0)
    {
        return WriteCharacter(new_c);
    }
    return false;
}