#pragma once

#include "ObjectGuard.hpp"
#include "types.hpp"
#include <persist/assert.hpp>

namespace persist
{

template <class Type> struct creator
{
    static Type create()
    {
        return Type();
    }
};

template <class Type> struct resolver
{
    static void resolve( void* /*reference*/, void* /*raw_ptr*/, void* /*smart_ptr*/ )
    {
        assert( false );
    }
};

template <class Archive, class Type> void save( Archive& archive, int mode, const char* name, Type& object )
{
    assert( mode == MODE_VALUE );    
    ObjectGuard<Archive> guard( archive, name, &object, mode, 1 );
    object.persist( archive );
}

template <class Archive, class Type> void load( Archive& archive, int mode, const char* name, Type& object )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    if ( archive.is_object() )
    {
        object.persist( archive );
    }
}

template <class Archive, class Type> void resolve( Archive& archive, int mode, Type& object )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    
    ObjectGuard<Archive> guard( archive, 0, &object, MODE_VALUE );    
    if ( archive.is_object() )
    {
        object.persist( archive );
        archive.track( &object, 0 );
    }
}

}
