#pragma once
#include "Color.h"
#include "Painter.h"
#include "Velocity.h"
#include "Point.h"
#include <cstddef>
#include <istream>

class Dust
{
public:
  Dust(const Velocity& v, const Point& c, const Color& cr);
  void draw(Painter& painter) const;
  size_t getLifetime() const;
  Point getCenter() const;
  Velocity getVelocity() const;
  void setCenter(const Point& center);
  void updateLifetime();

private:
  Velocity v_;
  Point c_;
  Color cr_;
  double r_ = 10.0;
  size_t lifetime_ = 0;
};
