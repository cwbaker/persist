//
// PathFilter.ipp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "PathFilter.hpp"
#include "functions.hpp"
#include <persist/assert.hpp>

using namespace persist;

PathFilter::PathFilter( const std::filesystem::path& path )
: path_( path )
{
}

std::string PathFilter::to_memory( const std::string& value ) const
{
    std::filesystem::path path( widen(value) );
    if ( !path.empty() && !path.is_absolute() )
    {
        path = path_ / path;
    }
    return path.string();
}

std::wstring PathFilter::to_memory( const std::wstring& value ) const
{
    std::filesystem::path path( value );
    if ( !path.empty() && !path.is_absolute() )
    {
        path = path_ / path;
    }
    return path.wstring();
}

std::string PathFilter::to_archive( const std::string& value ) const
{
    assert( value.empty() || std::filesystem::path(value).is_absolute() );
    
    std::filesystem::path relative_path;
    if ( !value.empty() )
    {
        relative_path = relative( std::filesystem::path(value), path_ );
    }
    return relative_path.string();
}

std::wstring PathFilter::to_archive( const std::wstring& value ) const
{
    assert( value.empty() || std::filesystem::path(value).is_absolute() );
 
    std::filesystem::path relative_path;
    if ( !value.empty() )
    {
        relative_path = relative( std::filesystem::path(value), path_ );
    }
    return relative_path.wstring();
}

/**
// Express \e path as a path relative to \e base_path.
//
// If this \e base_path is empty or \e base_path and \e path are on different
// drives then no conversion is done and \e path is returned.
//
// @param path
//  The path to get a relative path to.
//
// @param base_path
//  The path to convert \e path to be relative from.
// 
// @return
//  The path \e path expressed relative to \e base_path.
*/
std::filesystem::path PathFilter::relative( const std::filesystem::path& path, const std::filesystem::path& base_path )
{
    // If the base path is empty or the path are on different drives then no 
    // conversion is done.
    if ( base_path.empty() || (base_path.has_root_name() && path.has_root_name() && base_path.root_name() != path.root_name()) )
    {
        return path;
    }

    // Find the first elements that are different in both of the paths.
    std::filesystem::path::const_iterator i = base_path.begin();
    std::filesystem::path::const_iterator j = path.begin();
    while ( i != base_path.end() && j != path.end() && *i == *j )
    {
        ++i;
        ++j;
    }
    
    // Add a leading parent element ("..") for each element that remains in the 
    // base path.
    const char* PARENT = "..";
    const char* SEPARATOR = "/";
    std::string relative_path;
    while ( i != base_path.end() )
    {
        relative_path.append( PARENT );
        relative_path.append( SEPARATOR );
        ++i;
    }

    // Add the remaining elements from the related path.
    if ( j != path.end() )
    {
        relative_path.append( j->generic_string() );
        ++j;
        while ( j != path.end() ) 
        {
            relative_path.append( SEPARATOR );
            relative_path.append( j->generic_string() );
            ++j;
        }
    }
    
    return std::filesystem::path( relative_path );
}

PathFilter persist::path_filter( const std::filesystem::path& path )
{
    return PathFilter( path );
}
