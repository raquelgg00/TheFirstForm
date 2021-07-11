#include "Player.h"


// Singleton
Player* Player::pinstance = 0;
Player* Player::Instance(){
    if(pinstance == 0){
        pinstance = new Player;
    }
    return pinstance;
}

// Constructor
Player::Player(){

    motor = Motor::Instance();

    sprite = new Sprite();
    sprite->setTexture("player", "png");
    sprite->setFrameSprite(0,0,96,96);
    ancho = sprite->getSprite().getGlobalBounds().width;
    alto = sprite->getSprite().getGlobalBounds().height;
    sprite->setOrigin(ancho/2.f, alto/2.f);


    x=0;
    y=0;
    sprite->setPosition(x, y);


    posicion = new FlotanteInterpolado();

    valorVelociadadX=26.0;
    velocidad_x = 0.0;
    velocidad_y = 0.0;
    aceleracion_x = 2.0;
    aceleracion_y = 2.0;
    vel_plataforma = 0.0;
    habilidadActiva = 0;
    formaActiva = 0;
    dir_gravedad = 0;
    i = 0;
    current_coin_frame=0;

    atravesarObj = false;
    resetea_gravedad = false;
    encimaBolita = false;
    en_movimiento = false;
    saltando = false;
    rebotando = false;
    en_suelo=false;
    contactoVerdeDer=false;
    contactoVerdeIzq=false;
    contactoVerdeDown=false;
    contactoRojo=false;
    tengoArista=false;
    
    
    for(int i=0; i<4; i++){
        colisionesMapa[i] = false;
        colisionesDinam[i] = false;
        colisionesPared[i] = false;
    }
    
}

// Destructor
Player::~Player(){
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(sprite!=NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion!=NULL){
        delete posicion;
        posicion=NULL;
    }

}

void Player::setPosition(float n1, float n2){
    //if(sprite!=NULL){
        //sprite->setPosition(n1,n2);
        x=n1;
        y=n2;
    //}
        
}

void Player::update(int n){

    //motor->setShader(false);

    reloj.restart();

    dir_gravedad = n;

    if(movimiento_derecha){
        mover_derecha();
        movimiento_derecha=false;
    }

    if(movimiento_izquierda){
        mover_izquierda();
        movimiento_izquierda=false;
    }

    if(dir_gravedad == 0){
        update_gravedad0(false);
    }
    else if(dir_gravedad == 1){
        update_gravedad1(true);
    }
    else if(dir_gravedad == 2){
        update_gravedad0(true);
    }
    else if(dir_gravedad == 3){
        update_gravedad1(false);
    }

    posicion->setPositionXY(x, y);
    
       
    if(habilidadActiva == 0 || habilidadActiva == 2){
        i = 5;
    }else{
        i = 8;
    }
    if(clock.getElapsedTime().asSeconds() > 0.1f){
        if(current_coin_frame>=i){
          current_coin_frame = 0;
        }else{
          current_coin_frame++;
        }
        if(habilidadActiva == 5){
            sprite->setFrameSprite( current_coin_frame * 60, habilidadActiva*4*96 + formaActiva * 60, 60, 60);
        }
        else{
            sprite->setFrameSprite( current_coin_frame * 96, (habilidadActiva*4 + formaActiva) * 96, 96, 96);
        }
        clock.restart();
    }
    sf::Vector2f vMotor;
    vMotor.x = this->getX();
    vMotor.y = this->getY();
    motor->setPlayerCoord(vMotor);
   /* if(world2){
        if(motor->isKeyPressedQ() && !atravesarObj)
            atravesarObj = true;
        else if(motor->isKeyPressedQ() && atravesarObj)
            atravesarObj = false;
    }
    else
        atravesarObj = false;*/
}

