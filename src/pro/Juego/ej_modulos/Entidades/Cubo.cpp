#include "Cubo.h"

Cubo::Cubo(){
    sprite=NULL;
    motor=NULL;
    x=0;
    y=0;
    velocidad_x=0;
    velocidad_y=0;
    height=0;
    width=0;
    en_suelo=false;
    colisionCuboCubo = false;
    colisionCuboPlataforma = false;
    velocidadXPlataforma = 0.f;
    posicion = NULL;
}

Cubo::Cubo(int x_ini, int y_ini, int altura){

    sprite = new Sprite();
    //caja1 es la pequeña, caja2 la mediana, caja3 la grande
    if(altura == 0){
        sprite->setTexture("Caja1", "png");
    }
    else if(altura == 1){
        sprite->setTexture("Caja2", "png");
    }
    else {
        sprite->setTexture("Caja3", "png");
    }
    
    x = x_ini;
    y = y_ini;
    posicion = new FlotanteInterpolado(x, y);
    height = sprite->getBounds("global").height;
    width = sprite->getBounds("global").width;
    velocidad_x = 0.f;
    velocidad_y = 0.f;
    en_suelo=false;
    colisionCuboPlataforma = false;
    colisionCuboCubo = false;
    velocidadXPlataforma = 0.f;
    sprite->setPosition(x,y);
    
    motor = Motor::Instance();

    colisionesDinam[0] = false;
    colisionesDinam[1] = false;
    colisionesDinam[2] = false;
    colisionesDinam[3] = false;

    colisionesMapa[0] = false;
    colisionesMapa[1] = false;
    colisionesMapa[2] = false;
    colisionesMapa[3] = false;

}

Cubo::~Cubo(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}

void Cubo::setPosition(int n1, int n2){
  x=n1;
  y=n2;
}


void Cubo::updatemover(){

    Player *player = Player::Instance();
    float dT = motor->getDeltaTime();

    // Movimiento Personaje en X
    if(colisionCuboPlataforma){
        x = x + velocidadXPlataforma*dT;
    }   
    if(motor->isKeyPressedSpace() && player->getHabilidadActiva() == 4 && dir_grav == 0){
        if(colisionRight() || colisionLeft()){
            if(!colisionCuboCubo){
                velocidad_x = player->getVelocidad_x();
                x = x + velocidad_x * dT;
            }
        }
    }

    // Movimiento Personaje en Y
    if(!colisionesMapa[1] && !colisionesDinam[1]){ // si no hay colisiones con el suelo
        en_suelo=false;
        velocidad_y=velocidad_y+2;  // hay gravedad
        if(velocidad_y > 30){
            velocidad_y = 30;
        }
        y=y+velocidad_y*dT;
        
    }
    else{//si esta en el suelo
        en_suelo=true;
        velocidad_y=0.f;
    }
    posicion->setPositionXY(x, y);

}

void Cubo::render(float tick){
    float factor = std::min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void Cubo::setColisionesMapa(bool *colisiones){
    colisionesMapa[0]=colisiones[0];
    colisionesMapa[1]=colisiones[1];
    colisionesMapa[2]=colisiones[2];
    colisionesMapa[3]=colisiones[3];
}

void Cubo::onCollisionPlayer(int dir_gravedad){
    dir_grav = dir_gravedad;
    Player *player = Player::Instance();

    bool colisiones[4] = {false, false, false, false};

    if(sprite != NULL){
        if(dir_gravedad == 0){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=colisionTop();
                colisiones[1]=colisionDown();//abajo
                colisiones[2]=colisionRight();
                colisiones[3]=colisionLeft();
                player->setColisionesDinam(colisiones);
            }
        }
        else if(dir_gravedad == 1){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=colisionRight();
                colisiones[1]=colisionLeft();//abajo
                colisiones[2]=colisionDown();
                colisiones[3]=colisionTop();
                player->setColisionesDinam(colisiones);
            }
        }
        else if(dir_gravedad == 2){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=colisionDown();//abajo
                colisiones[1]=colisionTop();
                colisiones[2]=colisionLeft();
                colisiones[3]=colisionRight();
                player->setColisionesDinam(colisiones);
            }
        }
        else if(dir_gravedad == 3){
            if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                colisiones[0]=colisionLeft();
                colisiones[1]=colisionRight();//abajo
                colisiones[2]=colisionTop();
                colisiones[3]=colisionDown();
                player->setColisionesDinam(colisiones);
            }
        }
    }
}

bool Cubo::colisionDown(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height;
    int widthPlayer=player->getSprite()->getBounds("global").width;

    if(motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
        player->setPosition(xPlayer, y-heightPlayer/2.f+1);
        player->setEnSuelo(true);
        return true;
    } 
    return false;
}



bool Cubo::colisionTop(){
     Player *player = Player::Instance();
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
    return false;
}

bool Cubo::colisionLeft(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false)){
        player->setPosition(x+width+widthPlayer/2.f-1, yPlayer);
        return true;
    }
    return false;
}

bool Cubo::colisionRight(){
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

void Cubo::setColisionesDinam(bool *colisiones){
    colisionesDinam[0]=colisiones[0];
    colisionesDinam[1]=colisiones[1];
    colisionesDinam[2]=colisiones[2];
    colisionesDinam[3]=colisiones[3];
}