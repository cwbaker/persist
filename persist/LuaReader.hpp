#pragma once

#include "TextReader.hpp"

namespace error
{

class ErrorPolicy;

}

namespace persist
{

class Element;

/**
// Reads Lua archives.
*/
class LuaReader : public TextReader
{
    error::ErrorPolicy& error_policy_;
    
public:
    LuaReader( error::ErrorPolicy& error_policy );
    LuaReader( const TextReader& reader );

    template <class Char, class Type> void read( const Char* filename, const char* name, Type& object );
    template <class Char, class Type> void read( const Char* filename, const char* name, const char* child_name, Type& container );
    template <class Char, class Type, size_t LENGTH> void read( const Char* filename, const char* name, const char* child_name, Type (& values)[LENGTH] );

    template <class Type> void read( std::istream& stream, const char* name, Type& object );
    template <class Type> void read( std::istream& stream, const char* name, const char* child_name, Type& container );
    template <class Type, size_t LENGTH> void read( std::istream& stream, const char* name, const char* child_name, Type (& values)[LENGTH] );

private:
    void parse( const char* filename, Element* element );
    void parse( const wchar_t* filename, Element* element );
    void parse( std::istream& stream, Element* element );
};

}
