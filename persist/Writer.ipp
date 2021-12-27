//
// Writer.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "Writer.hpp"
#include "WriterType.ipp"
#include "assert.hpp"
#include "functions.ipp"
#include <error/ErrorPolicy.hpp>

namespace persist
{

template <class DerivedArchive>
persist::Writer<DerivedArchive>::Writer( error::ErrorPolicy& error_policy )
: Archive( ARCHIVE_WRITER )
, error_policy_( error_policy )
, m_types()
, m_tracked_addresses()
{
}

template <class DerivedArchive>
persist::Writer<DerivedArchive>::Writer( ArchiveType type, error::ErrorPolicy& error_policy )
: Archive( type )
, error_policy_( error_policy )
, m_types()
, m_tracked_addresses()
{
    assert( type != ARCHIVE_READER );
}

template <class DerivedArchive>
Writer<DerivedArchive>::Writer( const Writer<DerivedArchive>& writer )
: Archive( writer )
, error_policy_( writer.error_policy_ )
, m_types( writer.m_types )
, m_tracked_addresses( writer.m_tracked_addresses )
{
}

template <class DerivedArchive>
void Writer<DerivedArchive>::reset()
{
    set_entered( false );
    set_version( 0 );
    m_tracked_addresses.clear();
}

template <class DerivedArchive>
void Writer<DerivedArchive>::track( const void* address )
{
    m_tracked_addresses.insert( address );
}

template <class DerivedArchive>
bool Writer<DerivedArchive>::is_tracked( const void* address ) const
{
    return m_tracked_addresses.find( address ) != m_tracked_addresses.end();
}

template <class DerivedArchive>
void Writer<DerivedArchive>::persist( const std::type_info& type, DerivedArchive& archive, void* object )
{
    using std::set;
    
    if ( object )
    {
        typename set<WriterType<DerivedArchive> >::iterator i = m_types.find( WriterType<DerivedArchive>(type, std::string(), PERSIST_NORMAL, 0) );
        error_policy_.error( i == m_types.end(), "The type '%s' is not declared", type.name() );
        if ( i != m_types.end() )
        {
            if ( i->is_polymorphic() )
            {
                archive.type( i->get_name() );
            }            
            i->persist( archive, object );
        }
    }
}

template <class DerivedArchive>
template <class Type> 
void Writer<DerivedArchive>::enter( const char* format, int version, Type& /*object*/ )
{
    if ( !is_entered() )
    {
        DerivedArchive& archive = static_cast<DerivedArchive&>( *this );
        if ( archive.get_mode() == MODE_VALUE )
        {
            assert( format );
            std::string format_string( format );
            archive.value( get_format_keyword().c_str(), format_string );

            set_version( version );
            archive.value( get_version_keyword().c_str(), version );
        }
        set_entered( true );
    }
}

template <class DerivedArchive>
template <class Type> 
void Writer<DerivedArchive>::declare( const char* name, int flags )
{
    typename std::set<WriterType<DerivedArchive> >::iterator i = m_types.find( WriterType<DerivedArchive>(typeid(Type), std::string(), PERSIST_NORMAL, 0) );
    error_policy_.error( i != m_types.end(), "The type '%s' is already declared", typeid(Type).name() );
    if ( i == m_types.end() )
    {
        m_types.insert( WriterType<DerivedArchive>(typeid(Type), name, flags, &persist::persist<DerivedArchive, Type>) );
    }
}

}
