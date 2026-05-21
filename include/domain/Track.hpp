#pragma once

#include <string>

class Track
{
public:
    Track(const std::string& name, const std::string& filePath);
    const std::string& getName() const;
    const std::string& getFilePath() const;
private:
    std::string name;
    std::string filePath;
};
