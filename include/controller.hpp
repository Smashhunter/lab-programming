#pragma once
#include "figures.hpp"
#include "document.hpp"
#include <memory>

class Controller
{
public:
  void addFigure(std::unique_ptr<Figure> figure, Document& doc);
  void removeFigure(Figure* figure, Document& doc);
  void saveDocument(Document& doc);
  void exportDocument(Document& doc, std::string path);
  Document& importDocument(std::string path);
  Document& createDocument();
};
