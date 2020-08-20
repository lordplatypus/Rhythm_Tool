#ifndef MATH_H_
#define MATH_H_
#include <SFML/Graphics.hpp>

class Math
{
public:
    //v0 = current position v1 = end position t = time
    static sf::Vector2f Lerp(sf::Vector2f v0, sf::Vector2f v1, float t) 
    {
        return (1 - t) * v0 + t * v1;
    }
    static float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    } 
};

#endif