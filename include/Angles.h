#ifndef ANGLES_H_INCLUDED
#define ANGLES_H_INCLUDED
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

float getangle( sf::Vector2f mpos, sf::Vector2f cpos );
float angleconv( float arga );

#endif // ANGLES_H_INCLUDED
