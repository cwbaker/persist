#pragma once

#include "Archive.hpp"
#include "ReaderType.hpp"
#include <set>

namespace persist
{

/**
// Base class for DerivedArchive readers.
//
// Provides support for recording the type information needed to read 
// archives.
*/
template <class DerivedArchive>
class Reader : public Archive
{
public:
    typedef ArchiveTypeReader archive_type;

private:
    typename std::set<ReaderType<DerivedArchive> > m_types; ///< The types that have been declared for use with this archive.    
    typename std::set<const ReaderType<DerivedArchive>*, typename ReaderType<DerivedArchive>::less_by_name> m_types_by_name; ///< The types that have been declared for use with this archive ordered by name.

public:
    Reader();
    Reader( const Reader<DerivedArchive>& reader );
    void reset();
    template <class Type> void enter( const char* format, int version, Type& object );
    template <class Type> void declare( const char* name, int flags );
    template <class Type> void* create_and_persist();
};

}
