#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> 
#include <vector>
#include "Motor.h"
class Rectangle{

    public:
        Rectangle();
        ~Rectangle();

        //Funciones de color y texturas
        void setFillColor(int,int,int);
        void setFillColor(sf::Color);
        void setOutlineThickness(float);
        void setOutlineColor(int, int, int);

        //Funciones comunes SET de posicón, escala, tamaño, rotación y origen.
        void setSize(float, float);
        void setPosition(float, float);
        void setScale(float, float);
        void setRotation(float);
        void setOrigin(float, float);

        //Funciones básicas de colisiones y posición
        sf::FloatRect getGlobalBounds();
        sf::FloatRect getLocalBounds();
        float getXPosition();
        float getYPosition();

        //Funciones GET básicas del objeto
        sf::RectangleShape getRectangle();
        void drawRectangle();
        float getRotation();
        const sf::Vector2f getScale();

        //Funciones opcionales
        void move(float, float);
        
    private:
        sf::RectangleShape *rectangle = NULL;
        Motor *m = NULL;
};
#endif