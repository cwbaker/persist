#pragma once

#include <persist/assert.hpp>
#include <typeinfo>
#include <string>

namespace persist
{

/**
// @internal
//
// A type that can be created and persisted when reading an archive.
*/
template <class Archive>
class ReaderType
{
public:
    struct less_by_name
    {
        bool operator()( const ReaderType* lhs, const ReaderType* rhs ) const
        {
            assert( lhs && rhs );
            return lhs->compare_by_name( *rhs );
        }
    };

    typedef std::set<ReaderType> set;
    typedef std::set<const ReaderType*, less_by_name> set_by_name;

private:
    const std::type_info* m_type; ///< The std::type_info for the type.
    std::string m_name; ///< The application supplied name for the type.
    int m_flags; ///< Whether or not the type is polymorphic.
    void* (*m_create)(); ///< The function to create an object of the type on the heap.
    void (*m_persist)( Archive&, void* ); ///< The function to persist an object of the type.

public:
    ReaderType( const std::type_info& type, const std::string& name, int flags, void* (*create)(), void (*persist)(Archive&, void*) );
    bool is_polymorphic() const;
    bool is_anonymous() const;
    void* create() const;
    void persist( Archive& archive, void* object ) const;
    bool operator<( const ReaderType& type ) const;
    bool compare_by_name( const ReaderType& type ) const;
};

}
