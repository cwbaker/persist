//
// XmlParser.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "XmlParser.hpp"
#include "Element.hpp"
#include "functions.hpp"
#include <lalr/Parser.ipp>
#include <lalr/PositionIterator.hpp>
#include <lalr/ErrorPolicy.hpp>
#include <error/ErrorPolicy.hpp>
#include <assert/assert.hpp>
#include <fstream>
#include <functional>

using std::bind;
using std::vector;
using std::istream_iterator;
using std::placeholders::_2;
using std::placeholders::_3;
using namespace lalr;
using namespace persist;

extern const lalr::ParserStateMachine* xml_parser_state_machine;

struct XmlParserContext : public lalr::ErrorPolicy
{    
    const char* filename_;
    std::list<Element*> elements_;
    error::ErrorPolicy* error_policy_;
    
    XmlParserContext( const char* filename, Element* element, error::ErrorPolicy* error_policy )
    : filename_( filename )
    , elements_()
    , error_policy_( error_policy )
    {
        SWEET_ASSERT( filename_ );
        SWEET_ASSERT( element );
        SWEET_ASSERT( error_policy_ );
        elements_.push_back( element );
    }
    
    void begin_element( const std::string& name )
    {
        SWEET_ASSERT( !name.empty() );
        SWEET_ASSERT( !elements_.empty() );
        SWEET_ASSERT( elements_.back() );
        
        Element* element = elements_.back()->add_element( Element(name, nullptr) );
        SWEET_ASSERT( element );
        elements_.push_back( element );
    }
    
    void end_element()
    {
        SWEET_ASSERT( !elements_.empty() );    
        elements_.pop_back();
    }   

    void attribute( const std::string& name, const std::string& value )
    {
        SWEET_ASSERT( !name.empty() );
        SWEET_ASSERT( !elements_.empty() );
        SWEET_ASSERT( elements_.back() );
        elements_.back()->add_attribute( Attribute(name, value) );
    }
    
    void lalr_error( int line, int column, int /*error*/, const char* format, va_list args ) override
    {
        char message [1024];
        vsnprintf( message, sizeof(message), format, args );
        message[sizeof(message) - 1] = 0;
        error_policy_->error( true, "%s(%d) : %s", filename_, line, message );
    }
};

static void string_( PositionIterator<istream_iterator<unsigned char>> begin, PositionIterator<istream_iterator<unsigned char>> end, std::string* lexeme, const void** /*symbol*/, PositionIterator<istream_iterator<unsigned char>>* position, int* lines )
{
    SWEET_ASSERT( lexeme );
    SWEET_ASSERT( lexeme->length() == 1 );
    SWEET_ASSERT( position );
    SWEET_ASSERT( lines );

    PositionIterator<istream_iterator<unsigned char>> i = begin;
    int terminator = lexeme->at( 0 );
    SWEET_ASSERT( terminator == '\'' || terminator == '"' );
    lexeme->clear();
    
    while ( i != end && *i != terminator )
    {
        if ( *i != '&' )
        {
            *lexeme += *i;
            ++i;
        }
        else
        {
            ++i;            
            std::string reference;
            while ( i != end && *i != terminator && *i != ';' )
            {
                reference += *i;
                ++i;
            }
            
            if ( i != end && *i != terminator )
            {
                SWEET_ASSERT( *i == ';' );
                ++i;
            }

            struct ReferenceMap
            {
                const char* reference;
                const char* replacement;
            };

            static const ReferenceMap REFERENCE_MAP[] =
            {
                { "amp",  "&"  },
                { "lt",   "<"  },
                { "gt",   ">"  },
                { "quot", "\"" },
                { nullptr, nullptr }
            };

            const ReferenceMap* map = REFERENCE_MAP;
            while ( map->reference != 0 && reference != map->reference )
            {    
                ++map;
            }

            if ( map->replacement != nullptr )
            {
                lexeme->append( map->replacement );
            }
        }
    }
    
    if ( i != end )
    {
        ++i;
    }
    
    *position = i;
    *lines = 0;
}

static void* begin_element( XmlParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->begin_element( nodes[1].lexeme() );
    return nullptr;
}

static void* end_element( XmlParserContext* context, const ParserNode<char>* /*nodes*/, size_t /*length*/ )
{
    context->end_element();
    return nullptr;
}

static void* attribute( XmlParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( nodes[0].lexeme(), nodes[2].lexeme() );
    return nullptr;
}

XmlParser::XmlParser( const char* filename, Element* element, error::ErrorPolicy* error_policy )
{
    SWEET_ASSERT( filename );
    SWEET_ASSERT( error_policy );

    std::ifstream stream( filename, std::ios::binary );
    error_policy->error( !stream.is_open(), "Opening '%s' failed", filename );
    if ( stream.is_open() )
    {
        parse( filename, stream, element, error_policy );
    }
}

XmlParser::XmlParser( const wchar_t* filename, Element* element, error::ErrorPolicy* error_policy )
{
    SWEET_ASSERT( filename );
    SWEET_ASSERT( error_policy );
    
    std::ifstream stream( narrow(filename).c_str(), std::ios::binary );
    error_policy->error( !stream.is_open(), "Opening '%s' failed", narrow(filename).c_str() );
    if ( stream.is_open() )
    {
        parse( narrow(filename).c_str(), stream, element, error_policy );
    }
}

XmlParser::XmlParser( std::istream& stream, Element* element, error::ErrorPolicy* error_policy )
{
    parse( "", stream, element, error_policy );
}

void XmlParser::parse( const char* filename, std::istream& stream, Element* element, error::ErrorPolicy* error_policy )
{
    SWEET_ASSERT( error_policy );
    
    stream.unsetf( std::iostream::skipws );
    stream.exceptions( std::iostream::badbit );
    
    XmlParserContext context( filename, element, error_policy );
    Parser<PositionIterator<istream_iterator<unsigned char>>, void*, char> parser( xml_parser_state_machine, &context );
    parser.lexer_action_handlers()
        ( "string", &string_ )
    ;
    parser.parser_action_handlers()
        ( "begin_element", bind(&begin_element, &context, _2, _3) )
        ( "end_element", bind(&end_element, &context, _2, _3) )
        ( "attribute", bind(&attribute, &context, _2, _3) )
    ;
    
    parser.parse( PositionIterator<istream_iterator<unsigned char> >(istream_iterator<unsigned char>(stream), istream_iterator<unsigned char>()), PositionIterator<istream_iterator<unsigned char> >() );
    error_policy->error( !parser.accepted() || !parser.full(), "Parsing '%s' failed", filename );
}
