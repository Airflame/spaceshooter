#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include "Angles.h"

class Player
{
public:
    sf::ConvexShape entity;     //obiekt
    sf::Vector2f cpos;          //pozycja obiektu
    int radius;                 //promien obiektu
    float angle;                //kat odchylenia - obrot w strone myszki
    float mangle;               //kat odchylenia - poruszanie sie
    float workangle;            //kat poruszania - uzywany wewnatrz funkcji poruszania sie
    float speed;                //predkosc poruszania sie
    int vconstant;              //mnoznik predkosci
    float slide;                //poslizg
    float b_stimer;             //zegar od bonusu przyspieszenia
    bool exist;                 //istnienie

    Player();
    Player( int, int );
    virtual ~Player();
    bool collision( sf::Vector2f inpos, int inradius );   //kolizje
    bool sight( sf::Vector2f inpos );       //sprawdzenie czy dane koordynaty sa w zasiegu pola widzenia
    void update( sf::Vector2f mpos );       //ustawienie katow odchylenia
    void movement( float dt );              //poruszanie sie
    void b_speedpowerup( float dt );        //dzialanie bonusu przyspieszenia
    void b_reset();                         //usuniecie efektow bonusu
};

#endif // PLAYER_H

