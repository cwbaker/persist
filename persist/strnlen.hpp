#pragma once

#include <stddef.h>

namespace persist
{

size_t strnlen( const char* string, size_t max );
size_t strnlen( const wchar_t* string, size_t max );

}
