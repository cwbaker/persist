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
// Lua parser.
*/
class LuaParser
{
public:
    LuaParser( const char* filename, Element* element, error::ErrorPolicy* error_policy );
    LuaParser( const wchar_t* filename, Element* element, error::ErrorPolicy* error_policy );
    LuaParser( std::istream& stream, Element* element, error::ErrorPolicy* error_policy );

private:    
    void parse( const char* filename, std::istream& stream, Element* element, error::ErrorPolicy* error_policy );
};

}
