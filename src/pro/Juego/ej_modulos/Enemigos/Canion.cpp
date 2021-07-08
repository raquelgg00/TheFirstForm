#include "Canion.h"


Canion::Canion(){
    motor = NULL;
    bala = NULL;
    sprite= NULL;
    x = 0;
    y = 0;
    radio_grande = 0;
    radio_peque = 0;

    // Reloj
    reloj1 = NULL;
    tiempo1 = NULL;
}

Canion::Canion(int x_ini, int y_ini){
    motor = Motor::Instance();
    //bala = new Bala(x,y);
    bala = NULL;
    x = x_ini;
    y = y_ini;
    radio_grande = 600;
    radio_peque = 680;

    sprite=new Sprite();
    sprite->setTexture("canion","png");
    sprite->setOrigin(sprite->getBounds("global").width/2.0, sprite->getBounds("global").height-4);
    sprite->setPosition(x, y);
    sprite->setRotation(180);

    // Reloj
    reloj1 = new sf::Clock();
    tiempo1 = new sf::Time();

}

Canion::~Canion(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(reloj1 != NULL){
        delete reloj1;
        reloj1 = NULL;
    }
    if(tiempo1 != NULL){
        delete tiempo1;
        tiempo1 = NULL;
    }
    if(bala != NULL){
        delete bala;
        bala = NULL;
    }
}

void Canion::setPosition(int n1, int n2){
    sprite->setPosition(x,y);
    x=n1;
    y=n2;
}


void Canion::render(float tick){
    if(bala != NULL)
        bala->render(tick);
        
    motor->ventanaDibuja(sprite->getSprite());
}


void Canion::onCollisionPlayer(int g){
    g=0;
    Player *player=Player::Instance();
    if(bala!=NULL&&bala->getSprite() != NULL){
        if(bala->getSprite()->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            
            player->setMuere(true);
        }
    }
}

void Canion::updatemover(){
    Player *player = Player::Instance();

    sf::FloatRect shape1 = player->getSprite()->getSprite().getGlobalBounds();
    sf::FloatRect shape2 = sprite->getBounds("global");
    float radio1 = shape1.width/2;
    float radio2 = shape2.width/2;
    float dx = (player->getX() + radio1) - (x + radio2);
    float dy = (player->getY() + radio1) - (y + radio2);

    //float distance = std::sqrt((dx * dx) + (dy * dy));
    float distance = pow((dx * dx) + (dy * dy),0.5); 
    float alpha = asin((dx)/(distance));
    alpha = -1 * alpha * 360 / (2*M_PI);

   
    // Posicion de la bala
    if(bala != NULL){
        if(bala->getTengoPosFin()){    
            bala->mover();
        }
    }


    // Si la distancia (personaje, cañon) es < radio de acción
    if(distance < radio_grande && y<player->getY()){
        sprite->setRotation(180+alpha);

        if(distance < radio_peque){
            if(bala != NULL){
                if(bala->getTengoPosFin() == false){

                    bala->setTengoPosFin(true);
                    bala->setPosFin_x(player->getX());
                    bala->setPosFin_y(player->getY());

                    if(distance < 100){
                        bala->setavanzo_x(dx/5.0);
                        bala->setavanzo_y(dy/5.0); 
                    }
                    else if(distance <300){
                        bala->setavanzo_x(dx/10.0);
                        bala->setavanzo_y(dy/10.0); 
                    }
                    else {
                        bala->setavanzo_x(dx/20.0);
                        bala->setavanzo_y(dy/20.0); 
                    }
                }
            }
            *tiempo1 = reloj1->getElapsedTime();
            if(tiempo1->asSeconds()>3){
                if(bala != NULL){
                    delete bala;
                    bala = NULL;
                }
                bala = new Bala(x,y);
                reloj1->restart();

            }   
        }
    }
}

Sprite* Canion::getSpriteBala(){
    if(bala != NULL){
        return bala->getSprite();
    }
    else 
        return NULL;
}