void Player::update_gravedad0(bool inv){

    float dT = motor->getDeltaTime();

    int invertir = 1;
    if(inv) 
        invertir = -1;

    // Movimiento Personaje en X
    if(en_movimiento || rebotando){ // si toco teclado o si estoy rebotando actualizamos x
        if((velocidad_x<0&&!colisionesMapa[3])||(velocidad_x>0&&!colisionesMapa[2])
            || (velocidad_x<0&&!colisionesPared[3])||(velocidad_x>0&&!colisionesPared[2])){
                if(colisionesDinam[1]){
                    x=x+((velocidad_x+vel_plataforma)*0.8)*invertir*dT;
                }
                else{
                    x=x+velocidad_x*invertir*dT;   
                }
        }
    }
    else if(colisionesDinam[1]){
        x=x+vel_plataforma*invertir*dT;
    }
    else if(!en_movimiento && !rebotando) { //si no toco teclado y no estoy rebotando, vx=0
        velocidad_x=0.0;
    }

    // Rebote
    if(habilidadActiva==2 && rebotando){
        int frena_mas = 1;
        if(en_suelo) frena_mas = 2; //si esta en el suelo, hay mas rozamiento
        velocidad_x += aceleracion_x * frena_mas; //+ frena_mas;       // cada vez el impulso es menor

        if((aceleracion_x<0 && velocidad_x <= 0 )|| (aceleracion_x>0 && velocidad_x >= 0)){ // paro de rebotar
            rebotando=false;
        }
    }
   
    
    // Movimiento Personaje en Y
    if(!colisionesMapa[1] && !colisionesDinam[1] && !colisionesPared[1]){ // si no hay colisiones con el suelo
        en_suelo=false;
        saltando=false;
        if(colisionesMapa[0] || colisionesDinam[0]){ // si toca el techo para que no se quede adherido arriba
            velocidad_y = 0.f;
        }
        velocidad_y=velocidad_y+3;  // hay gravedad
        if(velocidad_y > 40){
            velocidad_y = 40;
        }
        y=y+velocidad_y*invertir*dT;
        
    }
    else{//si esta en el suelo
        en_suelo=true;
        if(!colisionesDinam[1])
            velocidad_y=0.f;
        else
            velocidad_y = 5.5f;
    }

    // Empuje inicial para el salto y el rebote
    if(saltando &&habilidadActiva==1 && en_suelo){ 
        velocidad_y=-5.f;
        y=y+velocidad_y*invertir*dT;
    }
    if(saltando&&habilidadActiva==2 && contactoVerdeDown){
        velocidad_y=-50.f;
        y=y+velocidad_y*invertir*dT;
    }   

}


void Player::update_gravedad1(bool invertir){
    float dT = motor->getDeltaTime();
    int inv = 1;
    if(invertir) inv = -1;

    // Movimiento Personaje en X
    if(en_movimiento || rebotando){ // si toco teclado o si estoy rebotando actualizamos x
        if((velocidad_x<0 && !colisionesMapa[3])||(velocidad_x>0&&!colisionesMapa[2]) || (velocidad_x<0 && !colisionesPared[3])||(velocidad_x>0&&!colisionesPared[2])){
            y = y - (velocidad_x*inv*dT);
        }
    }
    else if(!en_movimiento && !rebotando) { //si no toco teclado y no estoy rebotando, vx=0
        velocidad_x=0.0;
    }

    // Rebote
    if(habilidadActiva==2 && rebotando){
        int frena_mas = 1;
        if(en_suelo) frena_mas = 2; //si esta en el suelo, hay mas rozamiento
        velocidad_x += aceleracion_x * frena_mas; //+ frena_mas;       // cada vez el impulso es menor

        if((aceleracion_x<0 && velocidad_x <= 0 )|| (aceleracion_x>0 && velocidad_x >= 0)){ // paro de rebotar
            rebotando=false;
        }
    }

    // Movimiento Personaje en Y
    if(!colisionesMapa[1] && !colisionesDinam[1] && !colisionesPared[1]){ // si no hay colisiones con el suelo
        en_suelo=false;
        saltando=false;

        if(colisionesMapa[0] || colisionesDinam[0]){ // si toca el techo para que no se quede adherido arriba
            velocidad_y = 0.f;
        }
        velocidad_y=velocidad_y+3;  // hay gravedad
        if(velocidad_y > 30){
            velocidad_y = 30;
        }
        x = x + velocidad_y*inv*dT;
        
    }
    else{//si esta en el suelo
        en_suelo = true;
        if(!colisionesDinam[1])
            velocidad_y=0.f;
        else
            velocidad_y = 5.5f;
    }


    // Empuje inicial para el salto y el rebote
    if(saltando && habilidadActiva==1 && en_suelo){ 
        velocidad_y=-5.f;
        x = x + velocidad_y*inv*dT;
    }
    if(saltando&&habilidadActiva==2 && contactoVerdeDown){
        velocidad_y=-50.f;
        x = x + velocidad_y*inv*dT;
    }  

}

