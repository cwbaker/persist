//
// TextWriter.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "Writer.ipp"
#include <persist/assert.hpp>
#include <string.h>

namespace persist
{

template <class Type> 
void TextWriter::write( const char* name, Type& object )
{
    m_element.clear();
    reset();

    assert( m_state.empty() );
    m_state.push( State(&m_element, MODE_VALUE, &object) );
    save( *this, MODE_VALUE, name, object );
    m_state.pop();
    assert( m_state.empty() );
}

template <class Type> 
void TextWriter::write( const char* name, const char* child_name, Type& container )
{
    m_element.clear();
    reset();

    assert( m_state.empty() );
    m_state.push( State(&m_element, MODE_VALUE, &container) );
    save( *this, MODE_VALUE, name, child_name, container );
    m_state.pop();
    assert( m_state.empty() );
}

template <class Type, size_t LENGTH> 
void TextWriter::write( const char* name, const char* child_name, Type (& values)[LENGTH] )
{
    m_element.clear();
    reset();

    assert( m_state.empty() );
    m_state.push( State(&m_element, MODE_VALUE, nullptr) );
    save( *this, MODE_VALUE, name, child_name, values, LENGTH );
    m_state.pop();
    assert( m_state.empty() );
}

template <class Filter> 
void TextWriter::value( const char* name, wchar_t* value, size_t /*max*/, const Filter& filter )
{
    TextWriter::value( name, filter.to_archive(std::wstring(value)) );
}

template <class Filter> 
void TextWriter::value( const char* name, std::wstring& value, const Filter& filter )
{
    TextWriter::value( name, filter.to_archive(value) );
}

template <class Filter> 
void TextWriter::value( const char* name, char* value, size_t /*max*/, const Filter& filter )
{
    TextWriter::value( name, filter.to_archive(std::string(value, strlen(value))) );
}

template <class Filter> 
void TextWriter::value( const char* name, std::string& value, const Filter& filter )
{
    std::string filtered_value = filter.to_archive( value );
    TextWriter::value( name, filtered_value );
}

template <class Type, class Filter> 
void TextWriter::value( const char* name, Type& value, const Filter& filter )
{
    assert( name );
    if ( get_mode() != MODE_REFERENCE )
    {
        std::string text_value = filter.to_archive(static_cast<int>(value)).c_str();
        get_current_element()->add_attribute( Attribute(name, text_value) );
    }
}

template <class Type> 
void TextWriter::value( const char* name, Type& object )
{
    assert( name );
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, name, object );
    }
}

template <class Type> 
void TextWriter::refer( const char* name, Type& object )
{
    assert( name );
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, name, object );
    }
}

template <class Type> 
void TextWriter::value( const char* name, const char* child_name, Type& container )
{
    assert( name );
    assert( child_name );
    
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, name, child_name, container );
    }
}

template <class Type> 
void TextWriter::refer( const char* name, const char* child_name, Type& container )
{
    assert( name );
    assert( child_name );

    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, name, child_name, container );        
    }
}

template <class Type, size_t LENGTH> 
void TextWriter::value( const char* name, const char* child_name, Type (& values)[LENGTH] )
{
    assert( name );
    assert( child_name );

    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, name, child_name, values, LENGTH );
    }
}

template <class Type, size_t LENGTH> 
void TextWriter::refer( const char* name, const char* child_name, Type (& values)[LENGTH] )
{
    assert( name );
    assert( child_name );

    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, name, child_name, values, LENGTH );
    }
}

}
