#include "consol_destination.hpp"

#include "stream_destination.hpp"

#include <string>
#include <iostream>

namespace AbsMessage
{

ConsolDestination::ConsolDestination()
: StreamDestination(std::cout)
{
}

} // namespace AbsMessage