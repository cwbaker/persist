#pragma once

#include <iostream>

namespace persist
{

class Element;

/**
// @internal
//
// XML parser.
*/
class XmlParser
{
public:
    XmlParser( const char* filename, Element* element );
    XmlParser( const wchar_t* filename, Element* element );
    XmlParser( std::istream& stream, Element* element );

private:    
    void parse( const char* filename, std::istream& stream, Element* element );
};

}
