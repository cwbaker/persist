
# Persist

## Overview

Persist is a C++ library that serializes data to and from streams in XML, JSON, and binary formats.

Features:

- Enumeration conversion between values and text. 
- Bitmask conversion between values and text. 
- Absolute and relative path conversions.
- Polymorphism.
- Multiple and possibly cyclical references to objects.
- Containers `vector`, `list`, `set`, `multiset`, `map`, `multimap`.
- Smart pointers `unique_ptr`, `shared_ptr`, `weak_ptr`.
- Versioned backwards compatibility.
- UTF-8 encoded XML archives.
- JSON archives.
- Binary archives.

Anti features:

- Multiple inheritance is not supported.

### Boost Serialization vs Persist

The main difference between [Boost Serialization](https://www.boost.org/doc/libs/1_76_0/libs/serialization/doc/index.html) and Persist is the way that they handle shared data.  Boost Serialization automatically tracks pointers to shared data and writes out objects by value the first time they are encountered and then by reference for any further occurences.  Persist allows the application to specify when an object is written out by reference and when it is written out by value.  This is a deliberate design decision to simplify the implementation and to allow control of where data shows up in an archive - in my opinion this makes them easier to transform using XSLT and easier to read.  The cost of doing it this way is that the application is then responsible for making sure that all referenced objects are written to an archive and that objects aren't written out by value more than once.

Persist supports conversion of enumerations and bit masks to useful text values for text based archives.  Persist also supports the conversion of paths - converting absolute paths to relative paths when persisted in an archive and back to absolute paths when the archive is read back in.

Boost Serialization handles multiple inheritance, classes that contain reference member variables, works without RTTI, is far more portable, supports `std::optional` and `std::variant`, and has been reviewed and tested extensively by the Boost community.

In summary Boost Serialization is better if you don't need control over where your data appears when written to XML or JSON archives, you don't need your enumerations and bit masks converted to text, you don't need relative paths in your archives, or you don't want the responsibility of determining whether to write an object by value or by reference.

## Installation

Build Persist using [Forge](https://www.github.com/cwbaker/forge#forge) and a C++ compiler (XCode, Visual C++, GCC, or Clang depending on operating system).

**Linux:**

From a Bash shell with GCC and [Forge](https://github.com/cwbaker/forge#forge) installed and available in the path:

~~~sh
git clone git@github.com:cwbaker/persist.git persist
cd persist
git submodule update --init
forge variant=release
./release/bin/persist_examples
~~~

**macOS:**

From a Bash shell with XCode and [Forge](https://github.com/cwbaker/forge#forge) installed and available in the path:

~~~bash
git clone git@github.com:cwbaker/persist.git persist
cd persist
git submodule update --init
forge variant=release
./release/bin/persist_examples
~~~

**Windows:**

From a Visual C++ x64 Native Tools command prompt with [Forge](https://github.com/cwbaker/forge#forge) installed and available in the path:

~~~cmd
git clone git@github.com:cwbaker/persist.git persist
cd persist
git submodule update --init
forge variant=release
.\release\bin\persist_examples.exe
~~~

Linking with external code will require you to add the top level directory (e.g. "`...\persist`") and the per-variant library directory (e.g. "`...\perist\release\lib`") to your compiler's header and library search paths respectively.

## Usage

Persist serializes arbitrary data to and from an `iostream`.  Typically this is a file but can be a buffer in memory or any more complex combination supported by an `iostream`.

The library provides writer and reader objects to serialize data.  Different types of writers and readers are used serialize archives in XML (`XmlWriter`, `XmlReader`), JSON (`JsonWriter`, `JsonReader`), and binary (`BinaryWriter`, `BinaryReader`) formats.

Data is serialized out by creating a writer and calling its `write()` method.  This recursively traverses the data model being serialized using function templates that describe the relationships in the data model.  Similarly data is read in by creating a reader and calling its `read()` method.  This reconstructs the data in memory using the same function templates.

The function templates to traverse the data model are typically provided as `persist()` member function templates of the class being serialized.  This is the intrusive form.  It is the simplest form and most classes use it to serialize their data.

~~~c++
template <class Archive>
void persist( Archive& archive );
~~~

Overloaded function templates can be provided using
`save()`, `load()`, and `resolve()`.  This is the non-intrusive form allowing serialization of classes that can't be extended or if special case handling such as linking are required (see links below).  The simpler intrusive form is implemented using the non-intrusive form by having the default overload for the non-intrusive functions call the `persist()` member function template of the object being serialized.

~~~c++
template <class Archive, class Type> 
void save( Archive& archive, int mode, const char* name, Type& object );

template <class Archive, class Type>
void load( Archive& archive, int mode, const char* name, Type& object );

template <class Archive, class Type>
void resolve( Archive& archive, int mode, Type& object );
~~~

For example the classic "Hello World!" using Persist:

~~~c++
#include <persist/persist.hpp>
#include <string>

using std::string;
using namespace persist;

struct HelloWorld
{
    string message;
    
    template <class Archive> void persist( Archive& archive )
    {
        archive.enter( "HelloWorld", 1, *this );
        archive.value( "message", message );
    }
};

void persist_hello_world_example()
{
    HelloWorld hello_world;
    hello_world.message = "Hello World!";
    XmlWriter xml_writer;
    xml_writer.write( "persist_hello_world_example.xml", "hello_world", hello_world );

    hello_world.message.clear();    
    XmlReader xml_reader;
    xml_reader.read( "persist_hello_world_example.xml", "hello_world", hello_world );
    assert( hello_world.message == "Hello World!" );
}
~~~

The example program produces the following output:

~~~xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<hello_world format="HelloWorld" version="1" message="Hello World!" address="0x7ffeef4da718"/>
~~~

### Cyclic References

Persist supports serialization of cyclic references by allowing objects to be persisted by reference instead of by value.

Serializing by reference uses the address of an object as a unique identifier that can be written out in place of the object's content and used to resolve back to the equivalent object when the serialized archive is read back into memory.  Any referenced object must be serialized somewhere within the archive so that references to it can be properly recovered.

When a serialized archive is read back in it is read using two passes.  The first pass loads the data from the archive back into memory and builds a mapping from each object's address when it was written into the archive to the address that it has been allocated at when read in.  The second pass traverses the data in memory to resolve references made using the old addresses to objects at their new addresses in memory.

To serialize an object by reference instead of by value the application calls
`refer()` instead of `value()` function.  The obvious usage of this is in serializing a raw pointer to an object but it may also be applied to objects with pointer like semantics (e.g. smart pointers) or to containers.  In the latter case the contents of the container are serialized as references rather than as values.

For example a simple network of people with cyclic references from each person to their friends:

~~~c++
#include <persist/persist.hpp>
#include <persist/vector.hpp>
#include <persist/XmlWriter.ipp>
#include <persist/XmlReader.ipp>
#include <string>
#include <vector>

using std::vector;
using std::string;
using namespace persist;

struct Person
{
    string name_;
    vector<Person*> friends_;

    Person()
    : name_(),
      friends_()
    {
    }

    Person( const string& name )
    : name_( name ),
      friends_()
    {
    }

    void add_friend( Person* person )
    {
        friends_.push_back( person );
    }

    template <class Archive> void persist( Archive& archive )
    {
        archive.value( "name", name_ );
        archive.refer( "friends", "friend", friends_ );
    }
};

void persist_cyclic_references_example()
{
    vector<Person> people;
    people.push_back( Person("Alfred") );
    people.push_back( Person("Ben") );
    people.push_back( Person("Camilla") );
    people.push_back( Person("Denise") );

    Person& alfred = people[0];
    Person& ben = people[1];
    Person& camilla = people[2];
    Person& denise = people[3];

    alfred.add_friend( &ben );
    alfred.add_friend( &camilla );
    ben.add_friend( &alfred );
    ben.add_friend( &denise );
    camilla.add_friend( &alfred );
    camilla.add_friend( &ben );
    camilla.add_friend( &denise );
    denise.add_friend( &camilla );
    
    XmlWriter xml_writer;
    xml_writer.write( "persist_cyclic_references_example.xml", "people", "person", people );

    people.clear();
    XmlReader xml_reader;
    xml_reader.read( "persist_cyclic_references_example.xml", "people", "person", people );
}
~~~

The example program produces the following output:

~~~xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<people>
    <person name="Alfred" address="0x7f9103405bd0">
        <friends>
            <friend address="0x7f9103405c00"/>
            <friend address="0x7f9103405c30"/>
        </friends>
    </person>
    <person name="Ben" address="0x7f9103405c00">
        <friends>
            <friend address="0x7f9103405bd0"/>
            <friend address="0x7f9103405c60"/>
        </friends>
    </person>
    <person name="Camilla" address="0x7f9103405c30">
        <friends>
            <friend address="0x7f9103405bd0"/>
            <friend address="0x7f9103405c00"/>
            <friend address="0x7f9103405c60"/>
        </friends>
    </person>
    <person name="Denise" address="0x7f9103405c60">
        <friends>
            <friend address="0x7f9103405c30"/>
        </friends>
    </person>
</people>
~~~

### Polymorphism

Persist supports serializing polymorphic objects.  To do so polymorphic types must be declared with the reader or writer that is doing the serialization so that the `persist()` function of the correct type can be called when the reader or writer is passed a base class pointer to an object.

Polymorphic types are declared with a reader or writer using the `declare()`
function.  The `declare()` function is a function template that takes the true type as a template parameter and the name to use to uniquely identify the type when serialized.

~~~c++
template <class Type> 
void declare( const char* name, int flags );
~~~

See [persist_polymorphism_example.cpp](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_polymorphism_example.cpp) and [persist_polymorphism_example.json](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_polymorphism_example.json).

### Context

Each archive is able to store void pointers to context that can be used by serialization code during reading or writing.  Typically the `type` parameter is provided using the `SWEET_RTTI_TYPEID()` macro on the type of context being provided.

~~~c++
void set_context( const rtti::Type& type, void* context );
void* get_context( const rtti::Type& type ) const;
~~~

### Filters

Persist is able to provide conversion on serialized values with filters.  Filters are provided to convert bitmasks between integer and string values, enumerated values between integer and string values, and paths between absolute and relative.

Mask filters treat integer values like bitmasks and convert the integral value to and from an `|` separated string of application supplied mask values when serializing.

Enum filters treat integer or enumerated values as enumerations and convert the integral value to and from an application supplied string when serializing.

Path filters convert between an absolute path in the application and a relative path in the archive.  The relative path can be relative to any path but it is often most useful to make it relative to the path to the archive.  This allows the archive to be moved around (assuming that any files that it references are also moved so that they remain in the same relative position).

For example a contacts database that uses a mask filter to store the categories of a contact and an enum filter to store the status of a contact:

See [persist_filters_example.cpp](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_filters_example.cpp) and [persist_filters_example.json](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_filters_example.json).

### Links

Path filters, non-intrusive serialization, and stored context can be combined to serialize objects as links to data stored in external files rather than as data stored directly in the serialized archive itself.

For example during the development of a game using textures a serialized archive can be written and read that refers to textures stored in files external to the serialized archive itself.  The textures themselves are managed using a cache of textures that ensures that if the same texture is referenced multiple times each reference refers to the same texture.

Non-intrusive serialization functions `save()`, `load()`, and `resolve()` are written to serialize the textures.  The loading function retrieves a `TextureCache` to retrieve a texture from using the archive's context function.  Path filters are used to convert between the absolute paths used to refer to textures in memory and paths relative to the serialized archive in the archive.

See [persist_links_example.cpp](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_links_example.cpp) and [persist_links_example.json](https://github.com/cwbaker/persist/blob/main/persist/persist_examples/persist_links_example.json).

### Standard Template Library and Boost Support

Additional headers are provided for serializing containers and smart pointers.  The additional headers are given the same base name as the STL header that is included to use the actual type (e.g. include `<persist/list.hpp>` to persist lists or `<persist/shared_ptr.hpp>` to persist shared pointers).

Additional headers only need to be included when their particular type needs to be persisted.  If an additional header is left out then the compiler will generate many errors as it tries to match all of the overloaded save and load function templates.

### Format and Version

Persist identifies serialized archives by format and version.  The format of an archive is a string that must match the expected format when the archive is read in.  The version is used to determine which action to take when loading in an older version of an archive.

The call to `enter()` provides the format and version of the archive that is to be serialized.  When an archive is written the format and version are written to the archive.  Later on when the archive is read back in the format and version are read in and checked against the format passed to the function.  If the format doesn't match an exception is thrown.  Version checking is left to application code as it may wish to perform conversion or allow backwards compatibility.

The application is able to branch and provide different behaviour based on the version of the archive that is read in but this approach has the potential to generate spaghetti code over time.  A nice alternative is to provide an external script (XSLT, Javascript for JSON, or Lua for Lua) that converts between versions that is executed by the application to convert older versions into newer versions.

### Character Encoding

Persist supports both wide and narrow characters.  When serializing text archives strings are converted to UTF-8 encoding in an intermediate tree representation.  Narrow character strings are are assumed to be encoded as either ASCII or UTF-8 already.  Wide character strings are assumed to be encoded as UCS-2 and are converted to UTF-8 by the library when they are put into the intermediate tree representation.

When saving and loading binary archives there is no intermediate represention and thus no conversion of character data.  Strings are saved and loaded directly without conversion.

### Error Handling And Exception Safety

Persist provides strong exception safety when saving objects.  The objects that are being saved are never changed even if an exception is thrown.   However if an exception is thrown the file system has potentially been changed and an incomplete archive may have been written to disk.  If an exception is caught while writing it is recommended that the application removes any files that may have been created for the archive.

Only weak exception safety is provided when reading archives.  If an exception is thrown then no resources are leaked but the model may be left in an inconsistent state.

Any pointers in the model that are serialized by value are guaranteed to be either as they were before the archive was loaded or pointing to valid heap allocated objects.  It is possible to put the data model back in a consistent state without leaking resources by traversing and deleting any pointers that are serialized by value and that are not null. This assumes that the pointers were initialised to null before the archive was loaded.

It is easy to provide strong exception safety when reading archives by reading into temporary objects and swapping these with the actual objects after the read has succeeded.  If the read fails the temporary objects are discarded and the actual objects remain unchanged.
