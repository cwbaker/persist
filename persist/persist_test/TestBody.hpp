#ifndef SWEET_PERSIST_TESTBODY_HPP_INCLUDED
#define SWEET_PERSIST_TESTBODY_HPP_INCLUDED

#include <error/ErrorPolicy.hpp>
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
        error::ErrorPolicy error_policy;
        Writer writer( error_policy );
        writer.write( filename, "model", written_model_ );
        read_model_.clear();
        Reader reader( error_policy );
        reader.read( filename, "model", read_model_ );
    }

    ~TestBody()
    {
        std::filesystem::remove( std::filesystem::path(filename_) );
    }
};

#endif
