//
// TestOwningPointers.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include <UnitTest++/UnitTest++.h>
#include <persist/unique_ptr.hpp>
#include <persist/shared_ptr.hpp>
#include <persist/persist.hpp>
#include <persist/BinaryWriter.ipp>
#include <persist/BinaryReader.ipp>
#include <persist/LuaWriter.ipp>
#include <persist/LuaReader.ipp>
#include <persist/JsonWriter.ipp>
#include <persist/JsonReader.ipp>
#include <persist/XmlWriter.ipp>
#include <persist/XmlReader.ipp>
#include "Item.hpp"
#include "TestBody.hpp"

using namespace persist;

SUITE( TestOwningPointers )
{
    struct Model
    {
        std::unique_ptr<Item> unique_ptr_item_;
        std::shared_ptr<Item> shared_ptr_item_;    

    public:
        Model()
        : unique_ptr_item_( new Item("UniquePtrItem", 0) ),
          shared_ptr_item_( new Item("SharedPtrItem", 1) )
        {
        }

        void clear()
        {
            unique_ptr_item_.reset();
            shared_ptr_item_.reset();
        }

        template <class Archive> void enter( Archive& archive )
        {
            archive.template declare <Item> ( "Item", PERSIST_NORMAL );
        }

        template <class Archive> void exit( Archive& /*archive*/ )
        {
        }

        template <class Archive> void persist( Archive& archive )
        {
            archive.enter( "Model", 1, *this );
            archive.value( "auto_ptr_item", unique_ptr_item_ );
            archive.value( "scoped_ptr_item", shared_ptr_item_ );
        }

        void check( const Model& model )
        {
            CHECK( unique_ptr_item_.get() != nullptr && model.unique_ptr_item_.get() != nullptr && *unique_ptr_item_ == *model.unique_ptr_item_ );
            CHECK( shared_ptr_item_.get() != nullptr && model.shared_ptr_item_.get() != nullptr && *shared_ptr_item_ == *model.shared_ptr_item_ );
        }
    };

    TEST( TestOwningPointersXml )
    {
        TestBody<XmlWriter, XmlReader, Model> body( "TestOwningPointers.xml" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestOwningPointersJson )
    {
        TestBody<JsonWriter, JsonReader, Model> body( "TestOwningPointers.json" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestOwningPointersLua )
    {
        TestBody<LuaWriter, LuaReader, Model> body( "TestOwningPointers.lua" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestOwningPointersBinary )
    {
        TestBody<BinaryWriter, BinaryReader, Model> body( "TestOwningPointers.dat" );
        body.written_model_.check( body.read_model_ );
    }
}
