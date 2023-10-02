#include "file_source.hpp"

#include <iostream>
#include <fstream>

namespace AbsMessage{

namespace{

std::ifstream& open_file(std::string const& a_file_name)
{
    std::ifstream* fileStream = new std::ifstream(a_file_name);
    return *fileStream;
}

} //namespace

FileSource::FileSource(std::string const& a_file_name)
: StreamBase(open_file(a_file_name)) 
{
}


} // namespace AbsMessage