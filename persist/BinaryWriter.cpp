//
// BinaryWriter.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "BinaryWriter.hpp"
#include "Writer.ipp"
#include <iostream>
#include <string.h>
#include <wchar.h>

using namespace persist;

BinaryWriter::BinaryWriter()
: Writer<BinaryWriter>()
, m_state()
, m_ostream( nullptr )
{
}

BinaryWriter::BinaryWriter( const BinaryWriter& writer )
: Writer<BinaryWriter>( writer )
, m_state()
, m_ostream( nullptr )
{
}

Mode BinaryWriter::get_mode() const
{
    assert( !m_state.empty() );
    return m_state.top().m_mode;
}

void BinaryWriter::begin_object( const char* /*name*/, const void* address, Mode mode, int size )
{
    assert( m_ostream );
    assert( mode == MODE_VALUE || mode == MODE_REFERENCE );

    m_state.push( State(mode) );
    m_ostream->write( reinterpret_cast<const char*>(&size), sizeof(size) );
    m_ostream->write( reinterpret_cast<const char*>(&address), sizeof(address) );
}

void BinaryWriter::end_object()
{
    m_state.pop();
    assert( !m_state.empty() );
}

void BinaryWriter::type( const std::string& type )
{
    assert( !type.empty() );
    value( static_cast<const char*>(NULL), const_cast<std::string&>(type) );
}

void BinaryWriter::flag( int /*value*/ )
{
}

void BinaryWriter::value( const char* /*name*/, bool& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, char& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, signed char& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, unsigned char& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, wchar_t& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, short& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, unsigned short& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, int& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, unsigned int& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, long& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, unsigned long& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

#if defined(_MSC_VER)
void BinaryWriter::value( const char* /*name*/, time_t& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}
#endif

void BinaryWriter::value( const char* /*name*/, float& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, double& value )
{
    assert( m_ostream );
    m_ostream->write( reinterpret_cast<const char*>(&value), sizeof(value) );
}

void BinaryWriter::value( const char* /*name*/, wchar_t* value, size_t /*max*/ )
{
    assert( m_ostream );
    size_t length = wcslen( value );
    m_ostream->write( reinterpret_cast<const char*>(&length), sizeof(length) );
    m_ostream->write( reinterpret_cast<const char*>(value), length * sizeof(wchar_t) );
}

void BinaryWriter::value( const char* /*name*/, std::wstring& value )
{
    assert( m_ostream );
    size_t length = value.length();
    m_ostream->write( reinterpret_cast<const char*>(&length), sizeof(length) );
    m_ostream->write( reinterpret_cast<const char*>(value.c_str()), length * sizeof(wchar_t) );
}

void BinaryWriter::value( const char* /*name*/, char* value, size_t /*max*/ )
{
    assert( m_ostream );
    size_t length = strlen( value );
    m_ostream->write( reinterpret_cast<const char*>(&length), sizeof(length) );
    m_ostream->write( reinterpret_cast<const char*>(value), length );
}

void BinaryWriter::value( const char* /*name*/, std::string& value )
{
    assert( m_ostream );
    size_t length = value.length();
    m_ostream->write( reinterpret_cast<const char*>(&length), sizeof(length) );
    m_ostream->write( reinterpret_cast<const char*>(value.c_str()), length );
}
