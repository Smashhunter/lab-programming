#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"

class Ball {    
private:
    Velocity _velocity;
    Point _point;
    double _radius;
    Color _color;
public:
    bool isCollideable;
    Ball();
    Ball(const Velocity& v, const Point& p, double radius, Color color, bool isCollide)
        :
        _velocity(v),
        _point(p),
        _radius(radius),
        _color(color),
        isCollideable(isCollide)
    {};
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
