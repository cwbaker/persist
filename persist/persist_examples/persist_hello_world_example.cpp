
#include <persist/persist.hpp>
#include <persist/XmlWriter.ipp>
#include <persist/XmlReader.ipp>
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
