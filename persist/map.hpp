#pragma once

#include "utility.hpp"
#include "sequences.ipp"
#include "maps.ipp"
#include <map>

namespace persist
{

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void save( Archive& archive, int mode, const char* name, const char* child_name, std::map<Key, Data, Predicate, Allocator>& container )
{
    save_stl_map( archive, mode, name, child_name, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void load( Archive& archive, int mode, const char* name, const char* child_name, std::map<Key, Data, Predicate, Allocator>& container )
{
    load_stl_map( archive, mode, name, child_name, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void resolve( Archive& archive, int mode, std::map<Key, Data, Predicate, Allocator>& container )
{
    resolve_stl_sequence( archive, mode, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator>
void save( Archive& archive, int mode, const char* name, std::map<Key, Data, Predicate, Allocator>& container )
{
    save( archive, mode, name, "item", container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator>
void load( Archive& archive, int mode, const char* name, std::map<Key, Data, Predicate, Allocator>& container )
{
    load( archive, mode, name, "item", container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void save( Archive& archive, int mode, const char* name, const char* child_name, std::multimap<Key, Data, Predicate, Allocator>& container )
{
    save_stl_map( archive, mode, name, child_name, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void load( Archive& archive, int mode, const char* name, const char* child_name, std::multimap<Key, Data, Predicate, Allocator>& container )
{
    load_stl_multimap( archive, mode, name, child_name, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator> 
void resolve( Archive& archive, int mode, std::multimap<Key, Data, Predicate, Allocator>& container )
{
    resolve_stl_sequence( archive, mode, container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator>
void save( Archive& archive, int mode, const char* name, std::multimap<Key, Data, Predicate, Allocator>& container )
{
    save( archive, mode, name, "item", container );
}

template <class Archive, class Key, class Data, class Predicate, class Allocator>
void load( Archive& archive, int mode, const char* name, std::multimap<Key, Data, Predicate, Allocator>& container )
{
    load( archive, mode, name, "item", container );
}

}
