#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include "Angles.h"

class Bullet
{
public:
    sf::CircleShape entity;
    sf::Vector2f cpos;
    int radius;
    bool exist;
    float angle;
    float speed;
    int vconstant;
    float life;
    float maxlife;

    Bullet();
    void create( sf::Vector2f cpos, float angle, float dt );
    void fire( float dt );
    void lifealt( float dt );
};
#endif // BULLET_H
