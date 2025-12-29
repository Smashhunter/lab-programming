#pragma once
#include "painter.hpp"
#include <cstddef>

struct Vector2
{
  Vector2(int x, int y);
  Vector2(Vector2& copy);
  Vector2(Vector2&& moved);
  Vector2 operator+(Vector2& vector);
  Vector2 operator-(Vector2& vector);
  Vector2 operator*(int factor);

  int x;
  int y;
};

struct Color
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

class Figure
{
public:
  Figure(Vector2 pivot, size_t width, size_t height);
  ~Figure() = default;
  virtual void draw(Painter* painter);
  virtual void move(Vector2 position);

protected:
  Vector2 pivot;
  size_t width;
  size_t height;
  Color color;
};

class Line : public Figure
{
public:
  Line(Vector2 begin, Vector2 end)
    : Figure(begin, end.x - begin.x, begin.y - end.y)
    , begin(begin)
    , end(end) {};
  void draw(Painter* painter);
  void move(Vector2 position);

protected:
  Vector2 begin;
  Vector2 end;
};

class Ellipse : public Figure
{
public:
  Ellipse(Vector2 center, size_t radiusWidth, size_t radiusHeight)
    : Figure({ center.x - (int)radiusWidth, center.y - (int)radiusHeight },
             radiusWidth * 2,
             radiusHeight * 2)
    , radiusWidth(radiusWidth)
    , radiusHeight(radiusHeight) {};
  void draw(Painter* painter);
  void move(Vector2 position);

protected:
  size_t radiusWidth;
  size_t radiusHeight;
};
