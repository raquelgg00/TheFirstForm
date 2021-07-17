#include "Arista.h"

Arista::Arista(){
    sprite=NULL;
    motor=NULL;
    x=0;
    y=0;
   
    height=0;
    width=0;
    i = 0;
    current_coin_frame = 0;
    
}

Arista::Arista(int x_ini, int y_ini){

    sprite = new Sprite();
    sprite->setTexture("Arista", "png");
    sprite->setFrameSprite(0,0,60,60);

    x = x_ini;
    y = y_ini;
    height = sprite->getBounds("global").height;
    width = sprite->getBounds("global").width;
    setPosition(x,y);
    i = 8;
    current_coin_frame = 0;
    
    motor = Motor::Instance();

}

Arista::~Arista(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
}

void Arista::setPosition(int n1, int n2){
    if(sprite!=NULL)
        sprite->setPosition(x,y);
    x=n1;
    y=n2;
}


void Arista::render(float tick){
    tick = 0.f;
    
    if(sprite!=NULL)
        motor->ventanaDibuja(sprite->getSprite());
}



void Arista::onCollisionPlayer(int g){
    g=0;
    Player *player = Player::Instance();
   
    if(sprite != NULL){
        if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            motor->getSonidoEvolucion()->Play();
			
            player->setForma();
            player->setArista(true);

			if (sprite != NULL) {
				delete sprite;
				sprite = NULL;
			}
        }
    }
   
}

void Arista::updatemover(){
    if(sprite!=NULL){
        if(clock.getElapsedTime().asSeconds() > 0.1f){
            if(current_coin_frame>=i-3){
            current_coin_frame = 0;
            }else{
            current_coin_frame++;
            }
            sprite->setFrameSprite( current_coin_frame * 60, 0, 60, 60);
            clock.restart();
        }
    }
    
}






