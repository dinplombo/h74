#ifndef FILE_DESTINATION_HPP
#define FILE_DESTINATION_HPP

#include "stream_destination.hpp"

#include <string>

namespace AbsMessage
{

class FileDestination : public StreamDestination{
public:
    FileDestination(std::string const& a_file_name);
    ~FileDestination() override = default;

};

 }// namespace AbsMessage

#endif // FILE_DESTINATION_HPPs