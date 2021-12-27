//
// ReaderType.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include <persist/assert.hpp>

namespace persist
{

template <class Archive>
ReaderType<Archive>::ReaderType( const std::type_info& type, const std::string& name, int flags, void* (*create)(), void (*persist)(Archive&, void*) )
: m_type( &type ),
  m_name( name ),
  m_flags( flags ),
  m_create( create ),
  m_persist( persist )
{
}

template <class Archive>
bool ReaderType<Archive>::is_polymorphic() const
{
    return (m_flags & PERSIST_POLYMORPHIC) != 0;
}

template <class Archive>
void* ReaderType<Archive>::create() const
{
    assert( m_create );
    return (*m_create)();
}

template <class Archive>
void ReaderType<Archive>::persist( Archive& archive, void* object ) const
{
    assert( m_persist );
    (*m_persist)( archive, object );
}

template <class Archive>
bool ReaderType<Archive>::operator<( const ReaderType& type ) const
{
    return m_type->before( *type.m_type );
}

template <class Archive>
bool ReaderType<Archive>::compare_by_name( const ReaderType& type ) const
{
    return m_name < type.m_name;
}

}
