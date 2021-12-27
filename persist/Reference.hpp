#pragma once

namespace persist
{

/**
// @internal
//
// A reference to an identified address.
*/
class Reference
{
    typedef void (*ResolveFunction)( void* reference, void* raw_ptr, void* smart_ptr );

    const void* m_address; ///< The address of the referenced object.
    void* m_reference; ///< The pointer to where the reference is made from.
    ResolveFunction m_resolve; ///< The function to call to resolve the reference.

public:
    Reference( const void* address, void* reference, void (*resolve)(void* reference, void* raw_ptr, void* smart_ptr) );
    const void* address() const;
    void* reference() const;
    void resolve( void* raw_ptr, void* smart_ptr ) const;
    bool operator<( const Reference& reference ) const;
};

}
