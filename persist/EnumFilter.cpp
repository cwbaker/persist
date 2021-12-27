//
// EnumFilter.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "EnumFilter.hpp"
#include "types.hpp"
#include <error/ErrorPolicy.hpp>
#include <assert/assert.hpp>
#include <stdlib.h>
#include <stdio.h>

#if defined(BUILD_OS_WINDOWS)
#define snprintf _snprintf
#endif

using namespace persist;

const persist::EnumFilter::Conversion persist::BASIC_TYPES[] =
{
    { TYPE_VOID, "void" },
    { TYPE_ADDRESS, "address" },
    { TYPE_BOOLEAN, "boolean" },
    { TYPE_INTEGER, "integer" },
    { TYPE_UNSIGNED_INTEGER, "unsigned_integer" },
    { TYPE_REAL, "real" },
    { TYPE_NUMBER, "number" },
    { TYPE_STRING, "string" },
    { TYPE_OBJECT, "object" },
    { -1, "void" }
};

EnumFilter::EnumFilter( const Conversion* conversions )
: m_conversions( conversions )
, m_string()
{
}

int EnumFilter::to_memory( const std::string& value, error::ErrorPolicy& error_policy ) const
{
    const Conversion* conversion = m_conversions;
    while ( conversion->m_name != 0 && value != conversion->m_name )
    {
        ++conversion;
    }

    if ( conversion->m_name == 0 )
    {
        error_policy.error( value.empty() || isalpha(value[0]), "Unable to find enumerated value for '%s'", value.empty() ? "" : value.c_str() );
        return !value.empty() ? atoi( value.c_str() ) : 0;
    }

    return conversion->m_value;
}

const std::string& EnumFilter::to_archive( int value ) const
{
    const Conversion* conversion = m_conversions;
    while ( conversion->m_name != 0 && conversion->m_value != value )
    {
        ++conversion;
    }

    if ( conversion->m_name != 0 )
    {
        m_string.assign( conversion->m_name );
    }
    else
    {
        char number [11];
        snprintf( number, sizeof(number), "%d", value );
        m_string.assign( number );
    }

    return m_string;
}

EnumFilter persist::enum_filter( const EnumFilter::Conversion* conversions )
{
    return EnumFilter( conversions );
}
