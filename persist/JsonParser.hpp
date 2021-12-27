#pragma once

#include <istream>

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
// JSON parser.
*/
class JsonParser
{
public:
    JsonParser( const char* filename, Element* element, error::ErrorPolicy* error_policy );
    JsonParser( const wchar_t* filename, Element* element, error::ErrorPolicy* error_policy );
    JsonParser( std::istream& stream, Element* element, error::ErrorPolicy* error_policy );

private:    
    void parse( const char* filename, std::istream& stream, Element* element, error::ErrorPolicy* error_policy );
};

}
