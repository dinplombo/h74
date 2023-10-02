#include "file_destination.hpp"

#include "stream_destination.hpp"

#include <string>
#include <iostream>
#include <fstream>

namespace AbsMessage
{

namespace{

std::fstream& get_existing_or_create_file(std::string const& a_file_name)
{
    static std::fstream fileStream;
    if (!fileStream.is_open())
    {
        fileStream.open(a_file_name, std::ios::app);
    }
    return fileStream;
}

} //namespace

FileDestination::FileDestination(std::string const& a_file_name)
: StreamDestination(get_existing_or_create_file(a_file_name))
{
}

} // namespace AbsMessage

