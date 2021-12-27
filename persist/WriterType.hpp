#pragma once

#include <typeinfo>
#include <string>

namespace persist
{

/**
// @internal
//
// A named type that can be persisted when writing an archive.
*/
template <class Archive>
class WriterType
{
    const std::type_info* m_type; ///< The std::type_info for the type.
    std::string m_name; ///< The application supplied name for the type.
    int m_flags; ///< Whether or not the type is polymorphic.
    void (*m_persist)( Archive&, void* ); ///< The function to persist an object of the type.

public:
    WriterType( const std::type_info& type, const std::string& name, int flags, void (*persist)(Archive&, void*) );
    const std::string& get_name() const;
    bool is_polymorphic() const;
    bool is_anonymous() const;
    void persist( Archive& archive, void* object ) const;
    bool operator<( const WriterType& type ) const;
};

}
