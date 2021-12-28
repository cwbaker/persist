#pragma once

#include <istream>

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
    JsonParser( const char* filename, Element* element );
    JsonParser( const wchar_t* filename, Element* element );
    JsonParser( std::istream& stream, Element* element );

private:    
    void parse( const char* filename, std::istream& stream, Element* element );
};

}
