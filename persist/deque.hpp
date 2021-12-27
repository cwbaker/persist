#pragma once

namespace persist
{

template <class Archive, class Type, class ALLOCATOR> 
void save( Archive& archive, int mode, const char* name, const char* child_name, std::deque<Type, ALLOCATOR>& container )
{
    save_stl_sequence( archive, mode, name, child_name, container );
}

template <class Archive, class Type, class ALLOCATOR> 
void load( Archive& archive, int mode, const char* name, const char* child_name, std::deque<Type, ALLOCATOR>& container )
{
    assert( container.empty() );
    load_stl_sequence( archive, mode, name, child_name, container );
}

template <class Archive, class Type, class ALLOCATOR> 
void resolve( Archive& archive, int mode, std::deque<Type, ALLOCATOR>& container )
{
    resolve_stl_sequence( archive, mode, container );
}

template <class Archive, class Type, class ALLOCATOR>
void save( Archive& archive, int mode, const char* name, std::deque<Type, ALLOCATOR>& container )
{
    save( archive, mode, name, "item", container );
}

template <class Archive, class Type, class ALLOCATOR>
void load( Archive& archive, int mode, const char* name, std::deque<Type, ALLOCATOR>& container )
{
    load( archive, mode, name, "item", container );
}

}
