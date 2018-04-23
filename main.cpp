#include <ctime>
#include <math.h>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Speedup.h"
using namespace std;


int main()
{
    srand( time( NULL ) );
    sf::Clock cl;
    float dt = 0;

    sf::Vector2i mpos;
    sf::Vector2f ampos;
    sf::Vector2f vcenter;
    Player p( 300, 300 );
    Bullet b[1000];
    const int bulletmx = 1000;

    Enemy *e[300];
    const int enemymx = 300;
    for( int i = 0; i < enemymx; i++ )
    {
        e[ i ] = new Enemy( 100, 100);
    }
    e[ 0 ]->create( (int)(rand() % 3000), (int)(rand() % 3000) );

    int enemyindex = 1;
    int bindex = 0;
    float btimer = 1;
    int bpersec = 8;
    sf::Vector2f r;

    r.x = (int)(rand() % 3000);
    r.y = (int)(rand() % 3000);
    Speedup s( r.x, r.y );


    //////TEKSTURA//TLA///////////////////////
    sf::Texture bgtexture;
    int bgx, bgy;
    if (!bgtexture.loadFromFile("bg.png"))
    {
        cout << "TEXTURE LOADING ERROR" << endl;
    }
    bgtexture.setRepeated(true);
    sf::RectangleShape bg[36];
    for( int i = 0; i < 36; i++ )
    {
        bg[ i ].setSize( sf::Vector2f( 500, 500 ) );
        bg[ i ].setTexture( &bgtexture );
        bgx = floor( i % 6 ) * 500;
        bgy = floor( i / 6 ) * 500;
        bg[ i ].setPosition( sf::Vector2f( bgx, bgy ) );
    }
    //////////////////////////////////////////

    int points = 0;
    string spoints;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setColor(sf::Color::White);

    string sgameover = "Game over";
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setCharacterSize(100);
    gameover.setColor(sf::Color::White);
    gameover.setString(sgameover);

    sf::RenderWindow window( sf::VideoMode( 600, 600 ), "rotate" );
    sf::View pview(sf::Vector2f(300, 300), sf::Vector2f(600, 600));

    while( window.isOpen() )
    {
        //////////PUNKTY//////////////////////////
        ostringstream ss;
        ss << points;
        spoints = ss.str();
        text.setString(spoints);
        //////////////////////////////////////////


        //////RYSOWANIE///////////////////////////
        window.clear( sf::Color::Black );
        for( int i = 0; i < 36; i++ )
        {
            window.draw( bg[ i ] );
        }
        for( int i = 0; i < bulletmx; i++ )
        {
            if( b[ i ].exist )
                window.draw( b[ i ].entity );
        }
        window.draw( s.entity );
        if( p.exist )
            window.draw( p.entity );
        for( int i = 0; i < enemymx; i++ )
        {
            if( e[ i ]->exist )
                window.draw( e[ i ]->entity );
        }
        window.draw( text );
        if( !p.exist )
            window.draw( gameover );
        //////////////////////////////////////////


        ///////GRACZ//////////////////////////////
        mpos = sf::Mouse::getPosition( window );
        ampos = window.mapPixelToCoords( mpos );
        if( p.exist )
        {
            p.update( ampos );
            p.movement( dt );
        }
        ////////WIDOK/////////////////////////////
        vcenter = p.cpos;
        if( vcenter.x < 300 )
            vcenter.x = 300;
        if( vcenter.x > 2700 )
            vcenter.x = 2700;
        if( vcenter.y < 300 )
            vcenter.y = 300;
        if( vcenter.y > 2700 )
            vcenter.y = 2700;
        pview.setCenter( vcenter );
        window.setView( pview );
        text.setPosition( vcenter.x - 300, vcenter.y - 300 );
        gameover.setPosition( vcenter.x - 250, vcenter.y - 100 );
        //////////////////////////////////////////


        //////////////POCISKI/////////////////////
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) and btimer >= 1 and p.exist  )
        {
            btimer = 0;
            b[ bindex ].create( p.cpos, p.angle, dt );
            bindex++;
        }
        for( int i = 0; i < bulletmx; i++ )
        {
            if( b[ i ].exist )
            {
                b[ i ].fire( dt );
            }
        }
        btimer += dt*bpersec;
        for( int i = 0; i < bulletmx; i++ )
            b[ i ].lifealt( dt );
        if( bindex >= bulletmx )
            bindex = 0;
        //////////////////////////////////////////


        /////////PRZECIWNICY//////////////////////
        for( int i = 0; i < enemymx; i++ )
        {
            if( e[ i ]->exist and p.exist )
            {
                e[ i ]->update( p.cpos );
                e[ i ]->movement( dt );
                if( p.collision( e[ i ]->cpos, e[ i ]->radius ) )
                    p.exist = false;
                for( int j = 0; j < bulletmx; j++ )
                {
                    if( b[ j ].exist and e[ i ]->collision( b[ j ].cpos, b[ j ].radius ) )
                    {
                        b[ j ].exist = false;
                        r = p.cpos;
                        while( p.sight( r ) )
                        {
                            r.x = (int)(rand() % 3000);
                            r.y = (int)(rand() % 3000);
                        }
                        e[ i ]->create( r.x, r.y );
                        r = p.cpos;
                        while( p.sight( r ) )
                        {
                            r.x = (int)(rand() % 3000);
                            r.y = (int)(rand() % 3000);
                        }
                        points++;
                        if( enemyindex < enemymx - 1 )
                        {
                            e[ enemyindex ]->create( r.x, r.y );
                            enemyindex++;
                        }
                    }
                }
            }
        }
        //////////////////////////////////////////


        /////////BONUSY///////////////////////////
        if( p.collision( s.cpos, s.radius ) and p.b_stimer < 3 )
        {
            r = p.cpos;
            while( p.sight( r ) )
            {
                r.x = (int)(rand() % 3000);
                r.y = (int)(rand() % 3000);
            }
            cout << r.x << ", " << r.y << endl;
            s.respawn( r );
            p.b_stimer = 5;
        }
        //////////////////////////////////////////


        /////RESZTA///////////////////////////////
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window.close();
        }
        window.display();
        dt = cl.restart().asSeconds();
        //////////////////////////////////////////
    }
    return 0;
}
