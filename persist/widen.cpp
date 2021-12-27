//
// widen.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "functions.hpp"
#include <persist/assert.hpp>
#include <vector>

using namespace persist;

// Disable the warning about unsafe use of std::ctype::narrow in the following
// two functions.
#ifdef _MSC_VER
#pragma warning( disable: 4996 )
#endif

namespace persist
{

std::wstring widen( const std::string& narrow_string, const std::locale& locale )
{
    if ( narrow_string.empty() )
    {
        return std::wstring();
    }

    size_t length = narrow_string.length();
    std::vector<wchar_t> buffer( length );    
    const std::ctype<wchar_t>* ctype = &std::use_facet<std::ctype<wchar_t> >( locale );
    ctype->widen( narrow_string.c_str(), narrow_string.c_str() + length, &buffer[0] );
    return std::wstring( &buffer[0], length );    
}

std::wstring widen( const wchar_t* wide_string, const std::locale& /*locale*/ )
{
    assert( wide_string );
    return std::wstring( wide_string );
}

}
