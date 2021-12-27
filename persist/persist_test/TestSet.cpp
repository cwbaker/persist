//
// TestSet.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include <UnitTest++/UnitTest++.h>
#include <sweet/persist/persist.hpp>
#include <sweet/persist/set.hpp>
#include <sweet/persist/XmlWriter.ipp>
#include <sweet/persist/XmlReader.ipp>
#include <sweet/persist/JsonWriter.ipp>
#include <sweet/persist/JsonReader.ipp>
#include <sweet/persist/LuaWriter.ipp>
#include <sweet/persist/LuaReader.ipp>
#include <sweet/persist/BinaryWriter.ipp>
#include <sweet/persist/BinaryReader.ipp>
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
