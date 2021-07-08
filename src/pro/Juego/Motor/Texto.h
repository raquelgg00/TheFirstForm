#ifndef TEXTO_H
#define TEXTO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> 
#include "Motor.h"

//Por defecto el texto al crearlo se pinta de blanco, tiene la tipografía Aanekdot.ttf que se encuenta en la carpeta resources > fonts y un tamaño de letra de un 14.

class Texto{

    public:
        //Le tenemos que pasar como parámetro al constructor el texto que queremos que imprima
        Texto();
        ~Texto();
        Texto(std::string);
        //Pasar SOLO el nombre de la fuente con su extensión, meter la fuente en la carpeta resources > fonts (por defecto aplica la aAnekdot.ttf)
        void setFuente(std::string);
        //EStablece el tamaño de la letra del texto
        void setSize(int);
        float getSize();
        void setPosition(float, float);
        void setRotation(float);
        void setOrigin(float, float);
        void setStyle(std::string);
        void setTexto(std::string st){texto->setString(st);};
        //Dibujamos el texto por pantalla (llamamos a Motor.dibujaVentana(sf::Text))
        void drawText();
        void setColor(int, int, int);
        void setColor(int, int, int, int);
        //Le pasamos o (white, black, red, green, cyan, blue, yellow, magenta, transparent)
        void setColor(std::string);

        std::string getTexto();
        std::string getFuente();
        float getXPosition();
        float getYPosition();
        float getRotation();
        float getXOrigin();
        float getYOrigin();
        float getWidthBounds();
        float getHeightBounds();
        sf::FloatRect getGlobalBounds();

    private:
        sf::Font *fuente = NULL;
        sf::Text *texto = NULL;
        std::string font_name = "";
        Motor *m = NULL;

};

#endif