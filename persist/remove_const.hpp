#pragma once

namespace persist
{

/**
// Remove const from an arbitrary type.
*/
template <class Type>
struct remove_const
{
    typedef Type type;
};

template <class Type>
struct remove_const<const Type>
{
    typedef Type type;    
};

}
