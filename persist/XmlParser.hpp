#pragma once

#include <iostream>

namespace error
{

class ErrorPolicy;

}

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
    XmlParser( const char* filename, Element* element, error::ErrorPolicy* error_policy );
    XmlParser( const wchar_t* filename, Element* element, error::ErrorPolicy* error_policy );
    XmlParser( std::istream& stream, Element* element, error::ErrorPolicy* error_policy );

private:    
    void parse( const char* filename, std::istream& stream, Element* element, error::ErrorPolicy* error_policy );
};

}
