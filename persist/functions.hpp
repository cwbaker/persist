#pragma once

#include <string>
#include <locale>

namespace persist
{

class Archive;

template <class Type> void* create();
template <class Archive, class Type> void persist( Archive& archive, void* object );
std::string narrow( const std::wstring& wide_string, char unknown = '_', const std::locale& locale = std::locale() );
std::wstring widen( const std::string& narrow_string, const std::locale& locale = std::locale() );
std::wstring widen( const wchar_t* narrow_string, const std::locale& locale = std::locale() );

}
