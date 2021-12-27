#pragma once

#include "ObjectGuard.hpp"
#include "objects.ipp"
#include <sweet/pointer/ptr.hpp>
#include <persist/assert.hpp>

namespace persist
{

template <class Type> struct resolver<ptr<Type> >
{
    static void resolve( void* reference, void* /*raw_ptr*/, void* smart_ptr )
    {
        if ( smart_ptr )
        {
            ptr<Type>* referer = static_cast<ptr<Type>*>( reference );
            ptr<Type>* owner = static_cast<ptr<Type>*>( smart_ptr );
            *referer = *owner;
        }
    }
};

template <class Archive, class Type>
void save( Archive& archive, int mode, const char* name, ptr<Type>& object )
{
    ObjectGuard<Archive> guard( archive, name, object.get(), mode, object.get() != 0 ? 1 : 0 );
    switch ( mode )
    {
        case MODE_VALUE:
            if ( object.get() != 0 )
            {
                archive.persist( typeid(*object.get()), archive, object.get() );
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
void load( Archive& archive, int mode, const char* name, ptr<Type>& object )
{
    assert( object.get() == NULL );

    ObjectGuard<Archive> guard( archive, name, 0, mode );
    switch ( mode )
    {
        case MODE_VALUE:
            object.reset( static_cast<Type*>(archive.template create_and_persist<Type>()) );
            break;

        case MODE_REFERENCE:
            archive.reference( archive.get_address(), reinterpret_cast<void**>(&object), &resolver<ptr<Type> >::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Archive, class Type>
void resolve( Archive& archive, int mode, ptr<Type>& object )
{
    ObjectGuard<Archive> guard( archive, 0, object.get(), mode );
    switch ( mode )
    {
        case MODE_VALUE:
            if ( object.get() )
            {
                archive.track( object.get(), &object );
                archive.persist( typeid(*object.get()), archive, object.get() );
            }
            break;

        case MODE_REFERENCE:
            archive.reference( 0, reinterpret_cast<void**>(&object), &resolver<ptr<Type> >::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Type>
struct resolver<pointer::weak_ptr<Type> >
{
    static void resolve( void* reference, void* /*raw_ptr*/, void* smart_ptr )
    {
        pointer::weak_ptr<Type>* referer = static_cast<pointer::weak_ptr<Type>*>( reference );
        ptr<Type>* owner = static_cast<ptr<Type>*>( smart_ptr );
        *referer = *owner;
    }
};

template <class Archive, class Type>
void save( Archive& archive, int mode, const char* name, pointer::weak_ptr<Type>& object )
{
    assert( mode == MODE_REFERENCE );
    (void) mode;

    ptr<Type> locked_object = object.lock();
    if ( locked_object )
    {
        ObjectGuard<Archive> guard( archive, name, locked_object.get(), MODE_REFERENCE, 1 );
    }
    else
    {
        ObjectGuard<Archive> guard( archive, name, NULL, MODE_REFERENCE, 0 );
    }
}

template <class Archive, class Type>
void load( Archive& archive, int mode, const char* name, pointer::weak_ptr<Type>& object )
{
    assert( mode == MODE_REFERENCE );
    assert( object.lock() == ptr<Type>() );
    (void) mode;

    ObjectGuard<Archive> guard( archive, name, 0, MODE_REFERENCE );
    archive.reference( archive.get_address(), reinterpret_cast<void**>(&object), &resolver<pointer::weak_ptr<Type> >::resolve );
}

template <class Archive, class Type>
void resolve( Archive& archive, int mode, pointer::weak_ptr<Type>& object )
{
    assert( mode == MODE_REFERENCE );
    (void) mode;
    archive.reference( 0, reinterpret_cast<void**>(&object), &resolver<pointer::weak_ptr<Type> >::resolve );
}

}
