#include "../include/Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy( int posx, int posy )
{
    radius = 15;
    slide = 0;
    entity.setPointCount( 4 );
    entity.setPoint(0, sf::Vector2f(0, -radius-radius/2));
    entity.setPoint(1, sf::Vector2f(radius, radius));
    entity.setPoint(2, sf::Vector2f(0, radius/2));
    entity.setPoint(3, sf::Vector2f(-radius, radius));
    entity.setPosition( posx, posy );
    entity.setFillColor( sf::Color( 0, 0, 0 ) );
    entity.setOutlineThickness( 2 );
    entity.setOutlineColor( sf::Color( 255, 0, 0 ) );
    cpos = entity.getPosition();
    exist = false;
    vconstant = 150;
}

void Enemy::create( int posx, int posy )
{
    entity.setPosition( posx, posy );
    exist = true;
}

void Enemy::movement( float dt )
{
    speed = vconstant*dt;
    entity.move( cos( mangle * M_PI/180 ) * speed, sin( mangle * M_PI/180 ) * speed );
}

void Enemy::update( sf::Vector2f mpos )
{
    angle = getangle( mpos, cpos );
    cpos = entity.getPosition();
    entity.setRotation( angle );
    mangle = angleconv( angle );
}
