#ifndef ENEMY_H
#define ENEMY_H
#include <Player.h>


class Enemy : public Player
{
public:
    Enemy();
    Enemy( int posx, int posy  );
    void create( int posx, int posy );
    void movement( float dt );
    void update( sf::Vector2f mpos );
};

#endif // ENEMY_H
