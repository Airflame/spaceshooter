#include "Bullet.h"

Bullet::Bullet()
{
    radius = 3;
    maxlife = 5;
    entity.setRadius( radius );
    entity.setOrigin( radius, radius );
    entity.setFillColor( sf::Color( 0, 0, 0 ) );
    entity.setOutlineThickness( 1 );
    entity.setOutlineColor(sf::Color(255, 255, 255));
    exist = false;
    vconstant = 1000;
}

void Bullet::create( sf::Vector2f argp, float arga, float dt )
{
    if( exist == false )
    {
        cpos = argp;
        angle = angleconv( arga );
        entity.setPosition( cpos );
        life = maxlife;
        exist = true;
    }
}

void Bullet::fire( float dt )
{
    speed = vconstant*dt;
    entity.move( cos( angle * M_PI/180 ) * speed, sin( angle * M_PI/180 ) * speed );
    cpos = entity.getPosition();
}

void Bullet::lifealt( float dt )
{
    if( life <= 0 && exist )
    {
        life = maxlife;
        exist = false;
    }
    if( life > 0 && exist )
        life -= dt;
}
