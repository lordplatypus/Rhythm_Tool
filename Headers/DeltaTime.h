#ifndef DELTA_TIME_H_
#define DELTA_TIME_H
#include <SFML/Graphics.hpp>

class DeltaTime
{
public:
    DeltaTime() = default;
    ~DeltaTime() = default;
    void ResetDeltaTime()
    {
        clock_.restart();
    }
    float GetDeltaTime()
    {
        return clock_.restart().asSeconds();
    }

private:
    sf::Clock clock_;
};

#endif