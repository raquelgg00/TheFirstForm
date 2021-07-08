#include "Pared.h"
#include "Player.h"


// Constructor
Pared::Pared(){
    motor = NULL;
    sprite = NULL;
    x = 0;
    y = 0;
    alto = 0;
    ancho = 0;
}

Pared::Pared(int n1, int n2, int pinchitos){
    motor = Motor::Instance();
    sprite = new Sprite();
    sprite->setTexture("pared_romper", "png");
    sprite->setFrameSprite(0,0,64,256);
    
    //sprite->setRotation(90);
    x = n1;
    y = n2;
    alto = sprite->getBounds("global").height;
    ancho = sprite->getBounds("global").width;
    setPosition(x,y);

    if(pinchitos == 1){ 
        pinchos[0] = new PinchoPared(x-64, y+25, 3); //izquierda
        pinchos[1] = new PinchoPared(x+ancho, y+25, 1);// derecha
        pinchos[2] = new PinchoPared(x, y+alto, 2);// abajo
    }
    else if(pinchitos == 2){
        pinchos[0] = new PinchoPared(x-64, y-25, 3); //izquierda
        pinchos[1] = new PinchoPared(x+ancho, y-25, 1);// derecha
        pinchos[2] = new PinchoPared(x, y-64, 0);// arriba
    }
    else {
        pinchos[0] = NULL;
        pinchos[1] = NULL;
        pinchos[2] = NULL;
    }
}

Pared::~Pared(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    for(int i=0; i<3; i++){
        if(pinchos[i] != NULL){
            delete pinchos[i];
            pinchos[i] = NULL;
        }
    } 
}



void Pared::setPosition(int n1, int n2){
    sprite->setPosition(x,y);
    x=n1;
    y=n2;
}

void Pared::updatemover(){

    for(int i=0; i<3; i++){
        if(pinchos[i] != NULL){
            pinchos[i]->updatemover();
        }
    }
    
    if(romper){
        if(sprite != NULL){
            sprite->setFrameSprite(64*i,0,64,256);
            i++;
            if(i>10){
                this->~Pared(); 
                romper = false;
            }
        }
    }
}

void Pared::render(float tick){
    tick = 0.f;
    if(sprite != NULL){
        motor->ventanaDibuja(sprite->getSprite());
        for(int i=0; i<3; i++){
            if(pinchos[i] != NULL){
                if(pinchos[i]->getSprite() != NULL)
                    pinchos[i]->render(0.f);
            }
        }
    }
    
}

void Pared::onCollisionPlayer(int dir_gravedad){

    Player *player = Player::Instance();

    if(pinchos[0] != NULL && pinchos[1] != NULL && pinchos[2] != NULL){
                        
        Sprite *s1 = pinchos[0]->getSprite();
        Sprite *s2 = pinchos[1]->getSprite();
        Sprite *s3 = pinchos[2]->getSprite();

        if(s1 != NULL && s2 != NULL && s3 != NULL){
            if(player->getSprite()->getBounds("global").intersects(s1->getBounds("global")) ||
                player->getSprite()->getBounds("global").intersects(s2->getBounds("global")) ||
                player->getSprite()->getBounds("global").intersects(s3->getBounds("global"))
                )
            {   
                
                player->setMuere(true);
                //morision();                  
            }
        }
    }

    bool colisiones[4] = {false, false, false, false};
    if(sprite != NULL&&!player->getMuere()){
        if(dir_gravedad == 0){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=onCollisionPlayerTop();
                colisiones[1]=onCollisionPlayerDown();//abajo
                colisiones[2]=onCollisionPlayerRight();
                colisiones[3]=onCollisionPlayerLeft();
                if(motor->isKeyPressedSpace() && player->getHabilidadActiva()==3){
                    //this->~Pared(); 
                    romper = true;
                }
                player->setColisionesDinam(colisiones);    
            }
        }
        else if(dir_gravedad == 1){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=onCollisionPlayerRight();
                colisiones[1]=onCollisionPlayerLeft();//abajo
                colisiones[2]=onCollisionPlayerDown();
                colisiones[3]=onCollisionPlayerTop();
                if(motor->isKeyPressedSpace() && player->getHabilidadActiva()==3){
                    //this->~Pared(); 
                    romper = true;
                }
                player->setColisionesDinam(colisiones);    
            }
        }
        else if(dir_gravedad == 2){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=onCollisionPlayerDown();//abajo
                colisiones[1]=onCollisionPlayerTop();
                colisiones[2]=onCollisionPlayerLeft();
                colisiones[3]=onCollisionPlayerRight();
                if(motor->isKeyPressedSpace() && player->getHabilidadActiva()==3){
                    //this->~Pared(); 
                    romper = true;
                }
                player->setColisionesDinam(colisiones);    
            }
        }
        else if(dir_gravedad == 3){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=onCollisionPlayerLeft();
                colisiones[1]=onCollisionPlayerRight();//abajo
                colisiones[2]=onCollisionPlayerTop();
                colisiones[3]=onCollisionPlayerDown();
                if(motor->isKeyPressedSpace() && player->getHabilidadActiva()==3){
                    //this->~Pared(); 
                    romper = true;
                }
                player->setColisionesDinam(colisiones);    
            }
        }
    }

}

    
bool Pared::onCollisionPlayerDown(){

    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    // Colision
    int width = ancho;
    int height = alto; 

    if(motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
        player->setPosition(xPlayer, y-heightPlayer/2.f+1);
        player->setEnSuelo(true);
        return true;
    }

  
    return false;
}

bool Pared::onCollisionPlayerTop(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    // Colision
    int width = ancho;
    int height = alto; 

    if(motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false, false)){
        player->setPosition(xPlayer, y+height+heightPlayer/2.f-1);
        player->setEnSuelo(true);
        return true;
    }

  
    return false;
}

bool Pared::onCollisionPlayerRight(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    // Colision
    int width = ancho;
    int height = alto; 
      
    if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
        player->setPosition(x-widthPlayer/2.f+1, yPlayer);
        return true;
    }

    return false;
}

bool Pared::onCollisionPlayerLeft(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    // Colision
    int width = ancho;
    int height = alto; 

    if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
        player->setPosition(x+width+widthPlayer/2.f-1, yPlayer);
        return true;
    }
    return false;
}

