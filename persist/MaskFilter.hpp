#pragma once

#include <string>

namespace error
{

class ErrorPolicy;

}

namespace persist
{

/**
// @internal
//
// A simple filter that uses an array of structures to convert from an
// integer mask value into a string.
//
// If no mask conversions can be found when converting to a string then the
// integer value is simply written out.
//
// If no mask conversions can be found when converting to an integer from a 
// string value that begins with a digit then atoi() is used to convert the 
// value to an integer.  If the string begins with a letter and there is no 
// matching name then an exception is thrown.
*/
class MaskFilter
{
public:
    struct Conversion
    {
        int m_value;
        const char* m_name;
    };

private:
    const Conversion* m_conversions; ///< The array of Conversion structures that defines the mapping between text and mask values.
    mutable std::string m_string; ///< The string value that gets returned when to_archive() is called.

public:
    MaskFilter( const Conversion* conversions );
    int to_memory( const std::string& value, error::ErrorPolicy& error_policy ) const;
    const std::string& to_archive( int value ) const;

private:
    static bool in( int character, const char* separators );
    static bool compare( std::string::const_iterator begin, std::string::const_iterator end, const char* value );
};

MaskFilter mask_filter( const MaskFilter::Conversion* conversions );

}
