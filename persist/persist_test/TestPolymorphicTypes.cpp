//
// TestPolymorphicTypes.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#if defined SWEET_BOOST_ENABLED

#include <UnitTest++/UnitTest++.h>
#include <sweet/persist/persist.hpp>
#include <sweet/persist/vector.hpp>
#include <sweet/persist/shared_ptr.hpp>
#include "TestBody.hpp"

using namespace boost;
using namespace persist;

SUITE( TestPolymorphicTypes )
{
    struct Base
    {
        std::string name_;

        Base()
        : name_()
        {
        }

        virtual ~Base()
        {
        }

        Base( const std::string& name )
        : name_( name )
        {
        }

        bool operator==( const Base& base ) const
        {
            return name_ == base.name_;
        }

        template <class Archive> void persist( Archive& archive )
        {
            archive.value( "name", name_ );
        }
    };

    struct Left : public Base
    {
        int left_value_;

        Left()
        : Base(),
          left_value_( 0 )
        {
        }

        Left( const std::string& name, int left_value )
        : Base( name ),
          left_value_( left_value )
        {
        }
    
        bool operator==( const Left& left ) const
        {
            return Base::operator==( left ) && left_value_ == left.left_value_;
        }

        template <class Archive> void persist( Archive& archive )
        {
            Base::persist( archive );
            archive.value( "left_value", left_value_ );
        }
    };

    struct Right : public Base
    {
        float right_value_;

        Right()
        : Base(),
          right_value_( 0 )
        {
        }

        Right( const std::string& name, float right_value )
        : Base( name ),
          right_value_( right_value )
        {
        }

        bool operator==( const Right& right ) const
        {
            return Base::operator==( right ) && right_value_ == right.right_value_;
        }

        template <class Archive> void persist( Archive& archive )
        {
            Base::persist( archive );
            archive.value( "right_value", right_value_ );
        }
    };

    struct Model 
    {
        std::vector<shared_ptr<Base>> bases_;

        Model()
        {
            bases_.push_back( shared_ptr<Base>(new Base("001"))         );
            bases_.push_back( shared_ptr<Base>(new Right("002", 23.4f)) );
            bases_.push_back( shared_ptr<Base>(new Left("003", 23))     );
            bases_.push_back( shared_ptr<Base>(new Right("004", 23.4f)) );
        }
        
        void clear()
        {
            bases_.clear();
        }

        template <class Archive> void enter( Archive& archive )
        {
            archive.declare <Base>  ( "Base",  PERSIST_POLYMORPHIC );        
            archive.declare <Left>  ( "Left",  PERSIST_POLYMORPHIC );        
            archive.declare <Right> ( "Right", PERSIST_POLYMORPHIC );        
        }

        template <class Archive> void exit( Archive& archive )
        {
        }

        template <class Archive> void persist( Archive& archive )
        {
            archive.enter( "Model", 1, *this );
            archive.value( "bases", "base", bases_ );
        }

        void check( const Model& model ) const
        {
            std::vector<shared_ptr<Base>>::const_iterator i = bases_.begin();
            std::vector<shared_ptr<Base>>::const_iterator j = model.bases_.begin();
            while ( i != bases_.end() && j != model.bases_.end() && (*i == NULL && *j == NULL || *i != NULL && *j != NULL && (*(*i) == *(*j) && typeid(*(*i)) == typeid(*(*j)))) )
            {
                ++i;
                ++j;
            }

            CHECK( typeid(*bases_[0].get()) == typeid(Base) );
            CHECK( typeid(*bases_[1].get()) == typeid(Right) );
            CHECK( typeid(*bases_[2].get()) == typeid(Left) );
            CHECK( typeid(*bases_[3].get()) == typeid(Right) );
            CHECK( i == bases_.end() && j == model.bases_.end() );
        }
    };

    TEST( TestPolymorphicTypesXml )
    {
        TestBody<XmlWriter, XmlReader, Model> body( "TestPolymorphicTypes.xml" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestPolymorphicTypesJson )
    {
        TestBody<JsonWriter, JsonReader, Model> body( "TestPolymorphicTypes.json" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestPolymorphicTypesLua )
    {
        TestBody<LuaWriter, LuaReader, Model> body( "TestPolymorphicTypes.lua" );
        body.written_model_.check( body.read_model_ );
    }
    
    TEST( TestPolymorphicTypesBinary )
    {
        TestBody<BinaryWriter, BinaryReader, Model> body( "TestPolymorphicTypes.dat" );
        body.written_model_.check( body.read_model_ );
    }
}

#endif
