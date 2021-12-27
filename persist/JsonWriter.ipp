//
// JsonWriter.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "JsonWriter.hpp"
#include "basic_types.ipp"
#include "arrays.ipp"
#include "objects.ipp"
#include "pointers.ipp"
#include "void_pointers.ipp"
#include "strings.ipp"
#include "functions.ipp"
#include <persist/assert.hpp>

/**
// Write an object to a JSON archive.
//
// @param filename
//  The name of the JSON archive to write.
//
// @param name
//  The name of the element for the object in the archive.
//
// @param object
//  The object to write.
*/
template <class Char, class Type> 
void 
persist::JsonWriter::write( const Char* filename, const char* name, Type& object )
{
//
// Set the directory that this archive is being written to in the base
// Writer class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to a JSON file. 
//
    TextWriter::write( name, object );
    write( widen(filename).c_str(), get_element() );
}


/**
// Write a container of objects to a JSON archive.
//
// @param filename
//  The name of the file to write to.
//
// @param name
//  The name of the root element.
//
// @param child_name
//  The name of the element for each object stored in the container.
//
// @param container
//  The container to write objects from.
*/
template <class Char, class Type> 
void 
persist::JsonWriter::write( const Char* filename, const char* name, const char* child_name, Type& container )
{
//
// Set the directory that this archive is being written to in the base
// Writer class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to a JSON file. 
//
    TextWriter::write( name, child_name, container );
    write( widen(filename).c_str(), get_element() );
}


/**
// Write an array of objects to a JSON archive.
//
// @param filename
//  The name of the file to write to.
//
// @param name
//  The name of the root element.
//
// @param child_name
//  The name of the element for each object stored in the array.
//
// @param values
//  The array to write objects from.
*/
template <class Char, class Type, size_t LENGTH> 
void 
persist::JsonWriter::write( const Char* filename, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
//
// Set the directory that this archive is being written to in the base
// Writer class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to a JSON file. 
//
    TextWriter::write( name, child_name, values );
    write( widen(filename).c_str(), get_element() );
}


/**
// Write an object to a JSON archive.
//
// @param stream
//  The stream to write the archive to.
// 
// @param name
//  The name of the root element.
// 
// @param object
//  The object to write.
*/
template <class Type> 
void 
persist::JsonWriter::write( std::ostream& stream, const char* name, Type& object )
{
//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to the stream. 
//
    TextWriter::write( name, object );
    write( stream, get_element() );
}


/**
// Write a container of objects to a JSON archive.
//
// @param stream
//  The stream to write the archive to.
//
// @param name
//  The name of the root element.
//
// @param child_name
//  The name of the element for each object stored in the container.
//
// @param container
//  The container to write objects from.
*/
template <class Type> 
void 
persist::JsonWriter::write( std::ostream& stream, const char* name, const char* child_name, Type& container )
{
//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to the stream. 
//
    TextWriter::write( name, child_name, container );
    write( stream, get_element() );
}


/**
// Write an array of objects to a JSON archive.
//
// @param ostream
//  The stream to write to.
//
// @param name
//  The name of the root element.
//
// @param child_name
//  The name of the element for each object stored in the array.
//
// @param values
//  The array to write objects from.
//
// @param length
//  The number of items in the array to write out.
*/
template <class Type, size_t LENGTH> 
void 
persist::JsonWriter::write( std::ostream& stream, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
//
// Create the root element, process the C++ model into a tree of data, and 
// then recursively write this tree out to the stream. 
//
    TextWriter::write( name, child_name, values );
    write( stream, get_element() );
}
