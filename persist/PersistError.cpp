//
// PersistError.cpp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "PersistError.hpp"
#include "assert.hpp"
#include <stdarg.h>

using namespace persist;

PersistError::PersistError( const char* format, ... )
: std::runtime_error( "PersistError" )
, what_()
{
	va_list args;
	va_start( args, format );
	char message [2048];
	int length = vsnprintf( message, sizeof(message), format, args );
	va_end( args );
	if ( length >= 0 )
	{
		what_.assign( message, length );
	}
}

const char* PersistError::what() const noexcept
{
	return what_.c_str();
}
