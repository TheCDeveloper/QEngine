#pragma once
#include <cmath>


namespace QEngine
{

template<typename T>
class Angle
{
private:
    Angle(T radians) : angle(radians) {}


public:
    static Angle fromDegrees(T degrees) { return Angle(degrees * (M_PI / 180.0)); }
    static Angle fromRadians(T radians) { return Angle(radians); }

    void setDegrees(T degrees) { angle = degrees * (M_PI / 180.0); }
    void setRadians(T radians) { angle = radians; }

    T getDegrees() { return angle * (180.0 / M_PI); }
    T getRadians() { return angle; }


    T angle;
};


struct Colour
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;
};


template<typename T>
class Vector2
{
public:
    Vector2()         : x(0), y(0) {}
    Vector2(T a)      : x(a), y(a) {}
    Vector2(T x, T y) : x(x), y(y) {}

    T x, y;


    Vector2 operator+(const Vector2& a) { return Vector2(x + a.x, y + a.y); }
    Vector2 operator-(const Vector2& a) { return Vector2(x - a.x, y - a.y); }
    Vector2 operator*(const Vector2& a) { return Vector2(x * a.x, y * a.y); }
    Vector2 operator*(const T a)        { return Vector2(x * a, y * a); }
    Vector2 operator/(const Vector2& a) { return Vector2(x / a.x, y / a.y); }
    Vector2 operator/(const T a)        { return Vector2(x / a, y / a); }

    void operator+=(const Vector2& a) { x += a.x; y += a.y; }
    void operator-=(const Vector2& a) { x -= a.x; y -= a.y; }
    void operator*=(const Vector2& a) { x *= a.x; y *= a.y; }
    void operator*=(T a)              { x *= a; y *= a; }
    void operator/=(const Vector2& a) { x /= a.x; y /= a.y; }
    void operator/=(T a)              { x /= a; y /= a; }

    bool operator==(const Vector2& a) { return (x == a.x) && (y == a.y); }
    bool operator>(const Vector2& a)  { return length() > a.length(); }
    bool operator<(const Vector2& a)  { return length() < a.length(); }
    bool operator>=(const Vector2& a) { return length() >= a.length(); }
    bool operator<=(const Vector2& a) { return length() <= a.length(); }


    void unit()       { T len = length(); x /= len; y /= len; };
    Vector2 getUnit() { T len = length(); return Vector2(x / len, y / len); };

    T length() { return std::hypot(x, y); }
};


template<typename T>
struct Rectangle
{
    Vector2<T> position;
    Vector2<T> scale;
};

}
