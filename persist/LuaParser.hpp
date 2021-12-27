#pragma once

#include <istream>

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
    LuaParser( const char* filename, Element* element );
    LuaParser( const wchar_t* filename, Element* element );
    LuaParser( std::istream& stream, Element* element );

private:    
    void parse( const char* filename, std::istream& stream, Element* element );
};

}
