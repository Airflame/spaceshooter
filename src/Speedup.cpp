#include "Speedup.h"

Speedup::Speedup( int posx, int posy )
{
    radius = 10;
    entity.setRadius( radius );
    entity.setOrigin( radius, radius );
    entity.setPosition( posx, posy );
    entity.setFillColor( sf::Color( 0, 0, 0 ) );
    entity.setOutlineThickness( 2 );
    entity.setOutlineColor( sf::Color( 0, 255, 0 ) );
    cpos = entity.getPosition();
}


void Speedup::respawn( sf::Vector2f inpos )
{
    entity.setPosition( inpos );
    cpos = inpos;
}
