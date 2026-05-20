#pragma once

#include <string>

class Track
{
public:
    Track(const std::string& name, const std::string& filePath, int duration);
    const std::string& getName() const;
    const std::string& getFilePath() const;
    int getDuration() const; // Duration in seconds     
private:
    std::string name;
    std::string filePath;
    int duration; // Duration in seconds
};
