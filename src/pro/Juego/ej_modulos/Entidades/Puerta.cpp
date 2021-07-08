#include "Puerta.h"

Puerta::Puerta(){
    sprite=NULL;
    motor=NULL;
    player=NULL;
    x=0;
    y=0;
    tipo=0;
    height=0;
    width=0;
    i = 16;
    current_coin_frame = 0;
    abierta=false;
}

Puerta::Puerta(int x_ini, int y_ini, int topito){

    sprite = new Sprite();
    //caja1 es la pequeña, caja2 la mediana, caja3 la grande
    sprite->setTexture("compuerta", "png");
    sprite->setFrameSprite(0,0,64,256);
    x = x_ini;
    y = y_ini;
    if(topito==1){
        sprite->setRotation(90);
        x+=256;
    }

    tipo=topito;
    height = sprite->getBounds("global").height;
    width = sprite->getBounds("global").width;
    setPosition(x,y);
    i = 16;
    current_coin_frame = 0;
    abierta=false;
    motor = Motor::Instance();

}

Puerta::~Puerta(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
}

void Puerta::setPosition(int n1, int n2){
    if(sprite!=NULL)
        sprite->setPosition(x,y);
    x=n1;
    y=n2;
}


void Puerta::render(float tick){
    tick = 0.f;
    
    if(sprite!=NULL)
        motor->ventanaDibuja(sprite->getSprite());
}



void Puerta::onCollisionPlayer(int g){
    g=0;
    Player *player = Player::Instance();

    bool colisiones[4] = {false, false, false, false};

    if(sprite != NULL){
        if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            //colisiones[0]=colisionTop();
            //colisiones[1]=colisionDown();//abajo
            colisiones[2]=colisionRight();
            //colisiones[3]=colisionLeft();
            player->setColisionesDinam(colisiones);
        }
    }
   
}

bool Puerta::colisionRight(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;
    
    if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
        player->setPosition(x-widthPlayer/2.f+1, yPlayer);
        return true;
    }
    
    return false;
}

void Puerta::updatemover(){
    
    if(final_animacion == false){
        if(sprite!=NULL){
            comprobarApertura();
            if(alguna_vez_abierta){
                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    if(current_coin_frame>=i){
                        final_animacion = true;
                        this->~Puerta();
                    }
                    else{
                        current_coin_frame++;
                         sprite->setFrameSprite(current_coin_frame*64, 0, 64, 256);
                        clock.restart();
                    }
                }
            }
        }
    }
}

void Puerta::comprobarApertura(){
    abierta = true;
 
    for(unsigned int k=0;k<sensores.size();k++){
        //ret=ret*sensores[i]->getPresionado();
        if(!sensores[k]->getPresionado()){
            abierta = false;
        }
    }
    if(abierta) alguna_vez_abierta = true;
}




