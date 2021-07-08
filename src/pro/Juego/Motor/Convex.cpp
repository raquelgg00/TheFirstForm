#include "Convex.h"

Convex::Convex(){
    convex= new sf::ConvexShape;
    m = Motor::Instance();
}

Convex::~Convex(){
    if(convex!=NULL){
        delete convex;
        convex=NULL;
    }
}

void Convex::setFillColor(int r, int g, int b){
    convex->setFillColor(sf::Color(r, g, b));
}

void Convex::setFillColor(sf::Color c){
    convex->setFillColor(c);
}

void Convex::setOutlineThickness(float thickness){
    convex->setOutlineThickness(thickness);
}

void Convex::setOutlineColor(int r, int g, int b){
    convex->setOutlineColor(sf::Color(r,g,b));
}

sf::ConvexShape Convex::getConvex(){
    return *convex;
}
void Convex::drawConvex(){
    m->ventanaDibuja(*convex);
}

void Convex::setPointCount(int p){
    convex->setPointCount(p);
}

void Convex::setPoint(int point, float x, float y){
    bool point_exist = false;
    int p = convex->getPointCount();
    for(int i=0; i<p; i++){
        if(i==point){
            point_exist=true;
        }
    }
    if(point_exist==true){
        convex->setPoint(point, sf::Vector2f(x, y));
    }
}

void Convex::setPosition(float x, float y){
    convex->setPosition(x,y);
}
void Convex::setScale(float x, float y){
    convex->setScale(x,y);
}
void Convex::setRotation(float x){
    convex->setRotation(x);
}
sf::FloatRect Convex::getGlobalBounds(){
    return convex->getGlobalBounds();
}
sf::FloatRect Convex::getLocalBounds(){
    return convex->getLocalBounds();
}
float Convex::getXPosition(){
    return convex->getPosition().x;
}
float Convex::getYPosition(){
    return convex->getPosition().y;
}
float Convex::getRotation(){
    return convex->getRotation();
}
const sf::Vector2f Convex::getScale(){
    return convex->getScale();
}
void Convex::move(float x, float y){
    convex->move(x,y);
}