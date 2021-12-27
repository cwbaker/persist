//
// TestVector.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include <UnitTest++/UnitTest++.h>
#include <sweet/persist/persist.hpp>
#include <sweet/persist/vector.hpp>
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

SUITE( TestVector )
{
    struct Model
    {
        std::vector<Item> items_;

        Model()
        {
            items_.insert( items_.end(), 4, Item() );
            items_[0].m_string = "item_000";
            items_[1].m_string = "item_001";
            items_[2].m_string = "item_002";
            items_[3].m_string = "item_003";
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

    TEST( TestVectorXml )
    {
        TestBody<XmlWriter, XmlReader, Model> body( "TestVector.xml" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestVectorJson )
    {
        TestBody<JsonWriter, JsonReader, Model> body( "TestVector.json" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestVectorLua )
    {
        TestBody<LuaWriter, LuaReader, Model> body( "TestVector.lua" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
    
    TEST( TestVectorBinary )
    {
        TestBody<BinaryWriter, BinaryReader, Model> body( "TestVector.dat" );
        CHECK( body.written_model_.items_ == body.read_model_.items_ );
    }
}
