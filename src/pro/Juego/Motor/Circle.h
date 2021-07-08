#ifndef CIRCLE_H
#define CIRCLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> 
#include <vector>
#include "Motor.h"

class Circle{

    public:
        Circle();
        ~Circle();

        //Funciones de color y texturas
        void setFillColor(int,int,int);
        void setFillColor(sf::Color);
        void setOutlineThickness(float);
        void setOutlineColor(int, int, int);

        //Funciones comunes SET de posicón, escala, tamaño y rotación.
        void setSize(float);
        void setPosition(float, float);
        void setScale(float, float);
        void setRotation(float);

        //Funciones básicas de colisiones y posición
        sf::FloatRect getGlobalBounds();
        sf::FloatRect getLocalBounds();
        float getXPosition();
        float getYPosition();

        //Funciones GET básicas del objeto
        sf::CircleShape getCircle();
        void drawCircle();
        float getRotation();
        const sf::Vector2f getScale();

        //Funciones opcionales
        void move(float, float);

    private:
        sf::CircleShape *circle = NULL;
        Motor *m = NULL;
};
#endif