#pragma once

#include "sequences.ipp"
#include <persist/assert.hpp>
#include <list>

namespace persist
{

template <class Archive, class Type, class ALLOCATOR> 
void save( Archive& archive, int mode, const char* name, const char* child_name, std::list<Type, ALLOCATOR>& container )
{
    save_stl_sequence( archive, mode, name, child_name, container );
}

template <class Archive, class Type, class ALLOCATOR> 
void load( Archive& archive, int mode, const char* name, const char* child_name, std::list<Type, ALLOCATOR>& container )
{
    assert( container.empty() );
    load_stl_sequence( archive, mode, name, child_name, container );
}

template <class Archive, class Type, class ALLOCATOR> 
void resolve( Archive& archive, int mode, std::list<Type, ALLOCATOR>& container )
{
    resolve_stl_sequence( archive, mode, container );
}

template <class Archive, class Type, class ALLOCATOR>
void save( Archive& archive, int mode, const char* name, std::list<Type, ALLOCATOR>& container )
{
    save( archive, mode, name, "item", container );
}

template <class Archive, class Type, class ALLOCATOR>
void load( Archive& archive, int mode, const char* name, std::list<Type, ALLOCATOR>& container )
{
    load( archive, mode, name, "item", container );
}

}
