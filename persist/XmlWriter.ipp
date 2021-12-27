//
// XmlWriter.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "XmlWriter.hpp"
#include "TextWriter.ipp"
#include "basic_types.ipp"
#include "arrays.ipp"
#include "objects.ipp"
#include "pointers.ipp"
#include "void_pointers.ipp"
#include "strings.ipp"
#include "functions.ipp"
#include <persist/assert.hpp>

namespace persist
{

template <class Char, class Type> 
void XmlWriter::write( const Char* filename, const char* name, Type& object )
{
    assert( filename );
    set_filename( widen(filename) );
    TextWriter::write( name, object );
    write( widen(filename).c_str(), get_element() );
}

template <class Char, class Type> 
void XmlWriter::write( const Char* filename, const char* name, const char* child_name, Type& container )
{
    assert( filename );
    set_filename( widen(filename) );
    TextWriter::write( name, child_name, container );
    write( widen(filename).c_str(), get_element() );
}

template <class Char, class Type, size_t LENGTH> 
void XmlWriter::write( const Char* filename, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
    assert( filename );
    set_filename( widen(filename) );
    TextWriter::write( name, child_name, values );
    write( widen(filename).c_str(), get_element() );
}

template <class Type> 
void XmlWriter::write( std::ostream& stream, const char* name, Type& object )
{
    TextWriter::write( name, object );
    write( stream, get_element() );
}

template <class Type> 
void XmlWriter::write( std::ostream& stream, const char* name, const char* child_name, Type& container )
{
    TextWriter::write( name, child_name, container );
    write( stream, get_element() );
}

template <class Type, size_t LENGTH> 
void XmlWriter::write( std::ostream& stream, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
    TextWriter::write( name, child_name, values );
    write( stream, get_element() );
}

}
