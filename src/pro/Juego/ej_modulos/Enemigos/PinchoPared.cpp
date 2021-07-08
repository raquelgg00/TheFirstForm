#include "PinchoPared.h"

PinchoPared::PinchoPared(){
    motor = NULL;
    x = 0;
    y = 0;
    direccion = 0;
    sprite=NULL;
    posicion=NULL;
}

PinchoPared::PinchoPared(int x_ini, int y_ini, int rot){

    motor = Motor::Instance();
    x = x_ini;
    y = y_ini;
    posicion = new FlotanteInterpolado(x, y);
    direccion=0;

    sprite = new Sprite();
    if(rot == 0)
        sprite->setTexture("pinchoarriba", "png");
    else if(rot == 1){
        sprite->setTexture("pinchodrcha", "png");
    }
    else if(rot == 2){
        sprite->setTexture("pinchoabajo", "png");
    }
    else if(rot == 3){
        sprite->setTexture("pinchosizq", "png");
    }
    sprite->setPosition(x,y);
}

PinchoPared::~PinchoPared(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}


void PinchoPared::setPosition(int n1, int n2){
    x=n1;
    y=n2;
}

void PinchoPared::updatemover(){

    if(posicion != NULL){
        posicion->setPositionXY(x, y);
    }
}

void PinchoPared::render(float tick){
    tick = 0.f;
    if(sprite!=NULL){
        sprite->setPosition(x, y);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void PinchoPared::onCollisionPlayer(){
}

void PinchoPared::setColisionesMapa(bool *colisones){
    colisones[0]=false;
}
