//
// Attribute.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "Attribute.hpp"
#include <persist/assert.hpp>
#include <sstream>
#include <stddef.h>
#include <string.h>

using namespace persist;

Attribute::Attribute()
: m_name()
, m_type( TYPE_VOID )
, m_string()
{
    memset( &m_value, 0, sizeof(m_value) );
}

Attribute::Attribute( const std::string& name )
: m_name( name )
, m_type( TYPE_VOID )
, m_string()
{
    memset( &m_value, 0, sizeof(m_value) );
}

Attribute::Attribute( const std::string& name, const void* address )
: m_name( name )
, m_type( TYPE_ADDRESS )
, m_string()
{
    m_value.m_address = address;
}

Attribute::Attribute( const std::string& name, bool value )
: m_name( name )
, m_type( TYPE_BOOLEAN )
, m_string()
{
    m_value.m_boolean = value;
}

Attribute::Attribute( const std::string& name, int value )
: m_name( name )
, m_type( TYPE_INTEGER )
, m_string()
{
    m_value.m_integer = value;
}

Attribute::Attribute( const std::string& name, unsigned int value )
: m_name( name )
, m_type( TYPE_UNSIGNED_INTEGER )
, m_string()
{
    m_value.m_unsigned_integer = value;
}

Attribute::Attribute( const std::string& name, double value )
: m_name( name )
, m_type( TYPE_REAL )
, m_string()
{
    m_value.m_real = value;
}

Attribute::Attribute( const std::string& name, const std::string& value )
: m_name( name )
, m_type( TYPE_STRING )
, m_string( value )
{
    memset( &m_value, 0, sizeof(m_value) );
}

const std::string& Attribute::name() const
{
    return m_name;
}

BasicType Attribute::type() const
{
    return m_type;
}

const void* Attribute::address() const
{
    ptrdiff_t value = 0;
    
    switch ( m_type )
    {
        case TYPE_ADDRESS:
            value = reinterpret_cast<ptrdiff_t>( m_value.m_address );
            break;

        case TYPE_BOOLEAN:
            value = 0;
            break;

        case TYPE_INTEGER:
            value = static_cast<ptrdiff_t>( m_value.m_integer );
            break;

        case TYPE_UNSIGNED_INTEGER:
            value = static_cast<ptrdiff_t>( m_value.m_unsigned_integer );
            break;

        case TYPE_REAL:
            value = 0;
            break;

        case TYPE_STRING:
        {
            for ( unsigned int i = 0; i < m_string.size(); ++i )
            {
                unsigned int character = m_string[i];
                if ( character >= '0' && character <= '9' )
                {
                    value = (value << 4) | (character - '0');
                }
                else if ( character >= 'a' && character <= 'f' )
                {
                    value = (value << 4) | (character - 'a' + 10);
                }
                else if ( character >= 'A' && character <= 'F' )
                {
                    value = (value << 4) | (character - 'A' + 10);
                }
            }
            break;
        }

        default:
            assert( false );
            break;
    }

    return reinterpret_cast<void*>( value );
}

bool Attribute::boolean() const
{
    bool value = false;
    
    switch ( m_type )
    {
        case TYPE_ADDRESS:
            value = m_value.m_address != 0;
            break;

        case TYPE_BOOLEAN:
            value = m_value.m_boolean;
            break;

        case TYPE_INTEGER:
            value = m_value.m_integer != 0;
            break;

        case TYPE_UNSIGNED_INTEGER:
            value = m_value.m_unsigned_integer != 0;
            break;

        case TYPE_REAL:
            value = m_value.m_real != 0.0f;
            break;

        case TYPE_STRING:
            value = m_string == "true";
            break;

        default:
            assert( false );
            break;
    }

    return value;
}

int Attribute::integer() const
{
    int value = 0;
    
    switch ( m_type )
    {
        case TYPE_BOOLEAN:
            value = m_value.m_boolean ? 1 : 0;
            break;

        case TYPE_INTEGER:
            value = m_value.m_integer;
            break;

        case TYPE_UNSIGNED_INTEGER:
            value = static_cast<int>( m_value.m_unsigned_integer );
            break;

        case TYPE_REAL:
            value = static_cast<int>( m_value.m_real );
            break;

        case TYPE_STRING:
        {
            std::istringstream stream( m_string );
            stream >> value;
            break;
        }

        default:
            assert( false );
            break;
    }

    return value;
}

unsigned int Attribute::unsigned_integer() const
{
    unsigned int value = 0;
    
    switch ( m_type )
    {
        case TYPE_BOOLEAN:
            value = m_value.m_boolean ? 1 : 0;
            break;

        case TYPE_INTEGER:
            value = static_cast<unsigned int>( m_value.m_integer );
            break;

        case TYPE_UNSIGNED_INTEGER:
            value = m_value.m_unsigned_integer;
            break;

        case TYPE_REAL:
            assert( m_value.m_real >= 0.0 );
            value = static_cast<unsigned int>( m_value.m_real );
            break;

        case TYPE_STRING:
        {
            std::istringstream stream( m_string );
            stream >> value;
            break;
        }

        default:
            assert( false );
            break;
    }

    return value;
}

double Attribute::real() const
{
    double value = 0.0;

    switch ( m_type )
    {
        case TYPE_BOOLEAN:
            value = m_value.m_boolean ? 1.0 : 0.0;
            break;

        case TYPE_INTEGER:
            value = static_cast<double>( m_value.m_integer );
            break;

        case TYPE_UNSIGNED_INTEGER:
            value = static_cast<double>( m_value.m_unsigned_integer );
            break;

        case TYPE_REAL:
            value = m_value.m_real;
            break;

        case TYPE_STRING:
        {
            std::istringstream stream( m_string );
            stream >> value;
            break;
        }

        default:
            assert( false );
            break;
    }

    return value;
}

const std::string& Attribute::string() const
{
    switch ( m_type )
    {
        case TYPE_ADDRESS:
        {
            std::ostringstream stream( m_string );
            stream << m_value.m_address;
            break;
        }

        case TYPE_BOOLEAN:
            m_string = m_value.m_boolean ? "true" : "false";
            break;

        case TYPE_INTEGER:
        {
            std::ostringstream stream( m_string );
            stream << m_value.m_integer;
            break;
        }

        case TYPE_UNSIGNED_INTEGER:
        {
            std::ostringstream stream( m_string );
            stream << m_value.m_unsigned_integer;
            break;
        }

        case TYPE_REAL:
        {
            std::ostringstream stream( m_string );
            stream << m_value.m_real;
            break;
        }

        case TYPE_STRING:
            break;

        default:
            assert( false );
            break;
    }

    return m_string;
}

void Attribute::string( std::string* value ) const
{
    assert( value );

    switch ( m_type )
    {
        case TYPE_ADDRESS:
        {
            std::ostringstream stream;
            stream << m_value.m_address;
            *value = stream.str();
            break;
        }

        case TYPE_BOOLEAN:
            *value = m_value.m_boolean ? "true" : "false";
            break;

        case TYPE_INTEGER:
        {
            std::ostringstream stream;
            stream << m_value.m_integer;
            *value = stream.str();
            break;
        }

        case TYPE_UNSIGNED_INTEGER:
        {
            std::ostringstream stream;
            stream << m_value.m_unsigned_integer;
            *value = stream.str();
            break;
        }

        case TYPE_REAL:
        {
            std::ostringstream stream;
            stream << m_value.m_real;
            *value = stream.str();
            break;
        }

        case TYPE_STRING:
            *value = m_string;
            break;

        default:
            assert( false );
            break;
    }
}
