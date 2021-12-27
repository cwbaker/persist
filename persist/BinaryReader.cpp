//
// BinaryReader.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "BinaryReader.hpp"
#include "Resolver.hpp"
#include "Reader.ipp"
#include "Writer.ipp"
#include <iostream>

using namespace persist;

BinaryReader::BinaryReader( error::ErrorPolicy& error_policy )
: Reader<BinaryReader>( error_policy )
, error_policy_( error_policy )
, m_state()
, m_istream( nullptr )
, m_type()
, m_resolver( error_policy )
{
}

BinaryReader::BinaryReader( const BinaryReader& reader )
: Reader<BinaryReader>( reader )
, error_policy_( reader.error_policy_ )
, m_state()
, m_istream( nullptr )
, m_type()
, m_resolver( reader.m_resolver )
{
}

void BinaryReader::track( void* /*raw_ptr*/, void* /*smart_ptr*/ )
{
}

void BinaryReader::reference( const void* address, void* /*reference*/, void (* /*resolve*/)(void* reference, void* raw_ptr, void* smart_ptr) )
{
    m_resolver.add_reference_address( address );
}

void BinaryReader::add_set_reference_count( int /*count*/ )
{
}

void BinaryReader::move_reference_addresses_backward( int n )
{
    m_resolver.move_reference_addresses_backward( n );
}

const std::string& BinaryReader::get_type()
{
    value( static_cast<const char*>(NULL), m_type );
    return m_type;
}

const void* BinaryReader::get_address()
{
    assert( !m_state.empty() );
    return m_state.top().m_address;
}

Mode BinaryReader::get_mode() const
{
    assert( !m_state.empty() );
    return m_state.top().m_mode;
}

bool BinaryReader::get_sequence() const
{
    assert( !m_state.empty() );
    return m_state.top().m_sequence;
}

int BinaryReader::get_count() const
{
    // This is very different from the TextReader::get_count() function in
    // that it returns the remaining number of objects and not the total
    // number.  It is assumed that this function is only called to reserve the
    // number of elements to be read in for a std::vector before any of the
    // objects have been read in both cases this will be the total number of
    // objects to read in the sequence.
    assert( !m_state.empty() );
    return m_state.top().m_size;
}

void BinaryReader::begin_object( const char* /*name*/, const void* /*ignored_address*/, Mode mode, int /*ignored_size*/ )
{
    assert( m_istream );
    assert( mode == MODE_VALUE || mode == MODE_REFERENCE );
    
    int size = 0;
    m_istream->read( reinterpret_cast<char*>(&size), sizeof(size) );

    const void* address = NULL;
    m_istream->read( reinterpret_cast<char*>(&address), sizeof(address) );

    m_state.push( State(mode, size, address, false) );
    if ( m_state.top().m_mode == MODE_VALUE )
    {
        m_resolver.begin_reference_addresses( address );
    }
}

void BinaryReader::end_object()
{
    if ( get_mode() == MODE_VALUE )
    {
        m_resolver.end_reference_addresses();
    }

    m_type.clear();
    m_state.pop();
    assert( !m_state.empty() );
}

bool BinaryReader::find_next_object( const char* /*name*/ )
{
    assert( !m_state.empty() );

    if ( m_state.top().m_size > 0 )
    {
        --m_state.top().m_size;
        return true;
    }
    else
    {
        return false;
    }
}

bool BinaryReader::is_object() const
{
    assert( !m_state.empty() );
    return m_state.top().m_size > 0;
}

bool BinaryReader::is_object_empty() const
{
    return false;
}

bool BinaryReader::is_reference() const
{
    return get_mode() == MODE_REFERENCE;
}

void BinaryReader::flag( int /*value*/ )
{
}

void BinaryReader::value( const char* /*name*/, bool& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, char& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, signed char& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, unsigned char& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, wchar_t& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, short& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, unsigned short& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, int& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, unsigned int& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, long& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, unsigned long& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

#if defined(_MSC_VER)
void BinaryReader::value( const char* /*name*/, std::time_t& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}
#endif

void BinaryReader::value( const char* /*name*/, float& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, double& value )
{
    assert( m_istream );
    m_istream->read( reinterpret_cast<char*>(&value), sizeof(value) );
}

void BinaryReader::value( const char* /*name*/, wchar_t* value, size_t max )
{
    assert( m_istream );

    size_t length = 0;
    m_istream->read( reinterpret_cast<char*>(&length), sizeof(length) );
    m_istream->read( reinterpret_cast<char*>(value), std::min(max, length) * sizeof(wchar_t) );
    value[std::min(max - 1, length)] = L'\0';

    if ( length > max )
    {
        m_istream->seekg( (length - max) * sizeof(wchar_t), std::ios_base::cur );
    }
}

void BinaryReader::value( const char* /*name*/, std::wstring& value )
{
    assert( m_istream );

    size_t length = 0;
    m_istream->read( reinterpret_cast<char*>(&length), sizeof(length) );
    value.clear();
    value.reserve( length );
    
    wchar_t buffer [256];
    length *= sizeof(wchar_t);
    while ( length > sizeof(buffer) )
    {
        m_istream->read( reinterpret_cast<char*>(buffer), sizeof(buffer) );        
        value.append( buffer, sizeof(buffer) / sizeof(wchar_t) );
        length -= sizeof(buffer);
    }

    if ( length > 0 )
    {
        m_istream->read( reinterpret_cast<char*>(buffer), length );        
        value.append( buffer, length / sizeof(wchar_t) );
    }
}

void BinaryReader::value( const char* /*name*/, char* value, size_t max )
{
    assert( m_istream );

    size_t length = 0;
    m_istream->read( reinterpret_cast<char*>(&length), sizeof(length) );
    m_istream->read( value, std::min(max, length) );
    value[std::min(max - 1, length)] = '\0';

    if ( length > max )
    {
        m_istream->seekg( length - max, std::ios_base::cur );
    }
}

void BinaryReader::value( const char* /*name*/, std::string& value )
{
    assert( m_istream );

    size_t length = 0;
    m_istream->read( reinterpret_cast<char*>(&length), sizeof(length) );
    value.clear();
    value.reserve( length );
    
    char buffer [256];
    while ( length > sizeof(buffer) )
    {
        m_istream->read( buffer, sizeof(buffer) );
        value.append( buffer, sizeof(buffer) );
        length -= sizeof(buffer);
    }

    if ( length > 0 )
    {
        m_istream->read( buffer, length );
        value.append( buffer, length );
    }
}
