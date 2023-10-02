#ifndef FILE_SOURCE_HPP
#define FILE_SOURCE_HPP

#include "stream_base.hpp"

namespace AbsMessage
{

class FileSource : public StreamBase{
public: 
    FileSource(std::string const& a_file_name);
    ~FileSource() override = default;

};

 }// namespace AbsMessage

#endif // FILE_SOURCE_HPP