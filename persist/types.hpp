#pragma once

namespace persist
{

/**
// The type of an Attribute.
*/
enum BasicType
{
    TYPE_VOID, ///< No type.
    TYPE_ADDRESS, ///< The address of an object.
    TYPE_BOOLEAN, ///< Boolean.
    TYPE_INTEGER, ///< Integer.
    TYPE_UNSIGNED_INTEGER, ///< Unsigned integer.
    TYPE_REAL, ///< Real.
    TYPE_NUMBER, ///< Number.
    TYPE_STRING, ///< String.
    TYPE_OBJECT ///< Object.
};

/**
// Flags that are used to indicate boolean properties of Types.
*/
enum TypeFlags
{
    PERSIST_NORMAL = 0x00, ///< Normal type.
    PERSIST_POLYMORPHIC = 0x01  ///< A polymorphic type.
};

/**
// Flags that are used to indicate boolean properties of objects.
*/
enum ElementFlags
{
    PERSIST_PRESERVE_EMPTY_ELEMENTS = 0x01, ///< The element's children should be written out even if they are empty.
    PERSIST_ANONYMOUS = 0x02  ///< The object's address should not be written out.
};

/**
// The mode of an Archive.
*/
enum Mode
{
    MODE_VALUE, ///< Persist the values of objects.
    MODE_REFERENCE ///< Persist references to objects.
};

}
