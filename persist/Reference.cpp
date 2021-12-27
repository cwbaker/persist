//
// Reference.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "Reference.hpp"

using namespace persist;

Reference::Reference( const void* address, void* reference, void (*resolve)(void* reference, void* raw_ptr, void* smart_ptr) )
: m_address( address )
, m_reference( reference )
, m_resolve( resolve )
{
}

const void* Reference::address() const
{
    return m_address;
}

void* Reference::reference() const
{
    return m_reference;
}

void Reference::resolve( void* raw_ptr, void* smart_ptr ) const
{
    if ( m_resolve )
    {
        (*m_resolve)( m_reference, raw_ptr, smart_ptr );
    }
}

bool Reference::operator<( const Reference& reference ) const
{
    return m_address < reference.m_address;
}
