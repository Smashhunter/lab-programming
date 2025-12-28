#include "Dust.hpp"
#include "Painter.h"
#include <cstddef>

Dust::Dust(const Velocity& v, const Point& c, const Color& cr)
{
  v_ = v;
  c_ = c;
  cr_ = cr;
}

void
Dust::draw(Painter& painter) const
{
  painter.draw(c_, r_, cr_);
}

void
Dust::updateLifetime()
{
  ++lifetime_;
}

/**
 * @return центр объекта
 */
Point
Dust::getCenter() const
{
  return c_;
}

/**
 * @return скорость объекта
 */
Velocity
Dust::getVelocity() const
{
  return v_;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void
Dust::setCenter(const Point& center)
{
  c_ = center;
}

size_t
Dust::getLifetime() const
{
  return lifetime_;
}