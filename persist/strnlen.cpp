//
// strnlen.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "strnlen.hpp"
#include <persist/assert.hpp>

using namespace persist;

namespace persist
{

size_t strnlen( const char* string, size_t max )
{
    assert( string );
    const char* pos = string;
    const char* end = string + max;
    while ( pos < end && *pos != '\0' )
    {
        ++pos;
    }
    return pos - string;
}

size_t strnlen( const wchar_t* string, size_t max )
{
    assert( string );
    const wchar_t* pos = string;
    const wchar_t* end = string + max;
    while ( pos < end && *pos != L'\0' )
    {
        ++pos;
    }
    return pos - string;
}

}
