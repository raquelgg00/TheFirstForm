#include "Triangle.h"

Triangle::Triangle(){
    triangle= new sf::CircleShape;
    triangle->setPointCount(3);
    m = Motor::Instance();
}

Triangle::~Triangle(){
    if(triangle!=NULL){
        delete triangle;
        triangle=NULL;
    }
}

void Triangle::setFillColor(int r, int g, int b){
    triangle->setFillColor(sf::Color(r, g, b));
}

void Triangle::setFillColor(sf::Color c){
    triangle->setFillColor(c);
}

void Triangle::setOutlineThickness(float thickness){
    triangle->setOutlineThickness(thickness);
}

void Triangle::setOutlineColor(int r, int g, int b){
    triangle->setOutlineColor(sf::Color(r,g,b));
}

sf::CircleShape Triangle::getTriangle(){
    return *triangle;
}
void Triangle::drawTriangle(){
    m->ventanaDibuja(*triangle);
}

void Triangle::setSize(float r){
    triangle->setRadius(r);
}

void Triangle::setPosition(float x, float y){
    triangle->setPosition(x,y);
}
void Triangle::setScale(float x, float y){
    triangle->setScale(x,y);
}
void Triangle::setRotation(float x){
    triangle->setRotation(x);
}
sf::FloatRect Triangle::getGlobalBounds(){
    return triangle->getGlobalBounds();
}
sf::FloatRect Triangle::getLocalBounds(){
    return triangle->getLocalBounds();
}
float Triangle::getXPosition(){
    return triangle->getPosition().x;
}
float Triangle::getYPosition(){
    return triangle->getPosition().y;
}
float Triangle::getRotation(){
    return triangle->getRotation();
}
const sf::Vector2f Triangle::getScale(){
    return triangle->getScale();
}

void Triangle::move(float x, float y){
    triangle->move(x,y);
}