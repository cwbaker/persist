#pragma once

#include "types.hpp"
#include <string>

namespace persist
{

/**
// @internal
//
// An attribute in the tree of Elements and Attributes used when persisting
// text Archives. 
*/
class Attribute
{
    union Value
    {
        const void* m_address;
        bool m_boolean;
        int m_integer;
        unsigned int m_unsigned_integer;
        double m_real;
    };

    std::string m_name; ///< The name.
    BasicType m_type; ///< The basic type.
    Value m_value; ///< The value.
    mutable std::string m_string; ///< The UTF-8 encoded string value.

    public:
        Attribute();
        Attribute( const std::string& name );
        Attribute( const std::string& name, const void* address );
        Attribute( const std::string& name, bool value );
        Attribute( const std::string& name, int value );
        Attribute( const std::string& name, unsigned int value );
        Attribute( const std::string& name, double value );
        Attribute( const std::string& name, const std::string& value );

        const std::string&  name() const;
        BasicType type() const;
        const void* address() const;
        bool boolean() const;
        int integer() const;
        unsigned int unsigned_integer() const;
        double real() const;
        const std::string& string() const;
        void string( std::string* value ) const;
};

}
