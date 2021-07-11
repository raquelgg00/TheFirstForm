#include "Sensor.h"

Sensor::Sensor(){
    p = NULL;
    motor = NULL;
    sprite = NULL;
    x = 0;
    y = 0;
    velx = 0;
    vely = 0;
    presionado = false;
}

Sensor::Sensor(int x_ini, int y_ini){

    p = Player::Instance();
    motor = Motor::Instance();

    sprite=new Sprite();
    sprite->setTexture("interruptor2","png");
    sprite->setFrameSprite(0,0,70,70);
    sprite->setPosition(x_ini, y_ini);

    x = x_ini;
    y = y_ini;
    velx = 0.f;
    vely = 0.f;
    presionado = false;
    tiene_que_sonar = false;
}

Sensor::~Sensor(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
}


void Sensor::setPosition(int n1, int n2){
    if(sprite != NULL)
        sprite->setPosition(x,y);

    x=n1;
    y=n2;
}


void Sensor::updatemover(){
    setPosition(x,y);
    if(presionado){
        sprite->setFrameSprite(140, 0, 70, 70);
        if(tiene_que_sonar){
            Motor::Instance()->getSonidoSensor()->Play();
            tiene_que_sonar = false;
        }
    }
    else{
        sprite->setFrameSprite(0,0,70,70);      
        tiene_que_sonar = true;
    }
}

void Sensor::render(float tick){
    tick=0.f;
    motor->ventanaDibuja(sprite->getSprite());
}

void Sensor::onCollisionPlayer(int g){
    g=0;
}