#pragma once

#include "functions.hpp"
#include <persist/assert.hpp>

namespace persist
{

template <class Type> 
void* create()
{
    return static_cast<void*>( new Type() );
}

template <class Archive, class Type> 
void persist( Archive& archive, void* object )
{
    Type* type = static_cast<Type*>( object );
    assert( type );
    type->persist( archive );
}

}
