#include "consol_source.hpp"

#include <iostream>

namespace AbsMessage{

ConsolSource::ConsolSource()
: StreamBase(std::cin)
{
}

} // namespace AbsMessage