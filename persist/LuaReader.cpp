//
// LuaReader.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "LuaReader.hpp"
#include "LuaParser.hpp"
#include "Reader.ipp"
#include "Writer.ipp"

using namespace persist;

LuaReader::LuaReader( error::ErrorPolicy& error_policy )
: TextReader( error_policy )
, error_policy_( error_policy )
{
}

LuaReader::LuaReader( const TextReader& reader )
: TextReader( reader )
, error_policy_( reader.error_policy() )
{
}

void LuaReader::parse( const char* filename, Element* element )
{
    LuaParser parser( filename, element, &error_policy_ );
}

void LuaReader::parse( const wchar_t* filename, Element* element )
{
    LuaParser parser( filename, element, &error_policy_ );
}

void LuaReader::parse( std::istream& stream, Element* element )
{
    LuaParser parser( stream, element, &error_policy_ );
}
