#ifndef MOTOR_H
#define MOTOR_H
#include <SFML/Graphics.hpp>
#include "Audio.h"
#include "Guardar.h"

class Motor{

    public:
        static Motor* Instance();
        sf::Color new_color(int, int, int);
        void ventanaClear();
        void ventanaClear(int, int, int);
        void ventanaDisplay();
        void ventanaClose();
        bool ventanaIsOpen();
        bool ventanaPollEvent();
        bool eventTypeClosed();
        void setSizeVentana(int,int);
        sf::RenderWindow* getWindow(){return ventana1;};
        sf::Event* getEvent(){return event;};
        void setPlayerCoord(sf::Vector2f v){playercoord = v;};
        void setShader(bool u){useShader = u;};
        
        // Mirar como pasar un sf::Drawable que los engloba a los 3
        void ventanaDibuja(sf::Sprite);
        void ventanaDibujaSinShader(sf::Sprite);
        void ventanaDibuja(sf::Text);
        void ventanaDibuja(sf::RectangleShape);
        void ventanaDibuja(sf::CircleShape); 
        void ventanaDibuja(sf::ConvexShape);

        sf::RectangleShape crearRectangleShape(float, float);
        bool isKeyPressed() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Unknown);};
        bool isKeyPressedRight() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);};
        bool isKeyPressedLeft() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);};
        bool isKeyPressedUp() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);};
        bool isKeyPressedDown() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);};
        bool isKeyPressedSpace() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);};
        bool isKeyPressedEnter() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);};
        bool isKeyPressedEscape() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);};
        bool isKeyPressedNum0() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);};
        bool isKeyPressedNum1() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);};
        bool isKeyPressedNum2() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);};
        bool isKeyPressedNum3() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);};
        bool isKeyPressedNum4() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);};
        bool isKeyPressedNum5() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);};
        bool isKeyPressedP() {return sf::Keyboard::isKeyPressed(sf::Keyboard::P);};
        bool isKeyPressedI() {return sf::Keyboard::isKeyPressed(sf::Keyboard::I);};
        bool isKeyPressedJ() {return sf::Keyboard::isKeyPressed(sf::Keyboard::J);};
        bool isKeyPressedK() {return sf::Keyboard::isKeyPressed(sf::Keyboard::K);};
        bool isKeyPressedL() {return sf::Keyboard::isKeyPressed(sf::Keyboard::L);};
        bool isKeyPressedF() {return sf::Keyboard::isKeyPressed(sf::Keyboard::F);};
        bool isKeyPressedG() {return sf::Keyboard::isKeyPressed(sf::Keyboard::G);};
        bool isKeyPressedQ() {return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);};

        // Camara
        void setCameraCenter(float, float);
        void setCamaraRotation(float);
        float getCamaraRotation(){return camara->getRotation();};
        void setView(int);
        sf::Vector2f getCamaraCenter(){return camara->getCenter();};

        // Colisiones con Player
        bool colisionDerecha(int, int, int, int, int, int, int, int, bool);
        bool colisionIzq(int, int, int, int, int, int, int, int, bool);
        bool colisionAbajo(int, int, int, int, int, int, int, int, bool);
        bool colisionArriba(int, int, int, int, int, int, int, int, bool, bool); // el bool es para ver si es pincho

        //Delta Time
        void setDeltaTime(float delta){deltaTime=delta*20;};
        float getDeltaTime(){return deltaTime;};

        //Sonidos
        Audio* getMusica(){return musica;};
        Audio* getMusicaMenu(){return musicaMenu;};
        Audio* getSonidoMover(){return sonidoMover;};
        Audio* getSonidoSeleccion(){return sonidoSeleccion;};
        Audio* getMusicaAnimacion(){return musicaAnimacion;};
        Audio* getSonidoInicio(){return sonidoInicio;};
        Audio* getSonidoMorision(){return sonidoMorision;};
        Audio* getSonidoEvolucion(){return sonidoEvolucion;};
        Audio* getSonidoNivelCompleto(){return sonidoNivelCompletado;};

        int getTamWidth(){return tamWidth;};
        int getTamHeight(){return tamHeight;};

        void setRadioShader(float r){radio=r;};

    protected:
        Motor();
        ~Motor();
        Motor(const Motor & );
        Motor &operator= (const Motor & );
        void new_ventana(int, int, sf::String);
        void setFramerateLimit(int);
    private:
        static Motor* pinstance;
        sf::RenderWindow *ventana1 = NULL;
        sf::View *camara;
        sf::View *camara2;
        sf::Event *event;
        Audio *musica;
        Audio *musicaMenu;
        Audio *musicaAnimacion;
        Audio *sonidoMover;
        Audio *sonidoSeleccion;
        Audio *sonidoMorision;
        Audio *sonidoInicio;
        Audio *sonidoEvolucion;
        Audio *sonidoNivelCompletado;
        float deltaTime;
        int tamWidth, tamHeight;
        sf::Vector2f playercoord;
        sf::Shader shaderM;
        bool useShader = false;
        float radio=0;
};

#endif

