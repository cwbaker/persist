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
// A filter that uses an array of structures to convert from an integer 
// value into a string.
//
// If no conversion can be found when converting to a string then the integer
// value is simply written out.
//
// If no conversion can be found when converting to an integer from a string
// value that begins with a digit then atoi() is used to convert the value to
// an integer.  If the string begins with a letter and there is no matching
// name then an exception is thrown.
*/
class EnumFilter
{
    public:
        struct Conversion
        {
            int m_value;
            const char* m_name;
        };

    private:
        const Conversion* m_conversions;
        mutable std::string m_string;

    public:
        EnumFilter( const Conversion* conversions );
        int to_memory( const std::string& value, error::ErrorPolicy& error_policy ) const;
        const std::string& to_archive( int value ) const;
};

extern const EnumFilter::Conversion BASIC_TYPES[];
EnumFilter enum_filter( const EnumFilter::Conversion* conversions );

}
