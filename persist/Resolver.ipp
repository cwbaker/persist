#pragma once

#include "Resolver.hpp"
#include <error/ErrorPolicy.hpp>
#include <persist/assert.hpp>

namespace persist
{

template <class Type>
void Resolver::process( int version, Type& object, error::ErrorPolicy& error_policy )
{
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE, &m_object) );
    set_version( version );
    resolve( *this, MODE_VALUE, object );
    m_state.pop();
    assert( m_state.empty() );
    error_policy.error( !m_references.empty(), "Not all references were resolved" );
}

template <class Type> 
void Resolver::process( int version, const char* /*child_name*/, Type& container, error::ErrorPolicy& error_policy )
{
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE, &m_object) );
    set_version( version );
    resolve( *this, MODE_VALUE, container );
    m_state.pop();
    assert( m_state.empty() );
    error_policy.error( !m_references.empty(), "Not all references were resolved" );
}

template <class Type> 
void Resolver::process( int version, const char* /*child_name*/, Type& values, size_t length, error::ErrorPolicy& error_policy )
{
    assert( m_state.empty() );
    m_state.push( State(MODE_VALUE, &m_object) );
    set_version( version );
    resolve( *this, MODE_VALUE, values, length );
    m_state.pop();
    assert( m_state.empty() );
    error_policy.error( !m_references.empty(), "Not all references were resolved" );
}

template <class Filter> 
void Resolver::value( const char* /*name*/, wchar_t* /*value*/, size_t /*max*/, const Filter& /*filter*/ )
{
}

template <class Filter> 
void Resolver::value( const char* /*name*/, std::wstring& /*value*/, const Filter& /*filter*/ )
{
}

template <class Filter> 
void Resolver::value( const char* /*name*/, char* /*value*/, size_t /*max*/, const Filter& /*filter*/ )
{
}

template <class Filter> 
void Resolver::value( const char* /*name*/, std::string& /*value*/, const Filter& /*filter*/ )
{
}

template <class Type, class Filter> 
void Resolver::value( const char* /*name*/, Type& /*value*/, const Filter& /*filter*/ )
{
}

template <class Type> 
void Resolver::value( const char* /*name*/, Type& object )
{
    resolve( *this, MODE_VALUE, object );
}

template <class Type> 
void Resolver::refer( const char* /*name*/, Type& object )
{
    resolve( *this, MODE_REFERENCE, object );
}

template <class Type> 
void Resolver::value( const char* /*name*/, const char* /*child_name*/, Type& container )
{
    resolve( *this, MODE_VALUE, container );
}

template <class Type> 
void Resolver::refer( const char* /*name*/, const char* /*child_name*/, Type& container )
{
    resolve( *this, MODE_REFERENCE, container );
}

template <class Type, size_t LENGTH> 
void Resolver::value( const char* /*name*/, const char* /*child_name*/, Type (& values)[LENGTH] )
{
    resolve( *this, MODE_VALUE, values, LENGTH );
}

template <class Type, size_t LENGTH> 
void Resolver::refer( const char* /*name*/, const char* /*child_name*/, Type (& values)[LENGTH] )
{
    resolve( *this, MODE_REFERENCE, values, LENGTH );
}

}
