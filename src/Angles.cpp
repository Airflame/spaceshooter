#include "../include/Angles.h"

float getangle( sf::Vector2f mpos, sf::Vector2f cpos )
{
    int quarter;
    if( mpos.x - cpos.x > 0 )
    {
        if( mpos.y - cpos.y > 0 )
            quarter = 2;
        else
            quarter = 1;
    }
    else
    {
        if( mpos.y - cpos.y > 0 )
            quarter = 3;
        else
            quarter = 4;
    }
    float dx = abs( mpos.x - cpos.x );
    float dy = abs( mpos.y - cpos.y );
    if( dx == 0 )
        dx = 1;
    if( dy == 0 )
        dy = 1;
    switch( quarter )
    {
    case 1:
        return atan(dx/dy) * 180/M_PI;
    case 2:
        return atan(dy/dx) * 180/M_PI + 90;
    case 3:
        return atan(dx/dy) * 180/M_PI + 180;
    case 4:
        return atan(dy/dx) * 180/M_PI + 270;
    }
    return 0;
}

float angleconv( float arga )
{
    float angle;
    angle = arga - 90;
    if( angle < 0 )
        angle = 360 - ( 0 - angle );
    return angle;
}
