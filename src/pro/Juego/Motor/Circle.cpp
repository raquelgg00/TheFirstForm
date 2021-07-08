#include "Circle.h"

Circle::Circle(){
    circle= new sf::CircleShape;
    m = Motor::Instance();
}

Circle::~Circle(){
    if(circle!=NULL){
        delete circle;
        circle=NULL;
    }
}

void Circle::setFillColor(int r, int g, int b){
    circle->setFillColor(sf::Color(r, g, b));
}

void Circle::setFillColor(sf::Color c){
    circle->setFillColor(c);
}

void Circle::setOutlineThickness(float thickness){
    circle->setOutlineThickness(thickness);
}

void Circle::setOutlineColor(int r, int g, int b){
    circle->setOutlineColor(sf::Color(r,g,b));
}


void Circle::setSize(float r){
    circle->setRadius(r);
}

void Circle::setPosition(float x, float y){
    circle->setPosition(x,y);
}

void Circle::setScale(float x, float y){
    circle->setScale(x,y);
}
void Circle::setRotation(float x){
    circle->setRotation(x);
}
void Circle::drawCircle(){
    m->ventanaDibuja(*circle);
}

sf::CircleShape Circle::getCircle(){
    return *circle;
}
sf::FloatRect Circle::getGlobalBounds(){
    return circle->getGlobalBounds();
}
sf::FloatRect Circle::getLocalBounds(){
    return circle->getLocalBounds();
}
float Circle::getXPosition(){
    return circle->getPosition().x;
}
float Circle::getYPosition(){
    return circle->getPosition().y;
}
float Circle::getRotation(){
    return circle->getRotation();
}
const sf::Vector2f Circle::getScale(){
    return circle->getScale();
}
void Circle::move(float x, float y){
    circle->move(x,y);
}