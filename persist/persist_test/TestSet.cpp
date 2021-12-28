//
// TestSet.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include <UnitTest++/UnitTest++.h>
#include <persist/persist.hpp>
#include <persist/set.hpp>
#include <persist/XmlWriter.ipp>
#include <persist/XmlReader.ipp>
#include <persist/JsonWriter.ipp>
#include <persist/JsonReader.ipp>
#include <persist/LuaWriter.ipp>
#include <persist/LuaReader.ipp>
#include <persist/BinaryWriter.ipp>
#include <persist/BinaryReader.ipp>
#include "Item.hpp"
#include "TestBody.hpp"

using namespace persist;

SUITE( TestSet )
{
    struct Model
    {
        std::set<Item> items_;

        Model()
        {
            Item item;
            item.m_string = "item_000";
            items_.insert( item );
            item.m_string = "item_001";
            items_.insert( item );
            item.m_string = "item_002";
            items_.insert( item );
            item.m_string = "item_003";
            items_.insert( item );
        }

        void clear()
        {
            items_.clear();
        }

        template <class Archive> void enter( Archive& /*archive*/ )
        {
        }

        template <class Archive> void exit( Archive& /*archive*/ )
        {
        }

        template <class Archive> void persist( Archive& archive )
        {
            archive.value( "items", "item", items_ );
        }
    };

    TEST( TestSetXml )
    {
        TestBody<XmlWriter, XmlReader, Model> body( "TestSet.xml" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestSetJson )
    {
        TestBody<JsonWriter, JsonReader, Model> body( "TestSet.json" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestSetLua )
    {
        TestBody<LuaWriter, LuaReader, Model> body( "TestSet.lua" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestSetBinary )
    {
        TestBody<BinaryWriter, BinaryReader, Model> body( "TestSet.dat" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
}
