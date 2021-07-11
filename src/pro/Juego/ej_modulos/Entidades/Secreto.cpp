#include "Secreto.h"

Secreto::Secreto(){
    sprite=NULL;
    motor=NULL;
    x=0;
    y=0;
   
    height=0;
    width=0;
    i = 0;
    current_coin_frame = 0;
    tipo=0;
    
}

Secreto::Secreto(int x_ini, int y_ini, int t){

    sprite = new Sprite();
    if(t==1){
        sprite->setTexture("Secreto1", "png");
    }
    else if(t==2){
        sprite->setTexture("Secreto2", "png");
    }
    else{
        sprite->setTexture("Secreto5", "png");

    }
    tipo=t;
    //sprite->setScale(0.1, 0.1);
    //sprite->setFrameSprite(0,0,60,60);

    x = x_ini;
    y = y_ini;
    height = sprite->getBounds("global").height;
    width = sprite->getBounds("global").width;
    setPosition(x,y);
    i = 0;
    current_coin_frame = 0;
    
    motor = Motor::Instance();
    if((t==1&&Guardar::Instance()->getSecreto1()==1)||(t==2&&Guardar::Instance()->getSecreto2()==1)||(t==3&&Guardar::Instance()->getSecreto3()==1)){
        this->~Secreto();
    }
}

Secreto::~Secreto(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
}

void Secreto::setPosition(int n1, int n2){
    if(sprite!=NULL)
        sprite->setPosition(x,y);
    x=n1;
    y=n2;
}


void Secreto::render(float tick){
    tick = 0.f;
    
    if(sprite!=NULL)
        motor->ventanaDibuja(sprite->getSprite());
}



void Secreto::onCollisionPlayer(int g){
    g=0;
    Player *player = Player::Instance();
   
    if(sprite != NULL){
        if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            motor->getSonidoEvolucion()->Play(); //* cambiar sonido misterio
            if(tipo==1)
                Guardar::Instance()->setMonedas(1);
            else if(tipo==2)
                Guardar::Instance()->setMonedas(2);
            else
                Guardar::Instance()->setMonedas(3);

            this->~Secreto(); 
        }
    }
   
}

void Secreto::updatemover(){
  
  /*
    if(sprite!=NULL){
        if(clock.getElapsedTime().asSeconds() > 0.1f){
            if(current_coin_frame>=i){
                current_coin_frame = 0;
            }else{
                current_coin_frame++;
            }
            sprite->setFrameSprite( current_coin_frame * 60, 0, 60, 60);
            clock.restart();
        }
    }
   */ 
    
}






