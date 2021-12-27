#pragma once

#include "ObjectGuard.hpp"
#include "types.hpp"
#include <assert/assert.hpp>

namespace persist
{

template <class Archive>
ObjectGuard<Archive>::ObjectGuard( Archive& archive, const char* name, const void* address, int mode, int size )
: m_archive( archive )
{
    SWEET_ASSERT( mode == MODE_VALUE || mode == MODE_REFERENCE );
    m_archive.begin_object( name, address, static_cast<Mode>(mode), size );
}

template <class Archive>
ObjectGuard<Archive>::~ObjectGuard()
{
    m_archive.end_object();
}

}
