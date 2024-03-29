#pragma once

namespace persist
{

/**
// @internal
//
// A simple filter that converts from strings of UCS-2 encoded characters in 
// memory to strings of UTF-8 encoded characters in an archive.
*/
class Ucs2CharFilter
{
public:
    void to_archive( const wchar_t* src_begin, const wchar_t* src_end, char* dest_begin, char* dest_end ) const;
    void to_memory( const char* src_begin, const char* src_end, wchar_t* dest_begin, wchar_t* dest_end ) const;
    unsigned int to_archive_length( const wchar_t* begin, const wchar_t* end ) const;
    unsigned int to_memory_length( const char* begin, const char* end ) const;
};

Ucs2CharFilter ucs2_char_filter();

}
