#pragma once

#include "types.hpp"
#include "ObjectGuard.ipp"

namespace persist
{

template <class Archive>
void save( Archive& archive, int mode, const char* name, bool& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, bool& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, bool& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, char& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, signed char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, signed char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, signed char& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, unsigned char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, unsigned char& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, unsigned char& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, wchar_t& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, wchar_t& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, wchar_t& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, short& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, short& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, short& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, unsigned short& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, unsigned short& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, unsigned short& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, int& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, int& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, int& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, unsigned int& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, unsigned int& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, unsigned int& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, long& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, long& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, long& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, unsigned long& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, unsigned long& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, unsigned long& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, float& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, float& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, float& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

template <class Archive>
void save( Archive& archive, int mode, const char* name, double& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE, 1 );
    archive.value( "value", value );
}

template <class Archive>
void load( Archive& archive, int mode, const char* name, double& value )
{
    assert( mode == MODE_VALUE );
    (void) mode;
    ObjectGuard<Archive> guard( archive, name, 0, MODE_VALUE );
    archive.value( "value", value );
}

template <class Archive>
void resolve( Archive& archive, int /*mode*/, double& /*value*/ )
{
    ObjectGuard<Archive> guard( archive, 0, 0, MODE_VALUE );
}

}
