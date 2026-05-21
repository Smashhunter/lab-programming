#include "domain/Track.hpp"

Track::Track(const std::string &name, const std::string &filePath):
    name(name), filePath(filePath)
{
}

const std::string &Track::getName() const
{
    return name;
}

const std::string &Track::getFilePath() const
{
    return filePath;
}
