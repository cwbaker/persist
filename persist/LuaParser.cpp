//
// LuaParser.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "LuaParser.hpp"
#include "Element.hpp"
#include "PersistError.hpp"
#include "functions.hpp"
#include <lalr/Parser.ipp>
#include <lalr/PositionIterator.hpp>
#include <lalr/ErrorPolicy.hpp>
#include <persist/assert.hpp>
#include <fstream>
#include <functional>
#include <stdlib.h>

using std::bind;
using std::vector;
using std::istream_iterator;
using std::placeholders::_2;
using std::placeholders::_3;
using namespace lalr;
using namespace persist;

extern const lalr::ParserStateMachine* lua_parser_state_machine;

struct LuaParserContext : public lalr::ErrorPolicy
{
    const char* filename_;
    std::list<Element*> elements_;
    
    LuaParserContext( const char* filename, Element* element )
    : filename_( filename )
    , elements_()
    {
        assert( filename_ );
        assert( element );
        elements_.push_back( element );
    }

    void begin_element( const std::string& name )
    {
        assert( !name.empty() );
        assert( !elements_.empty() );
        assert( elements_.back() );
        
        Element* element = elements_.back()->add_element( Element(name, nullptr) );
        assert( element != nullptr );
        elements_.push_back( element );
    }
    
    void end_element()
    {
        assert( !elements_.empty() );        
        elements_.pop_back();
    }

    void attribute( const Attribute& attribute )
    {
        assert( !elements_.empty() );
        assert( elements_.back() );
        elements_.back()->add_attribute( attribute );
    }

    void lalr_error( int line, int column, int /*error*/, const char* format, va_list args ) override
    {
        char message [1024];
        vsnprintf( message, sizeof(message), format, args );
        message[sizeof(message) - 1] = 0;
        throw PersistError( "%s(%d) : %s", filename_, line, message );
    }
};

static void string_( PositionIterator<istream_iterator<unsigned char>> begin, PositionIterator<istream_iterator<unsigned char>> end, std::string* lexeme, const void** /*symbol*/, PositionIterator<istream_iterator<unsigned char>>* position, int* lines )
{
    assert( lexeme );
    assert( lexeme->length() == 1 );
    assert( position );
    assert( lines );

    PositionIterator<istream_iterator<unsigned char>> i = begin;
    int terminator = lexeme->at( 0 );
    assert( terminator == '\'' || terminator == '"' );
    lexeme->clear();
    
    while ( *i != terminator && i != end )
    {
        if ( *i != '\\' )
        {
            *lexeme += *i;
            ++i;
        }
        else
        {
            ++i;
            if ( i != end )
            {
                switch ( *i )
                {
                    case 'b':
                        *lexeme += '\b';
                        ++i;
                        break;
                    
                    case 'f':
                        *lexeme += '\f';
                        ++i;
                        break;
                    
                    case 'n':
                        *lexeme += '\n';
                        ++i;
                        break;
                    
                    case 'r':
                        *lexeme += '\r';
                        ++i;
                        break;
                    
                    case 't':
                        *lexeme += '\t';
                        ++i;
                        break;
                        
                    case 'x':
                    case 'X':
                    {
                        ++i;
                        int character = 0;
                        while ( i != end && isxdigit(*i) )
                        {
                            character <<= 4;                        
                            if ( *i >= '0' && *i <= '9' )
                            {
                                character += *i - '0';
                            }
                            else if ( *i >= 'a' && *i <= 'f' )
                            {
                                character += *i - 'a' + 10;
                            }
                            else if ( *i >= 'A' && *i <= 'F' )
                            {
                                character += *i - 'A' + 10;
                            }
                            
                            ++i;                            
                        }
                        
                        *lexeme += character;
                        break;
                    }
                        
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    {
                        int character = 0;
                        int count = 0;
                        while ( i != end && count < 3 && *i >= '0' && *i <= '7' )
                        {
                            character <<= 3;
                            character += *i - '0';
                            ++i;
                            ++count;
                        }
                        
                        *lexeme += character;                
                        break;
                    }
                        
                    default:
                        *lexeme += *i;
                        ++i;
                        break;
                }
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

static void* begin_element( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->begin_element( nodes[0].lexeme() );
    return nullptr;
}

static void* end_element( LuaParserContext* context, const ParserNode<char>* /*nodes*/, size_t /*length*/ )
{
    context->end_element();
    return nullptr;
}

static void* nil_attribute( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( Attribute(nodes[0].lexeme()) );
    return nullptr;
}

static void* boolean_attribute( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( Attribute(nodes[0].lexeme(), nodes[2].lexeme() == "true") );
    return nullptr;
}

static void* integer_attribute( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( Attribute(nodes[0].lexeme(), atoi(nodes[2].lexeme().c_str())) );
    return nullptr;
}

static void* real_attribute( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( Attribute(nodes[0].lexeme(), atof(nodes[2].lexeme().c_str())) );
    return nullptr;
}

static void* string_attribute( LuaParserContext* context, const ParserNode<char>* nodes, size_t length )
{
    context->attribute( Attribute(nodes[0].lexeme(), nodes[2].lexeme()) );
    return nullptr;
}

LuaParser::LuaParser( const char* filename, Element* element )
{
    assert( filename );

    std::ifstream stream( filename, std::ios::binary );
    if ( !stream.is_open() )
    {
        throw PersistError( "Opening '%s' failed", filename );
    }
    if ( stream.is_open() )
    {
        parse( filename, stream, element );
    }    
}

LuaParser::LuaParser( const wchar_t* filename, Element* element )
{
    assert( filename );
    
    std::ifstream stream( narrow(filename).c_str(), std::ios::binary );
    if ( !stream.is_open() )
    {
        throw PersistError( "Opening '%s' failed", narrow(filename).c_str() );
    }
    if ( stream.is_open() )
    {
        parse( narrow(filename).c_str(), stream, element );
    }    
}

LuaParser::LuaParser( std::istream& stream, Element* element )
{
    parse( "", stream, element );
}

void LuaParser::parse( const char* filename, std::istream& stream, Element* element )
{
    stream.unsetf( std::iostream::skipws );
    stream.exceptions( std::iostream::badbit );

    LuaParserContext context( filename, element );
    Parser<PositionIterator<istream_iterator<unsigned char>>, void*, char> parser( lua_parser_state_machine, &context );
    parser.lexer_action_handlers()
        ( "string", &string_ )
    ;
    parser.parser_action_handlers()
        ( "begin_element", bind(&begin_element, &context, _2, _3) )
        ( "end_element", bind(&end_element, &context, _2, _3) )
        ( "nil_attribute", bind(&nil_attribute, &context, _2, _3) )
        ( "boolean_attribute", bind(&boolean_attribute, &context, _2, _3) )
        ( "integer_attribute", bind(&integer_attribute, &context, _2, _3) )
        ( "real_attribute", bind(&real_attribute, &context, _2, _3) )
        ( "string_attribute", bind(&string_attribute, &context, _2, _3) )
    ;
    
    parser.parse( PositionIterator<istream_iterator<unsigned char> >(istream_iterator<unsigned char>(stream), istream_iterator<unsigned char>()), PositionIterator<istream_iterator<unsigned char> >() );
    if ( !parser.accepted() || !parser.full() )
    {
        throw PersistError( "Parsing '%s' failed", filename );
    }
}
