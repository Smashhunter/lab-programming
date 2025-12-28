#include "Ball.hpp"
#include "Color.h"
#include "Velocity.h"
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <istream>

Ball::Ball() = default;

/**
 * @brief Конструктор Ball
 * 
 * @param radius радиус шара
 * @param color цвет шара
 */
Ball::Ball(double radius, const Color& color)
{
  r_ = radius;
  cr_ = color;
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void
Ball::setVelocity(const Velocity& velocity)
{
  v_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity
Ball::getVelocity() const
{
  return v_;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void
Ball::draw(Painter& painter) const
{ 
  painter.draw(c_, r_, cr_);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void
Ball::setCenter(const Point& center)
{
  c_ = center;
}

void
Ball::setCollidable(bool flag)
{
  isCol_ = flag;
}

/**
 * @return центр объекта
 */
Point
Ball::getCenter() const
{
  return c_;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double
Ball::getRadius() const
{
  return r_;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double
Ball::getMass() const
{
  return m_;
}

bool
Ball::isCollidable() const
{
  return isCol_;
}

std::istream&
operator>>(std::istream& in, Ball& ball)
{
  double radius;
  Color color;
  Point center, velocity;
  bool isCollidable;

  in >> center >> velocity;
  in >> color;
  in >> radius;
  in >> std::boolalpha >> isCollidable;

  ball = Ball(radius, color);
  ball.setVelocity(Velocity(velocity));
  ball.setCenter(center);
  ball.setCollidable(isCollidable);

  return in;
}