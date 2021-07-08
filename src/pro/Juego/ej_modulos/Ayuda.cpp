#include "Ayuda.h"

Ayuda::Ayuda(){
    sprite=NULL;
    motor=NULL;
    x=0;
    y=0;
}

Ayuda::Ayuda(int niv,int pos_x, int pos_y){
    x=pos_x;
    y=pos_y;

    motor=Motor::Instance();
    
    sprite=new Sprite();
    switch(niv){
        case 0://primer nivel
            sprite->setTexture("Ayudas/Ayuda0","png");
        break;
        case 2://portal salto
            sprite->setTexture("Ayudas/Ayuda2","png");
        break;
        case 5://portal rebote
            sprite->setTexture("Ayudas/Ayuda5","png");
        break;
        case 6://mecanica mundo 2
            sprite->setTexture("Ayudas/Ayuda6","png");
        break;
        case 7://portal romper
            sprite->setTexture("Ayudas/Ayuda7","png");
        break;
        case 9://portal empujar
            sprite->setTexture("Ayudas/Ayuda9","png");
        break;
        case 11://mecanica mundo 3
            sprite->setTexture("Ayudas/Ayuda11","png");
        break;
        case 13://portal pequeño
            sprite->setTexture("Ayudas/Ayuda13","png");
        break;
    }
    sprite->setPosition(x,y);

}

Ayuda::~Ayuda(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
}



void Ayuda::render(){
    if(sprite!=NULL)
        motor->ventanaDibuja(sprite->getSprite());
}

