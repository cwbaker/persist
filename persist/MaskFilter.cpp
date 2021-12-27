//
// MaskFilter.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "MaskFilter.hpp"
#include <persist/assert.hpp>

using namespace persist;

MaskFilter::MaskFilter( const MaskFilter::Conversion* conversions )
: m_conversions( conversions )
, m_string()
{
    assert( m_conversions );
}

int MaskFilter::to_memory( const std::string& value, error::ErrorPolicy& /*error_policy*/ ) const
{
    const char* SEPARATORS = "| ";

    std::string::const_iterator begin = value.begin();
    std::string::const_iterator end = value.begin();
    while ( end != value.end() && !in(*end, SEPARATORS) )
    {
        ++end;
    }

    int mask = 0;
    while ( begin != value.end() )
    {
        const Conversion* conversion = m_conversions;
        while ( conversion->m_value != 0 && conversion->m_name && !compare(begin, end, conversion->m_name) )
        {
            ++conversion;
        }

        if ( conversion->m_name )
        {
            mask |= conversion->m_value;
        }

        begin = end != value.end() ? ++end : end;
        while ( end != value.end() && !in(*end, SEPARATORS) )
        {
            ++end;
        }
    }

    return mask;
}

const std::string& MaskFilter::to_archive( int value ) const
{
    m_string.clear();

    if ( value != 0 )
    {
        int mask = 0x01;
        while ( mask != 0 )
        {
            if ( (mask & value) != 0 )
            {
                const Conversion* conversion = m_conversions;
                while ( conversion->m_value != mask && conversion->m_name != 0 )
                {
                    ++conversion;
                }

                if ( conversion->m_name != 0 )
                {
                    if ( !m_string.empty() )
                    {
                        m_string += "|";
                    }

                    m_string += conversion->m_name;
                }
            }

            mask <<= 1;
        }
    }
    else
    {
        const Conversion* conversion = m_conversions;
        while ( conversion->m_value != 0 && conversion->m_name != 0 )
        {
            ++conversion;
        }

        if ( conversion->m_name != 0 )
        {
            m_string += conversion->m_name;
        }
    }

    return m_string;
}

MaskFilter persist::mask_filter( const MaskFilter::Conversion* conversions )
{
    return MaskFilter( conversions );
}

bool MaskFilter::in( int character, const char* separators )
{
    assert( separators );    
    const char* i = separators;
    while ( *i != '\0' && *i != character )
    {
        ++i;
    }
    return *i == character;
}

bool MaskFilter::compare( std::string::const_iterator begin, std::string::const_iterator end, const char* value )
{
    assert( value );    
    while ( begin != end && *value != '\0' && *begin == *value )
    {
        ++begin;
        ++value;
    }    
    return begin == end;
}
