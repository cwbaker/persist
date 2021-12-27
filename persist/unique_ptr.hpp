#pragma once

#include <persist/assert.hpp>
#include <memory>

namespace persist
{

/**
// Save a heap allocated object owned by a unique_ptr.
//
// The \e mode parameter must be MODE_VALUE because an unique_ptr always
// owns the object that it points to - it can never be a reference.
//
// @param archive
//  The Archive to save the object to.
//
// @param mode
//  Must be MODE_VALUE.
//
// @param name
//  The name of the element to save the object to.
//
// @param value
//  The unique_ptr that owns the object to save.
//
// @relates unique_ptr
*/
template <class Archive, class Type>
void
save( Archive& archive, int mode, const char* name, std::unique_ptr<Type>& object )
{
    assert( mode == MODE_VALUE );
    ObjectGuard<Archive> guard( archive, name, object.get(), mode, object.get() != nullptr ? 1: 0 );
    if ( object.get() )
    {
        archive.persist( typeid(*object.get()), archive, object.get() );
    }
}


/**
// Load a heap allocated object owned by an unique_ptr.
//
// The \e mode parameter must be MODE_VALUE because an unique_ptr always
// owns the object that it points to - it can never be a reference.
//
// @param archive
//  The Archive to load the object from.
//
// @param mode
//  Must be MODE_VALUE.
//
// @param name
//  The name of the element to load the object from.
//
// @param value
//  The unique_ptr to give ownership of the object to (must be empty when
//  passed to this function).
//
// @relates unique_ptr
*/
template <class Archive, class Type>
void
load( Archive& archive, int /*mode*/, const char* name, std::unique_ptr<Type>& object )
{
    assert( !object.get() );
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    object.reset( static_cast<Type*>(archive.template create_and_persist<Type>()) );
}


/**
// Resolve references made from a heap allocated object owned by 
// an unique_ptr.
//
// @param archive
//  The Archive to use to resolve references.
//
// @param mode
//  Must be MODE_VALUE.
//
// @param value
//  The unique_ptr that owns the object to resolve references in.
//
// @relates unique_ptr
*/
template <class Archive, class Type>
void
resolve( Archive& archive, int /*mode*/, std::unique_ptr<Type>& object )
{
    ObjectGuard<Archive> guard( archive, 0, object.get(), MODE_VALUE );
    if ( object.get() != nullptr )
    {
        archive.track( object.get(), &object );
        archive.persist( typeid(*object.get()), archive, object.get() );
    }
}

}
