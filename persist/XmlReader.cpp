//
// XmlReader.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "XmlReader.hpp"
#include "XmlParser.hpp"
#include "Reader.ipp"
#include "Writer.ipp"

using namespace persist;

XmlReader::XmlReader( error::ErrorPolicy& error_policy )
: TextReader( error_policy )
, error_policy_( error_policy )
{
}

XmlReader::XmlReader( const TextReader& reader )
: TextReader( reader )
, error_policy_( reader.error_policy() )
{
}

void XmlReader::parse( const char* filename, Element* element )
{
    XmlParser parser( filename, element, &error_policy_ );
}

void XmlReader::parse( const wchar_t* filename, Element* element )
{
    XmlParser parser( filename, element, &error_policy_ );
}

void XmlReader::parse( std::istream& stream, Element* element )
{
    XmlParser parser( stream, element, &error_policy_ );
}
