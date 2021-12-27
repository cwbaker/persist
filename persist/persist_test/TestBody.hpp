#ifndef SWEET_PERSIST_TESTBODY_HPP_INCLUDED
#define SWEET_PERSIST_TESTBODY_HPP_INCLUDED

#include <persist/assert.hpp>
#include <filesystem>

template <class Writer, class Reader, class Model>
struct TestBody
{
    const char* filename_;
    Model written_model_;
    Model read_model_;

    TestBody( const char* filename )
    : filename_( filename )
    , written_model_()
    , read_model_()
    {
        assert( filename );        
        Writer writer;
        written_model_.enter( writer );
        writer.write( filename, "model", written_model_ );
        written_model_.exit( writer );

        read_model_.clear();
        Reader reader;
        read_model_.enter( reader );
        reader.read( filename, "model", read_model_ );
        read_model_.exit( reader );
    }

    ~TestBody()
    {
        std::filesystem::remove( std::filesystem::path(filename_) );
    }
};

#endif
