#pragma once

#include "TextWriter.hpp"
#include <iostream>

namespace persist
{

class Element;

/**
// Writes LUA archives.
*/
class LuaWriter : public TextWriter
{
public:
    LuaWriter();
    LuaWriter( const TextWriter& writer );

    template <class Char, class Type> void write( const Char* filename, const char* name, Type& value );
    template <class Char, class Type> void write( const Char* filename, const char* name, const char* child_name, Type& container );
    template <class Char, class Type, size_t LENGTH> void write( const Char* filename, const char* name, const char* child_name, Type (& values)[LENGTH] );

    template <class Type> void write( std::ostream& stream, const char* name, Type& object );
    template <class Type> void write( std::ostream& stream, const char* name, const char* child_name, Type& container );
    template <class Type, size_t LENGTH> void write( std::ostream& stream, const char* name, const char* child_name, Type (& values)[LENGTH] );

private:
    void write( const wchar_t* filename, const Element* element );
    void write( std::ostream& ostream, const Element* element );
    void write_element( std::ostream& stream, const Element* element, bool preserve_empty_elements, int depth );
    void write_indent( std::ostream& stream, int indent );
};

}