void Player::saltar(){
    
    saltando=true;
    velocidad_y = -63;
}

void Player::rebote(){
    if(contactoVerdeDown){
        saltando=true;
        velocidad_y = -110;
        Motor::Instance()->getSonidoRebote()->Play();
    }
    else if(contactoVerdeDer){
        rebotando=true;
        if(aceleracion_x<0)
            aceleracion_x=aceleracion_x*-1;
        velocidad_x = -110;
        Motor::Instance()->getSonidoRebote()->Play();
    }
    else if(contactoVerdeIzq){
        rebotando=true;
        if(aceleracion_x>0)
            aceleracion_x=aceleracion_x*-1;
        velocidad_x = +110;
        Motor::Instance()->getSonidoRebote()->Play();
    }
}

void Player::input(){

}

Sprite* Player::getSprite(){
    return sprite;
}

void Player::mover_derecha(){
    if(!rebotando){
        velocidad_x += valorVelociadadX;
        if(velocidad_x>valorVelociadadX) velocidad_x = valorVelociadadX;
        en_movimiento = true;
    }
}

void Player::mover_izquierda(){
    if(!rebotando){
        velocidad_x -= valorVelociadadX;
        if(velocidad_x<-valorVelociadadX) velocidad_x = -valorVelociadadX;
        en_movimiento = true;
    }
}

void Player::setHabilidad(int n){
    if(!rebotando){
        if(n <= Guardar::Instance()->getHabilidades()){
            habilidadActiva = n;
            if(habilidadActiva == 5){
                sprite->setFrameSprite(0,(habilidadActiva*4*96 + formaActiva*60),60,60);
            }
            else
                sprite->setFrameSprite(0, (n*4 + formaActiva)*96,96,96);

        }
        sprite->setOrigin(sprite->getBounds("global").width/2,sprite->getBounds("global").height/2);
    }
}

void Player::setForma(){
    formaActiva  ++;
    if(habilidadActiva == 5){
        sprite->setFrameSprite(0,(habilidadActiva*4*96 + formaActiva*60),60,60);
    }
    else
        sprite->setFrameSprite(0,(habilidadActiva*4 + formaActiva)*96,96,96);
    sprite->setOrigin(sprite->getBounds("global").width/2,sprite->getBounds("global").height/2);
    
   
}

void Player::setFormaReset(int form){
    formaActiva=form;
    if(habilidadActiva == 5){
        sprite->setFrameSprite(0,(habilidadActiva*4*96 + formaActiva*60),60,60);
    }
    else
        sprite->setFrameSprite(0,(habilidadActiva*4 + formaActiva)*96 ,96,96);
    sprite->setOrigin(sprite->getBounds("global").width/2,sprite->getBounds("global").height/2);
    
}

void Player::usarHabilidad(){
    
    if(habilidadActiva==1&& (en_suelo || encimaBolita)){
        saltar();
        encimaBolita = false;
        
    }
    else if(habilidadActiva==2&&(contactoVerdeDer||contactoVerdeIzq||contactoVerdeDown)){
        rebote();
    }
    else if(habilidadActiva==3){
        romper();
    }
    else if(habilidadActiva==4){
        
    }
    else if(habilidadActiva==5){
        hacerse_peque();
    }
}





void Player::romper(){

}


void Player::hacerse_peque(){
   // sprite->setFrameSprite(0,(habilidadActiva*4 + formaActiva)*96 ,60,60);
}


void Player::setColisionesMapa(bool *colision){
    colisionesMapa[0]=colision[0];
    colisionesMapa[1]=colision[1];
    colisionesMapa[2]=colision[2];
    colisionesMapa[3]=colision[3];
}

void Player::setColisionesDinam(bool *colision){
    colisionesDinam[0]=colision[0];
    colisionesDinam[1]=colision[1];
    colisionesDinam[2]=colision[2];
    colisionesDinam[3]=colision[3];
}

void Player::setColisionesPared(bool *colision){
    for (unsigned short i = 0; i < 4; i++)
        colisionesPared[i]=colision[i];
}

void Player::reseteaColisionesMapa(){
    for(int i=0; i<4; i++){
        colisionesDinam[i] = false;
    }
}