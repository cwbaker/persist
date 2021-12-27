//
// JsonReader.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "JsonReader.hpp"
#include "JsonParser.hpp"
#include "Reader.ipp"
#include "Writer.ipp"

using namespace persist;

/**
// Constructor.
*/
JsonReader::JsonReader( error::ErrorPolicy& error_policy )
: TextReader( error_policy ),
  error_policy_( error_policy )
{
}


/**
// Constructor.
//
// @param reader
//  The TextReader to copy.
*/
JsonReader::JsonReader( const TextReader& reader )
: TextReader( reader ),
  error_policy_( reader.error_policy() )
{
}


/**
// Parse the JSON file \e filename into the element and attribute tree rooted
// at \e element.
//
// @param filename
//  The path to the JSON file to read.
//
// @param element
//  The root element of the tree to read into.
*/
void JsonReader::parse( const char* filename, Element* element )
{
    JsonParser parser( filename, element, &error_policy_ );
}


/**
// Parse the JSON file \e filename into the element and attribute tree rooted
// at \e element.
//
// @param filename
//  The path to the JSON file to read.
//
// @param element
//  The root element of the tree to read into.
*/
void JsonReader::parse( const wchar_t* filename, Element* element )
{
    JsonParser parser( filename, element, &error_policy_ );
}


/**
// Parse a stream containing JSON into the element and attribute tree rooted
// at \e element.
//
// @param stream
//  The stream to parse the JSON from.
//
// @param element
//  The root element of the tree to read into.
*/
void JsonReader::parse( std::istream& stream, Element* element )
{
    JsonParser parser( stream, element, &error_policy_ );
}
