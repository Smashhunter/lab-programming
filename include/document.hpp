#pragma once
#include <string>
#include <vector>
#include <memory>
#include "figures.hpp"

class Document
{
private:
    std::vector<std::unique_ptr<Figure>> figures;
    std::string path;
public:
    Document(std::string path);
    Document();
};
