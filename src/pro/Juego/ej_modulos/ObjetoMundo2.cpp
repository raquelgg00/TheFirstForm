#include "ObjetoMundo2.h"


// Constructor
ObjetoMundo2::ObjetoMundo2(){
    motor = NULL;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    activo = true;
    sprite=NULL;
}

// Constructor 2
ObjetoMundo2::ObjetoMundo2(int x_ini, int y_ini){
    motor = Motor::Instance();
    sprite = new Sprite();
    sprite->setTexture("Mundo2", "png");
    x = x_ini;
    y = y_ini;
    sprite->setPosition(x,y);
    activo = true;
    width=sprite->getBounds("global").width;
    height=sprite->getBounds("global").height;
}

// Destructor
ObjetoMundo2::~ObjetoMundo2(){
    if(sprite!=NULL){
        delete sprite;
        sprite = NULL;
    }
}

void ObjetoMundo2::render(){
    Player *player = Player::Instance();
    if(sprite!=NULL && !player->getAtravesarObj()){
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void ObjetoMundo2::onCollisionPlayer(){
    Player *player = Player::Instance();

    bool colisiones[4] = {false, false, false, false};

    if(sprite != NULL){
        if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            if(!player->getAtravesarObj()){
                colisiones[0]=colisionTop();
                colisiones[1]=colisionDown();//abajo
                colisiones[2]=colisionRight();
                colisiones[3]=colisionLeft();
                player->setColisionesDinam(colisiones);
                player->setMuere(true);
            }
        }
    }
}

bool ObjetoMundo2::colisionDown(){
    Player *player = Player::Instance();
    if(!player->getAtravesarObj()){
        int xPlayer=player->getX();
        int yPlayer=player->getY();
        int heightPlayer=player->getSprite()->getBounds("global").height;
        int widthPlayer=player->getSprite()->getBounds("global").width;

        if(motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
            player->setPosition(xPlayer, y-heightPlayer/2.f+1);
            player->setEnSuelo(true);
            return true;
        } 
    }
    return false;
}



bool ObjetoMundo2::colisionTop(){
     Player *player = Player::Instance();
     if(!player->getAtravesarObj()){
        int xPlayer=player->getX();
        int yPlayer=player->getY();
        int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
        int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

        if(motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false,false)){
            y = yPlayer - heightPlayer/2.f - height - 5;
            //player->setPosition(xPlayer, y+height+heightPlayer/2.f-1);
            player->setVelocidad_y(0);
            return true;
        }
    }
    return false;
}

bool ObjetoMundo2::colisionLeft(){
    Player *player = Player::Instance();
    if(!player->getAtravesarObj()){
        int xPlayer=player->getX();
        int yPlayer=player->getY();
        int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
        int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

        if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
            player->setPosition(x+width+widthPlayer/2.f-1, yPlayer);
            return true;
        }
    }
    return false;
}

bool ObjetoMundo2::colisionRight(){
    Player *player = Player::Instance();
    if(!player->getAtravesarObj()){
        int xPlayer=player->getX();
        int yPlayer=player->getY();
        int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
        int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;
        
        if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
            player->setPosition(x-widthPlayer/2.f+1, yPlayer);
            return true;
        }
    }

    return false;
}
  
void ObjetoMundo2::setPosition(float f1, float f2){
    x = f1;
    y = f2;
}
