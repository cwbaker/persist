#pragma once

#include "Resolver.ipp"
#include "ReaderType.ipp"
#include "functions.ipp"
#include <persist/assert.hpp>
#include <memory>

namespace persist
{

template <class DerivedArchive>
Reader<DerivedArchive>::Reader()
: Archive( ARCHIVE_READER )
, m_types()
, m_types_by_name()
{
}

template <class DerivedArchive>
Reader<DerivedArchive>::Reader( const Reader<DerivedArchive>& reader )
: Archive( reader )
, m_types( reader.m_types )
, m_types_by_name( reader.m_types_by_name )
{
}

template <class DerivedArchive>
void Reader<DerivedArchive>::reset()
{
    set_entered( false );
    set_version( 0 );
}

template <class DerivedArchive>
template <class Type>
void Reader<DerivedArchive>::enter( const char* format, int /*version*/, Type& /*object*/ )
{
    assert( format );

    if ( !is_entered() )
    {
        DerivedArchive& archive = static_cast<DerivedArchive&>( *this );
        std::string actual_format;
        archive.value( get_format_keyword().c_str(), actual_format );
        if ( actual_format != format )
        {
            throw PersistError( "Actual format '%s' does not match expected format '%s'", actual_format.c_str(), format );
        }
        
        int version = 0;
        archive.value( get_version_keyword().c_str(), version );
        set_version( version );
        set_entered( false );
    }
}

template <class DerivedArchive>
template <class Type>
void Reader<DerivedArchive>::declare( const char* name, int flags )
{
    typename ReaderType<DerivedArchive>::set::iterator i = m_types.find( ReaderType<DerivedArchive>(typeid(Type), std::string(), PERSIST_NORMAL, 0, 0) );
    if ( i != m_types.end() )
    {
        throw PersistError( "Type '%s' is already declared", typeid(Type).name() );
    }
    if ( i == m_types.end() )
    {
        typename ReaderType<DerivedArchive>::set::iterator j = m_types.insert( ReaderType<DerivedArchive>(typeid(Type), name, flags, &persist::create<Type>, &persist::persist<DerivedArchive, Type>) ).first;
        m_types_by_name.insert( &(*j) );
    }
}

template <class DerivedArchive>
template <class Type>
void* Reader<DerivedArchive>::create_and_persist()
{
    DerivedArchive& archive = static_cast<DerivedArchive&>( *this );
    if ( !archive.is_object() || archive.is_object_empty() )
    {
        return nullptr;
    }

    const ReaderType<DerivedArchive>* type = nullptr;
    typename ReaderType<DerivedArchive>::set::iterator i = m_types.find( ReaderType<DerivedArchive>(typeid(Type), std::string(), PERSIST_NORMAL, 0, 0) );
    if ( i == m_types.end() )
    {
        throw PersistError( "Undefined type '%s'", typeid(Type).name() );
    }
    if ( i != m_types.end() )
    {
        type = &(*i);
        if ( type->is_polymorphic() )
        {
            std::string name = archive.get_type();
            ReaderType<DerivedArchive> type_by_name( typeid(Type), name, PERSIST_NORMAL, 0, 0 );
            typename ReaderType<DerivedArchive>::set_by_name::iterator j = m_types_by_name.find( &type_by_name );
            if ( j == m_types_by_name.end() )
            {
                throw PersistError( "Undefined type '%s'", name.c_str() );
            }
            if ( j != m_types_by_name.end() )
            {
                type = *j;
            }
        }
    }

    if ( type )
    {
        std::unique_ptr<Type> object( static_cast<Type*>(type->create()) );
        type->persist( archive, static_cast<void*>(object.get()) );
        return static_cast<void*>( object.release() );
    }
    else
    {
        return nullptr;
    }
}

}
