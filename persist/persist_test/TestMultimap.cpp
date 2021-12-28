//
// TestMultimap.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include <UnitTest++/UnitTest++.h>
#include <persist/persist.hpp>
#include <persist/map.hpp>
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

SUITE( TestMultimap )
{
    struct Model
    {
        std::multimap<std::string, Item> items_;

        Model()
        {
            using std::make_pair;

            Item item;
            item.m_string = "item_000";
            items_.insert( make_pair(item.m_string, item) );
            item.m_string = "item_001";
            items_.insert( make_pair(item.m_string, item) );
            item.m_string = "item_002";
            items_.insert( make_pair(item.m_string, item) );
            item.m_string = "item_003";
            items_.insert( make_pair(item.m_string, item) );
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

    TEST( TestMultimapXml )
    {
        TestBody<XmlWriter, XmlReader, Model> body( "TestMultimap.xml" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestMultimapJson )
    {
        TestBody<JsonWriter, JsonReader, Model> body( "TestMultimap.json" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestMultimapLua )
    {
        TestBody<LuaWriter, LuaReader, Model> body( "TestMultimap.lua" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestMultimapBinary )
    {
        TestBody<BinaryWriter, BinaryReader, Model> body( "TestMultimap.dat" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
}
