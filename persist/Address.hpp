#pragma once

namespace persist
{

class Address
{
    const void* m_address; ///< The identifier.
    void* m_raw_ptr; ///< The address of the identified object.
    void* m_smart_ptr; ///< The address of the smart pointer that manages the object (if any).

    public:
        Address( const void* address, void* raw_ptr, void* smart_ptr );
        const void* address() const;
        void* raw_ptr() const;
        void* smart_ptr() const;
        bool operator<( const Address& address ) const;
};

}
