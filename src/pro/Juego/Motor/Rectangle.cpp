#include "Rectangle.h"

Rectangle::Rectangle(){
    rectangle= new sf::RectangleShape;
    m = Motor::Instance();
}

Rectangle::~Rectangle(){
    if(rectangle!=NULL){
        delete rectangle;
        rectangle=NULL;
    }
}

void Rectangle::setFillColor(int r, int g, int b){
    rectangle->setFillColor(sf::Color(r, g, b));
}
void Rectangle::setFillColor(sf::Color c){
    rectangle->setFillColor(c);
}
void Rectangle::setOutlineThickness(float thickness){
    rectangle->setOutlineThickness(thickness);
}

void Rectangle::setOutlineColor(int r, int g, int b){
    rectangle->setOutlineColor(sf::Color(r,g,b));
}

void Rectangle::setSize(float x, float y){
    rectangle->setSize(sf::Vector2f(x,y));
}

void Rectangle::setPosition(float x, float y){
    rectangle->setPosition(x,y);
}

void Rectangle::setScale(float x, float y){
    rectangle->setScale(x,y);
}

void Rectangle::setRotation(float x){
    rectangle->setRotation(x);
}

sf::RectangleShape Rectangle::getRectangle(){
    return *rectangle;
}
void Rectangle::drawRectangle(){
    m->ventanaDibuja(*rectangle);
}

sf::FloatRect Rectangle::getGlobalBounds(){
    return rectangle->getGlobalBounds();
}
sf::FloatRect Rectangle::getLocalBounds(){
    return rectangle->getLocalBounds();
}

float Rectangle::getXPosition(){
    return rectangle->getPosition().x;
}
float Rectangle::getYPosition(){
    return rectangle->getPosition().y;
}
float Rectangle::getRotation(){
    return rectangle->getRotation();
}
const sf::Vector2f Rectangle::getScale(){
    return rectangle->getScale();
}

void Rectangle::move(float x, float y){
    rectangle->move(x,y);
}

void Rectangle::setOrigin(float x, float y){
    rectangle->setOrigin(x,y);
}