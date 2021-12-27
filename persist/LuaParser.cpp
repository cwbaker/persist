//
// LuaParser.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "LuaParser.hpp"
#include "Element.hpp"
#include "functions.hpp"
#include <lalr/Parser.ipp>
#include <lalr/PositionIterator.hpp>
#include <lalr/ErrorPolicy.hpp>
#include <error/ErrorPolicy.hpp>
#include <assert/assert.hpp>
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
    error::ErrorPolicy* error_policy_;
    
    LuaParserContext( const char* filename, Element* element, error::ErrorPolicy* error_policy )
    : filename_( filename )
    , elements_()
    , error_policy_( error_policy )
    {
        SWEET_ASSERT( filename_ );
        SWEET_ASSERT( error_policy_ );
        SWEET_ASSERT( element );
        elements_.push_back( element );
    }

    void begin_element( const std::string& name )
    {
        SWEET_ASSERT( !name.empty() );
        SWEET_ASSERT( !elements_.empty() );
        SWEET_ASSERT( elements_.back() );
        
        Element* element = elements_.back()->add_element( Element(name, nullptr) );
        SWEET_ASSERT( element != nullptr );
        elements_.push_back( element );
    }
    
    void end_element()
    {
        SWEET_ASSERT( !elements_.empty() );        
        elements_.pop_back();
    }

    void attribute( const Attribute& attribute )
    {
        SWEET_ASSERT( !elements_.empty() );
        SWEET_ASSERT( elements_.back() );
        elements_.back()->add_attribute( attribute );
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

LuaParser::LuaParser( const char* filename, Element* element, error::ErrorPolicy* error_policy )
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

LuaParser::LuaParser( const wchar_t* filename, Element* element, error::ErrorPolicy* error_policy )
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

LuaParser::LuaParser( std::istream& stream, Element* element, error::ErrorPolicy* error_policy )
{
    SWEET_ASSERT( error_policy );
    parse( "", stream, element, error_policy );
}

void LuaParser::parse( const char* filename, std::istream& stream, Element* element, error::ErrorPolicy* error_policy )
{
    SWEET_ASSERT( error_policy );
    
    stream.unsetf( std::iostream::skipws );
    stream.exceptions( std::iostream::badbit );

    LuaParserContext context( filename, element, error_policy );
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
    error_policy->error( !parser.accepted() || !parser.full(), "Parsing '%s' failed", filename );
}
