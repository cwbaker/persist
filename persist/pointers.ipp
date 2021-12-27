//
// pointers.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "ObjectGuard.hpp"
#include "objects.ipp"
#include <persist/assert.hpp>

namespace persist
{

template <class Type>
struct creator<Type*>
{
    static Type* create()
    {
        return nullptr;
    }
};

template <class Archive, class Type>
void save( Archive& archive, int mode, const char* name, Type*& object )
{
    ObjectGuard<Archive> guard( archive, name, object, mode, object != 0 ? 1 : 0 );
    switch ( mode )
    {
        case MODE_VALUE:
            if ( object )
            {
                archive.persist( typeid(*object), archive, static_cast<void*>(object) );
            }
            break;

        case MODE_REFERENCE:
            break;

        default:
            assert( false );
            break;
    }
}

template <class Archive, class Type>
void load( Archive& archive, int mode, const char* name, Type*& object )
{
    assert( object == NULL );

    ObjectGuard<Archive> guard( archive, name, 0, mode );
    switch ( archive.get_mode() )
    {
        case MODE_VALUE:
            object = static_cast<Type*>( archive.template create_and_persist<Type>() );
            break;

        case MODE_REFERENCE:
            archive.reference( archive.get_address(), reinterpret_cast<void**>(&object), &resolver<Type*>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Archive, class Type>
void resolve( Archive& archive, int mode, Type*& object )
{
    ObjectGuard<Archive> guard( archive, 0, object, mode );
    switch ( mode )
    {
        case MODE_VALUE:  
            if ( object )
            {      
                archive.track( object, 0 );
                archive.persist( typeid(*object), archive, object );
            }
            break;

        case MODE_REFERENCE:
            archive.reference( 0, reinterpret_cast<void**>(&object), &resolver<Type*>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Type>
struct resolver<Type*>
{
    static void resolve( void* reference, void* raw_ptr, void* /*smart_ptr*/ )
    {
        *reinterpret_cast<void**>( reference ) = static_cast<Type*>( raw_ptr );
    }
};

}
