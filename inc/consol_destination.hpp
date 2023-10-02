#ifndef CONSOL_DESTINATION_HPP
#define CONSOL_DESTINATION_HPP

#include "stream_destination.hpp"

namespace AbsMessage
{

class ConsolDestination : public StreamDestination{
public:
    ConsolDestination();
    ~ConsolDestination() override = default;

};

 }// namespace AbsMessage

#endif // CONSOL_DESTINATION_HPP