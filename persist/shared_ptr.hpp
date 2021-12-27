#pragma once

#include <persist/assert.hpp>
#include <memory>

namespace persist
{

template <class Archive, class Type>
void save( Archive& archive, int mode, const char* name, std::shared_ptr<Type>& object )
{
    ObjectGuard<Archive> guard( archive, name, object.get(), mode, object.get() != 0 ? 1 : 0 );
    switch ( mode )
    {
        case MODE_VALUE:
            if ( object.get() )
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
void load( Archive& archive, int mode, const char* name, std::shared_ptr<Type>& object )
{
    assert( !object.get() );

    ObjectGuard<Archive> guard( archive, name, 0, mode );
    switch ( mode )
    {
        case MODE_VALUE:
            object.reset( static_cast<Type*>(archive.create_and_persist<Type>()) );
            break;

        case MODE_REFERENCE:
            archive.reference( archive.get_address(), reinterpret_cast<void**>(&object), &resolver<std::shared_ptr<Type>>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Archive, class Type>
void resolve( Archive& archive, int mode, std::shared_ptr<Type>& object )
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
            archive.reference( 0, reinterpret_cast<void**>(&object), &resolver<std::shared_ptr<Type>>::resolve );
            break;

        default:
            assert( false );
            break;
    }
}

template <class Type>
struct resolver<std::shared_ptr<Type>>
{
    static void resolve( void* reference, void* raw_ptr, void* smart_ptr )
    {
        if ( smart_ptr )
        {
            std::shared_ptr<Type>* referer = static_cast<std::shared_ptr<Type>*>( reference );
            std::shared_ptr<Type>* owner = static_cast<std::shared_ptr<Type>*>( smart_ptr );
            *referer = *owner;
        }
    }
};

}
