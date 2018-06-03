#include "../include/Player.h"

Player::Player()
{

}

Player::Player( int posx, int posy )
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
    entity.setOutlineColor( sf::Color( 255, 255, 255 ) );
    cpos = entity.getPosition();
    vconstant = 300;
    b_stimer = 0;
    exist = true;
}

Player::~Player()
{
    //dtor
}

bool Player::collision( sf::Vector2f inpos, int inradius )
{
    float dx = abs( cpos.x - inpos.x );
    float dy = abs( cpos.y - inpos.y );
    float distance = sqrt( pow(dx, 2) + pow(dy, 2) );
    if( (int)distance < (radius + inradius) )
        return 1;
    else
        return 0;
}

bool Player::sight( sf::Vector2f inpos )
{
    float dx = abs( cpos.x - inpos.x );
    float dy = abs( cpos.y - inpos.y );
    float distance = sqrt( pow(dx, 2) + pow(dy, 2) );
    if( (int)distance < 600 )
        return 1;
    else
        return 0;
}

void Player::update( sf::Vector2f mpos )
{
    cpos = entity.getPosition();
    angle = getangle( mpos, cpos );
    entity.setRotation( angle );
    mangle = angleconv( angle );
}

void Player::movement( float dt )
{
    speed = vconstant*dt*slide;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        workangle = mangle;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) or slide > 0 )
        entity.move( cos( workangle * M_PI/180 ) * speed, sin( workangle * M_PI/180 ) * speed );
    if( !sf::Mouse::isButtonPressed(sf::Mouse::Left) and slide > 0 )
        slide -= dt;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) and slide < 1 )
        slide += dt;
    if( b_stimer > 0 )
        this->b_speedpowerup( dt );
    if( b_stimer <= 0 )
        this->b_reset();
}

void Player::b_speedpowerup( float dt )
{
    vconstant = 600;
    entity.setOutlineColor( sf::Color( 0, 255, 0 ) );
    b_stimer -= dt;
}

void Player::b_reset()
{
    vconstant = 300;
    entity.setOutlineColor( sf::Color( 255, 255, 255 ) );
    b_stimer = 0;
}
