#include "Molino.h"

Molino::Molino(){
    motor = NULL;
    x = 0;
    y = 0;
    velRotacion = 1;
    direccion = 1;
    posicion=NULL;
    sprite=NULL;
}

Molino::Molino(int x_ini, int y_ini, int dir){
    motor = Motor::Instance();
    x = x_ini;
    y = y_ini;
    posicion = new FlotanteInterpolado(x, y);
    velRotacion = 5;
    direccion = dir;

    sprite = new Sprite();
    sprite->setTexture("Molino", "png");

    float ancho = sprite->getBounds("global").width;
    float alto = sprite->getBounds("global").height;
    sprite->setOrigin(ancho/2.f, alto/2.f);
    sprite->setPosition(x,y);
}

Molino::~Molino(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}


void Molino::setPosition(int n1, int n2){
    x=n1;
    y=n2;
}

void Molino::updatemover(){
    posicion->setPositionXY(x, y);
    float dT = motor->getDeltaTime();
    sprite->setRotation(sprite->getRotation()+velRotacion*dT*direccion);
}

void Molino::render(float tick){
    float factor = std::min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void Molino::onCollisionPlayer(int g){
    g=0;
    Player *player=Player::Instance();
    if(player->getSprite()->getBounds("global").intersects(sprite->getBounds("global"))){
        if(Collision::PixelPerfectTest(player->getSprite()->getSprite(), sprite->getSprite())){
            
            player->setMuere(true);
        }
    }
};

void Molino::setColisionesMapa(bool *colisones){
    colisones[0]=false;
}