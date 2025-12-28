#pragma once
#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball
{
public:
  Ball();
  Ball(double radius, const Color& color);
  void setVelocity(const Velocity& velocity);
  Velocity getVelocity() const;
  void draw(Painter& painter) const;
  void setCenter(const Point& center);
  void setCollidable(bool flag);
  Point getCenter() const;
  double getRadius() const;
  double getMass() const;
  bool isCollidable() const;

private:
  Velocity v_;
  Point c_;
  Color cr_;
  double r_ = 10.0;
  double m_ = 100.0;
  bool isCol_ = true;
};

std::istream& operator>>(std::istream& in, Ball& ball);