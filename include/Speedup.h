#ifndef SPEEDUP_H
#define SPEEDUP_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>

class Speedup
{
public:
    sf::CircleShape entity;
    sf::Vector2f cpos;
    int radius;

    Speedup();
    Speedup( int posx, int posy );
    void respawn( sf::Vector2f inpos );
};

#endif // SPEEDUP_H
