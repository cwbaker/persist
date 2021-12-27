#pragma once

#include <filesystem>

namespace persist
{

/**
// @internal
//
// A simple filter that converts from absolute paths in memory to paths 
// relative to the archive path in an archive.
*/
class PathFilter
{
    const std::filesystem::path& path_; ///< The path to make paths relative to.

public:
    PathFilter( const std::filesystem::path& path );
    std::string to_memory( const std::string& value ) const;
    std::wstring to_memory( const std::wstring& value ) const;
    std::string to_archive( const std::string& value ) const;
    std::wstring to_archive( const std::wstring& value ) const;

private:
    static std::filesystem::path relative( const std::filesystem::path& path, const std::filesystem::path& base_path );
};

PathFilter path_filter( const std::filesystem::path& path );

}
