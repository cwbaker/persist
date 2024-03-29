#pragma once

namespace persist
{

/**
// @internal
//
// A scoped guard to provide exception safety when the current element
// and/or mode are changed for an Archive.
*/
template <class Archive>
class ObjectGuard
{
    Archive& m_archive; ///< The archive to object guard.

public:
    ObjectGuard( Archive& archive, const char* name, const void* address, int mode, int size = 0 );
    ~ObjectGuard();
};

}
