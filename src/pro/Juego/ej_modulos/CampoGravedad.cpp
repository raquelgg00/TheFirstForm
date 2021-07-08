#include "CampoGravedad.h"

CampoGravedad::CampoGravedad(){
    motor = NULL;
    sprite=NULL;
    posicion=NULL;
    x = 0;
    y = 0;
}

CampoGravedad::CampoGravedad(int x_ini, int y_ini, int t){
    motor = Motor::Instance();
    x = x_ini;
    y = y_ini;
    tipo = t;
    posicion = new FlotanteInterpolado(x, y);

    sprite = new Sprite();

    sprite->setTexture("campoGravedad", "png");
    if(tipo == 0)
        sprite->setFrameSprite(0,0,100,448);
    else if(tipo==1)
        sprite->setFrameSprite(0,192,100,256);
    
    sprite->setPosition(x_ini, y_ini);

}

CampoGravedad::~CampoGravedad(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}


void CampoGravedad::setPosition(int n1, int n2){
    x=n1;
    y=n2;
}

void CampoGravedad::updatemover(){

    if(sprite!=NULL){
        if(clock.getElapsedTime().asSeconds() > 0.1f){
            if(current_coin_frame>=i_max){
                current_coin_frame = 0;
            }
            else{
                current_coin_frame++;
            }

            if(tipo == 0)
                sprite->setFrameSprite(100*current_coin_frame,0,100,448);
            else if(tipo==1)
                sprite->setFrameSprite(100*current_coin_frame,192,100,256);

            clock.restart();
        }
    }
    posicion->setPositionXY(x, y);
}

void CampoGravedad::render(float tick){
    float factor = std::min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void CampoGravedad::onCollisionPlayer(int g){
    g=0;
    Player *player=Player::Instance();
    if(player->getSprite()->getBounds("global").intersects(sprite->getBounds("global"))){
        player->setDirGravedad(0);
        player->reseteaGravedad(true);
    }
}

void CampoGravedad::setColisionesMapa(bool *colisones){
    colisones[0]=false;
}