#pragma once

#include "ObjectGuard.hpp"
#include <persist/assert.hpp>

namespace persist
{

template <> struct creator<const void*>
{
    static const void* create()
    {
        return nullptr;
    }
};

template <> struct resolver<const void*>
{
    static void resolve( void* reference, void* raw_ptr, void* /*smart_ptr*/ )
    {
        *reinterpret_cast<const void**>( reference ) = static_cast<const void*>( raw_ptr );
    }
};

template <class Archive> void save( Archive& archive, int mode, const char* name, const void*& object )
{
    assert( mode == MODE_REFERENCE );
    ObjectGuard<Archive> guard( archive, name, object, mode, object != 0 ? 1 : 0 );
}

template <class Archive> void load( Archive& archive, int mode, const char* name, const void*& object )
{
    assert( !object );
    assert( mode == MODE_REFERENCE );

    ObjectGuard<Archive> guard( archive, name, 0, mode );
    switch ( archive.get_mode() )
    {
        case MODE_VALUE:
            break;

        case MODE_REFERENCE:
            archive.reference( archive.get_address(), reinterpret_cast<const void**>(&object), &resolver<const void*>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Archive> void resolve( Archive& archive, int mode, const void*& object )
{
    assert( mode == MODE_REFERENCE );

    ObjectGuard<Archive> guard( archive, nullptr, object, mode );
    switch ( mode )
    {
        case MODE_VALUE:  
            break;

        case MODE_REFERENCE:
            archive.reference( 0, reinterpret_cast<const void**>(&object), &resolver<const void*>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

}
