#pragma once

#include <typeinfo>

namespace persist
{

/**
// @internal
//
// Associates a type (by rtti::Type) with client supplied context 
// information.
*/
class Context
{
    const std::type_info* m_type;
    void* m_context;

public:
    Context( const std::type_info& type, void* context );
    void* get_context() const;
    bool operator<( const Context& context ) const;
};

}
