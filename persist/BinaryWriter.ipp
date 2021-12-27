#pragma once

#include "BinaryWriter.hpp"
#include "basic_types.ipp"
#include "arrays.ipp"
#include "objects.ipp"
#include "pointers.ipp"
#include "void_pointers.ipp"
#include "strings.ipp"
#include "functions.ipp"
#include <persist/assert.hpp>
#include <fstream>
#include <string.h>

namespace persist
{

template <class Char, class Type> 
void BinaryWriter::write( const Char* filename, const Char* name, Type& object )
{
    assert( filename );
    set_filename( widen(filename) );
    std::ofstream stream( filename, std::ios::binary );
    write( stream, name, object );
}

template <class Char, class Type> 
void BinaryWriter::write( const Char* filename, const Char* name, const Char* child_name, Type& container )
{
    assert( filename );
    set_filename( widen(filename) );
    write( std::ofstream(filename, std::ios::binary), name, child_name, container );
}

template <class Char, class Type, size_t LENGTH> 
void BinaryWriter::write( const Char* filename, const Char* name, const Char* child_name, Type (& values)[LENGTH] )
{
    assert( filename );
    set_filename( widen(filename) );
    write( std::ofstream(filename, std::ios::binary), name, child_name, values );
}

template <class Char, class Type> 
void BinaryWriter::write( std::ostream& ostream, const Char* /*name*/, Type& object )
{
    reset();
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE) );
    m_ostream = &ostream;
    ostream.exceptions( std::ostream::badbit | std::ostream::failbit );

    save( *this, MODE_VALUE, 0, object );
    object.exit( *this );

    m_ostream = NULL;
    m_state.pop();
    assert( m_state.empty() );
}

template <class Char, class Type> 
void BinaryWriter::write( std::ostream& ostream, const Char* /*name*/, const Char* /*child_name*/, Type& container )
{
    reset();
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE) );
    m_ostream = &ostream;
    ostream.exceptions( std::ostream::badbit | std::ostream::failbit );

    save( *this, MODE_VALUE, 0, 0, container );

    m_ostream = NULL;
    m_state.pop();
    assert( m_state.empty() );
}

template <class Char, class Type, size_t LENGTH> 
void BinaryWriter::write( std::ostream& ostream, const Char* /*name*/, const Char* /*child_name*/, Type (& values)[LENGTH] )
{
    reset();
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE) );
    m_ostream = &ostream;
    ostream.exceptions( std::ostream::badbit | std::ostream::failbit );

    save( *this, MODE_VALUE, 0, 0, values, LENGTH );

    m_ostream = NULL;
    m_state.pop();
    assert( m_state.empty() );
}

template <class Filter> 
void BinaryWriter::value( const char* /*name*/, wchar_t* value, size_t /*max*/, const Filter& filter )
{
    BinaryWriter::value( NULL, filter.to_archive(std::wstring(value, wcslen(value))) );
}

template <class Filter> 
void BinaryWriter::value( const char* /*name*/, std::wstring& value, const Filter& filter )
{
    BinaryWriter::value( NULL, filter.to_archive(value) );
}

template <class Filter> 
void BinaryWriter::value( const char* /*name*/, char* value, size_t /*max*/, const Filter& filter )
{
    BinaryWriter::value( NULL, filter.to_archive(std::string(value, strlen(value))) );
}

template <class Filter> 
void BinaryWriter::value( const char* /*name*/, std::string& value, const Filter& filter )
{
    BinaryWriter::value( NULL, filter.to_archive(value) );
}

template <class Type, class Filter>
void BinaryWriter::value( const char* /*name*/, Type& value, const Filter& /*filter*/ )
{
    assert( m_ostream );

    if ( get_mode() != MODE_REFERENCE )
    {
        m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
    }
}

template <class Type> 
void BinaryWriter::value( const char* /*name*/, Type& object )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, 0, object );
    }
}

template <class Type> 
void BinaryWriter::refer( const char* /*name*/, Type& object )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, 0, object );
    }
}

template <class Type> 
void BinaryWriter::value( const char* /*name*/, const char* /*child_name*/, Type& container )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, 0, 0, container );
    }
}

template <class Type> 
void BinaryWriter::refer( const char* /*name*/, const char* /*child_name*/, Type& container )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, 0, 0, container );
    }
}

template <class Type, size_t LENGTH> 
void BinaryWriter::value( const char* /*name*/, const char* /*child_name*/, Type (& values)[LENGTH] )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_VALUE, 0, 0, values, LENGTH );
    }
}

template <class Type, size_t LENGTH> 
void BinaryWriter::refer( const char* /*name*/, const char* /*child_name*/, Type (& values)[LENGTH] )
{
    if ( get_mode() != MODE_REFERENCE )
    {
        save( *this, MODE_REFERENCE, 0, 0, values, LENGTH );
    }
}

}
