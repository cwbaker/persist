//
// Context.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "Context.hpp"
#include <typeinfo>

using namespace persist;

Context::Context( const std::type_info& type, void* context )
: m_type( &type )
, m_context( context )
{
}

void* Context::get_context() const
{
    return m_context;
}

bool Context::operator<( const Context& context ) const
{
    return m_type->before( *context.m_type );
}
