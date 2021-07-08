#ifndef SHAPE_H
#define SHAPE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> 
#include <vector>
#include <math.h>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Convex.h"

class Shape{

    public:
        Shape();
        Shape(char[]);
        ~Shape();

        //Funciones de color y texturas
        void setFillColor(int,int,int);
        void setFillColor(char[]);
        void setBorder(float, int, int, int);

        //Funciones básicas de posición, escala, tamaño y rotación.
        void setSize(float, float = 0); 
        void setConvexPoints(int, float, float);
        void setPosition(float, float);
        void setScale(float, float);
        void setRotation(float);

        //Funciones básicas de colisión y posición
        void getGlobalBounds();
        void getLocalBounds();
        void getXPosition();
        void getYPosition();

        //Funciones básicas GET de la forma
        void drawShape();
        sf::CircleShape getCircle();
        sf::RectangleShape getRectangle();
        sf::CircleShape getTriangle();
        sf::ConvexShape getConvex();
        void getRotation();
        void getScale();

        //Optionals functions
        void move(float, float);

    private:
        char shape_type [10];
        Rectangle *rectangle = NULL;
        Circle *circle = NULL;
        Triangle *triangle = NULL;
        Convex *convex = NULL;
};
#endif