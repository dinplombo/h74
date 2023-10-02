#ifndef CONSOL_SOURCE_HPP
#define CONSOL_SOURCE_HPP

#include "stream_base.hpp"

namespace AbsMessage
{

class ConsolSource : public StreamBase{
public: 
    ConsolSource();
    ~ConsolSource() override = default;
    
};

 }// namespace AbsMessage

#endif // CONSOL_SOURCE_HPP