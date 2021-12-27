#pragma once

#include <stdexcept>
#include <string>

namespace persist
{

class PersistError : public std::runtime_error
{
	std::string what_;

public:
	PersistError( const char* format, ... );
	const char* what() const noexcept;
};

}
