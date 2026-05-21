#include "presentation/TrackPrinter.hpp"

#include <iostream>

void TrackPrinter::printTrackInfo(const Track &track, bool isCurrent)
{
    std::cout << (isCurrent ? "-> " : "   ") << track.getName() << std::endl;
}
