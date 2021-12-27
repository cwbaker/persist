//
// JsonReader.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#pragma once

#include "JsonReader.hpp"
#include "basic_types.ipp"
#include "arrays.ipp"
#include "objects.ipp"
#include "pointers.ipp"
#include "void_pointers.ipp"
#include "strings.ipp"
#include "functions.ipp"
#include <persist/assert.hpp>

/**
// Read a JSON archive into an object.
//
// @param filename
//  The name of the JSON archive to read.
//
// @param name
//  The name of the top level element.
//
// @param object
//  The object to read the archive into.
*/
template <class Char, class Type> 
void 
persist::JsonReader::read( const Char* filename, const char* name, Type& object )
{
//
// Set the directory that this archive is being written to in the base
// Reader class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != NULL );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been 
// read in into the C++ model.
//
    parse( filename, get_element() );
    TextReader::read( name, object );
}


/**
// Read a JSON archive into a container of objects.
//
// @param filename
//  The name of the JSON archive to read.
//
// @param name
//  The name of the top level element.
//
// @param child_name
//  The name of each child element.
//
// @param container
//  The container of objects to read the archive into.
*/
template <class Char, class Type> 
void 
persist::JsonReader::read( const Char* filename, const char* name, const char* child_name, Type& container )
{
//
// Set the directory that this archive is being written to in the base
// Reader class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != NULL );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been 
// read in into the C++ model.
//
    parse( filename, get_element() );
    TextReader::read( name, child_name, container );
}


/**
// Read a JSON archive into an array of objects.
//
// @param filename
//  The name of the JSON archive to read.
//
// @param name
//  The name of the top level element.
//
// @param child_name
//  The name of each child element.
//
// @param values
//  The array to read the archive into.
*/
template <class Char, class Type, size_t LENGTH> 
void 
persist::JsonReader::read( const Char* filename, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
//
// Set the directory that this archive is being written to in the base
// Reader class so that it can be retrieved later for path filtering.
//
    assert( filename );
    set_filename( widen(filename) );

//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != NULL );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been read 
// in into the C++ model.
//
    parse( filename, get_element() );
    TextReader::read( name, child_name, values );
}


/**
// Read a JSON archive into an object.
//
// @param stream
//  The stream to read the JSON archive from.
//
// @param name
//  The name of the top level element.
//
// @param object
//  The object to read the archive into.
*/
template <class Type> 
void 
persist::JsonReader::read( std::istream& stream, const char* name, Type& object )
{
//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != NULL );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been read 
// in into the C++ model.
//
    parse( stream, get_element() );
    TextReader::read( name, object );
}


/**
// Read a JSON archive into a container.
//
// @param stream
//  The stream to read the JSON archive from.
//
// @param name
//  The name of the top level element.
//
// @param child_name
//  The name of each child element.
//
// @param container
//  The container of objects to read the archive into.
*/
template <class Type> 
void 
persist::JsonReader::read( std::istream& stream, const char* name, const char* child_name, Type& container )
{
//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != 0 );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been read 
// in into the C++ model.
//
    parse( stream, get_element() );
    TextReader::read( name, child_name, container );
}


/**
// Read a JSON archive into an array.
//
// @param stream
//  The stream to read the JSON archive from.
//
// @param name
//  The name of the top level element.
//
// @param child_name
//  The name of each child element.
//
// @param values
//  The array to read the archive into.
*/
template <class Type, size_t LENGTH> 
void 
persist::JsonReader::read( std::istream& stream, const char* name, const char* child_name, Type (& values)[LENGTH] )
{
//
// Clear out the Element and Attribute tree.
//
    assert( get_element() != NULL );
    get_element()->clear();

//
// Parse the JSON file and then process the tree of data that has been read 
// in into the C++ model.
//
    parse( stream, get_element() );
    TextReader::read( name, child_name, values );
}
