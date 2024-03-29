#pragma once

#include "Archive.hpp"
#include "WriterType.hpp"
#include <set>

namespace persist
{

/**
// Base class for archive writers.
//
// Provides support for recording the type information needed to write 
// archives.
*/
template <class DerivedArchive>
class Writer : public Archive
{
public:
    typedef ArchiveTypeWriter archive_type;

private:
    std::set<WriterType<DerivedArchive> > m_types; ///< The types that have been declared for this archive.
    std::set<const void*> m_tracked_addresses; ///< The addresses of the objects that have been tracked by this Writer.

public:
    Writer();
    Writer( ArchiveType type);
    Writer( const Writer<DerivedArchive>& writer );
    void reset();
    void track( const void* address );
    bool is_tracked( const void* address ) const;
    void persist( const std::type_info& type, DerivedArchive& archive, void* object );
    template <class Type> void enter( const char* format, int version, Type& object );
    template <class Type> void declare( const char* name, int flags );
};

}
