#pragma once

#include <persist/assert.hpp>
#include <memory>

namespace persist
{

template <class Archive, class Type>
void save( Archive& archive, int mode, const char* name, std::weak_ptr<Type>& object )
{
//
// A weak_ptr can only ever be a reference and so it is always written out
// as such.
//
    assert( mode == MODE_REFERENCE );
    if ( !object.expired() )
    {
        std::shared_ptr<Type> locked_object = object.lock();
        ObjectGuard<Archive> guard( archive, name, locked_object.get(), MODE_REFERENCE, 1 );
    }
    else
    {
        ObjectGuard<Archive> guard( archive, name, 0, MODE_REFERENCE, 0 );
    }
}

template <class Archive, class Type>
void load( Archive& archive, int mode, const char* name, std::weak_ptr<Type>& object )
{
    assert( mode == MODE_REFERENCE );
    assert( object.expired() );

    ObjectGuard<Archive> guard( archive, name, 0, MODE_REFERENCE );
    archive.reference( archive.get_address(), reinterpret_cast<void**>(&object), &resolver<std::weak_ptr<Type>>::resolve );
}

template <class Archive, class Type>
void resolve( Archive& archive, int mode, std::weak_ptr<Type>& object )
{
    assert( mode == MODE_REFERENCE );
    archive.reference( 0, reinterpret_cast<void**>(&object), &resolver<std::weak_ptr<Type>>::resolve );
}

template <class Type>
struct resolver<std::weak_ptr<Type>>
{
    static void resolve( void* reference, void* raw_ptr, void* smart_ptr )
    {
        std::weak_ptr<Type>* referer = static_cast<std::weak_ptr<Type>*>( reference );
        std::shared_ptr<Type>* owner = static_cast<std::shared_ptr<Type>*>( smart_ptr );
        *referer = *owner;
    }
};

}
