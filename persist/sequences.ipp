#pragma once

#include "ObjectGuard.ipp"
#include "objects.ipp"
#include <persist/assert.hpp>

namespace persist
{

template <class Archive, class CONTAINER>
void save_stl_sequence( Archive& archive, int mode, const char* name, const char* child_name, CONTAINER& container )
{
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, static_cast<int>(container.size()) );

    archive.flag( PERSIST_PRESERVE_EMPTY_ELEMENTS );
    typename CONTAINER::iterator i = container.begin();
    while ( i != container.end() )
    {
        save( archive, mode, child_name, *i );
        ++i;
    }
}

template <class Archive, class CONTAINER>
void load_stl_sequence( Archive& archive, int mode, const char* name, const char* child_name, CONTAINER& container )
{
    assert( container.empty() );

    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    if ( archive.is_object() )
    {
        while ( archive.find_next_object(child_name) )
        {
            container.push_back( creator<typename CONTAINER::value_type>::create() );
            load( archive, mode, child_name, container.back() );
        }
    }
}

template <class Archive, class CONTAINER>
void resolve_stl_sequence( Archive& archive, int mode, CONTAINER& container )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
    for ( typename CONTAINER::iterator i = container.begin(); i != container.end(); ++i )
    {
        resolve( archive, mode, *i );
    }
}

}
