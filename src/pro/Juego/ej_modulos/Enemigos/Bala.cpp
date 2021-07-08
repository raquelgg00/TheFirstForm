#include "Bala.h"

Bala::Bala(){
    sprite=NULL;
    x=-20;
    y=-20;
    pos_inicial_x=-20;
    pos_inicial_y=-20;
    pos_final_x=0;
    pos_final_x=0;
    tengo_pos_fin=true;
    avanzo_x=0;
    avanzo_y=0;
    posicion = NULL;
}

Bala::Bala(float x_ini, float y_ini){

    pos_inicial_x = x_ini;
    pos_inicial_y = y_ini; 
    pos_final_x =-1.0;
    pos_final_y =-1.0;

    tengo_pos_fin = false;

    sprite = new Sprite();
    sprite->setTexture("Bola", "png");
    sprite->setFrameSprite(0,0,64,64);  
    sprite->setScale(0.3, 0.3);

    sprite->setPosition(pos_inicial_x,pos_inicial_y);    
    x = pos_inicial_x;
    y = pos_inicial_y;

    posicion = new FlotanteInterpolado(x, y);

    avanzo_x=0;
    avanzo_y=0;

    sprite->setPosition(x, y);
    posicion->setPositionXY(x, y);
}

Bala::~Bala(){
    
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}

void Bala::mover(){
    

    float dT = Motor::Instance()->getDeltaTime();
    reloj.restart();
    x = x + avanzo_x*dT;
    y = y + avanzo_y*dT;
    
    posicion->setPositionXY(x, y);
}


void Bala::render(float tick){

    Motor *motor = Motor::Instance();
    float factor = std::min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();
    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void Bala::resetea(){
    x = pos_inicial_x;
    y = pos_inicial_y;
    avanzo_x = 0;
    avanzo_y = 0;
}

bool Bala::getTengoPosFin(){ return tengo_pos_fin; }

float Bala::getavanzo_x(){ return avanzo_x; }

float Bala::getavanzo_y(){ return avanzo_y; }

void Bala::setTengoPosFin(bool b){ tengo_pos_fin = b;}

void Bala::setPosFin_x(float f){ pos_final_x = f; }

void Bala::setPosFin_y(float f){ pos_final_y = f; }

void Bala::setavanzo_x(float f){ avanzo_x = f; }

void Bala::setavanzo_y(float f){ avanzo_y = f; }