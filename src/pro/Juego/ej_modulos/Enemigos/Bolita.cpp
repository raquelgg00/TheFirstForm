#include "Bolita.h"
#include "Player.h"
#include "math.h"

Bolita::Bolita(){
    motor = NULL;
    x=0;
    y=0;
    x_ini = -1;
    y_ini = -1;
    x_fin = -1;
    y_fin = -1;
    velx = -1;
    vely = -1;
    tipo = -1;
    mov_horizontal = 0;
    mov_vertical = 0;
    hace_rectangulos = false;
    sprite = NULL;
    activa = false;
    distancia_max_tipo_3 = 0;
    posicion = NULL;
    ofensiva = true;
}

Bolita::Bolita(int x_uno, int y_uno, int x_max, int y_max, int t, int dist_tipo_3){
    motor = Motor::Instance();
    x_ini = x_uno;
    y_ini = y_uno;
    x_fin = x_max;
    y_fin = y_max;
    x = x_ini;
    y = y_ini;
    posicion = new FlotanteInterpolado(x, y);
    velx = 0;
    vely = 0;
    tipo = t;
    hace_rectangulos = false;
    activa = false;
    distancia_max_tipo_3 = dist_tipo_3;
    ofensiva = true;

    // Comprobamos hacia donde se debe mover el enemigo (establecemos el mov_vertical y horizontal) 
    mov_horizontal = 0;
    mov_vertical = 0;
    if(tipo==0){
        if(x_ini != x_fin && y_ini != y_fin) {
            hace_rectangulos = true;
            // Así va en sentido de las agujas del reloj. Si se necesita lo contario se puede pasar como otro atributo del mapa
            mov_horizontal = 1;
            mov_vertical = 0;
        }
        else {
            if(x_ini<x_fin) mov_horizontal = 1;
            else if (x_ini>x_fin) mov_horizontal = -1;
            if(y_ini<y_fin) mov_vertical = 1;
            else if (y_ini>y_fin) mov_vertical = -1;
        }       
    }
    else if(tipo == 1){
        mov_horizontal = 1; // si es del tipo 1 solo se mueve en horizontal (y todo el rato)
    }

    sprite = new Sprite();

    if(tipo == 3){
        sprite->setTexture("bolon", "png");
        sprite->setFrameSprite(0,0,192,192);  
        //sprite->setScale(2.f, 2.f);
    }
    else{
        sprite->setTexture("Bola", "png");
        sprite->setFrameSprite(0,0,64,64);  
        if(tipo==5){
            sprite->setScale(2.f, 2.f);
        }
    }

    sprite->setPosition(x,y);
}

Bolita::~Bolita(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
}

void Bolita::setColisionesMapa(bool *colisiones){
    colisionesMapa[0]=colisiones[0];
    colisionesMapa[1]=colisiones[1];
    colisionesMapa[2]=colisiones[2];
    colisionesMapa[3]=colisiones[3];
}

void Bolita::setPosition(int n1, int n2){
    x=n1;
    y=n2;
}

void Bolita::updatemover(){

    float dT = motor->getDeltaTime();
    int velocidad_max = 20.0;
    Player *p1 = Player::Instance();
    reloj.restart();


    
    if(clock.getElapsedTime().asSeconds() > 0.1){
        
        if(tipo != 3){
            iter = iter + 1;
            if(iter > 2) iter = 0;
            sprite->setFrameSprite(iter*64,0,64,64);
            
        }
        else {
            if(mov_horizontal == 1 && dirGravedad==0) iter+=1;
            else if(mov_horizontal == -1 || mov_horizontal == 1) iter -= 1;

            if(activa && ofensiva){
                if(iter>15) iter = 0;
                if(iter<0) iter=14;
                sprite->setFrameSprite(iter*192,0,192,192);
            }

        }
        clock.restart();
    }
    
    
    
    if(tipo == 0||tipo==4) {
        if(hace_rectangulos == false){ // es tipo = 0 y va en una sola direccion
            if(x > x_fin) mov_horizontal = -1;
            else if(x < x_ini) mov_horizontal = 1;
            
            if(y > y_fin) mov_vertical = -1;
            else if(y < y_ini) mov_vertical = 1;           
        }
        else { // es tipo = 0  y  hace un rectangulo
            if(x > x_fin) {
                mov_horizontal = 0;
                mov_vertical = 1;
                x = x_fin;
            }
            else if(y>y_fin){
                mov_vertical=0;
                mov_horizontal=-1;
                y=y_fin;
            }
            else if(x<x_ini){
                mov_horizontal=0;
                mov_vertical=-1;
                x=x_ini;
            }
            else if(y<y_ini){
                mov_horizontal=1;
                mov_vertical=0;
                y=y_ini;
            }

        }
    }
    else if(tipo == 1){ // se mueve e horizontal hasta que colisiona con una pared
        //velocidad_max=6.f;
        // AQUI HAY QUE COMPROBAR COLISIONES CON EL MAPA!! Ira de izquierda a drcha hasta que se encuentre algo colisionable
        // de momento esta puesto para que vaya desde 0 a 1000
        //if(colisionesMapa[2]||colisionesMapa[3]) mov_horizontal *= -1;
        if(colisionesMapa[2]){
            
            mov_horizontal = -1.0;
        }
        else if(colisionesMapa[3]){
            
            mov_horizontal = 1.0;
        }
        //else if(x>1000) mov_horizontal = -1.0;
    }
    else if(tipo == 2){ // se mueve en horizontal cuando te ve
        if(activa == false){ // si aun no te ha visto se comprueba siempre si esta en el rango de vision
            float y_player_min = p1->getY();
            float y_player_max = y_player_min + p1->getSprite()->getSprite().getGlobalBounds().height;
            float y_enemigo_min = y;
            

            if(y_player_min<y_enemigo_min && y_player_max>y_enemigo_min){ // si te ve, empieza a moverse
                activa = true;
                if(p1->getX() < x) mov_horizontal = -1;
                else mov_horizontal = 1;
            }
        }

        //velocidad_max=2.f;
        // AQUI HAY QUE COMPPROBAR COLISIONES CON EL MAPA TAMBIEN
        //if(colisionesMapa[2]||colisionesMapa[3]) mov_horizontal *= -1;
        if(colisionesMapa[2]){
            mov_horizontal = -1.0;
        }
        else if(colisionesMapa[3]){
            mov_horizontal = 1.0;
        }
        //else if(x>3000) mov_horizontal = -1.0;
    }
    else if(tipo == 3){ // Bola por plano inclinado 

        velocidad_max=20.f;
        if(activa == false){

            // Sacamos la distancia Player-Bolita
            sf::FloatRect shape1 = p1->getSprite()->getSprite().getGlobalBounds();
            sf::FloatRect shape2 = sprite->getSprite().getGlobalBounds();
            float radio1 = shape1.width/2;
            float radio2 = shape2.width/2;
            float dx = (p1->getX() + radio1) - (this->x + radio2);
            float dy = (p1->getY() + radio1) - (this->y + radio2);
            float distance = pow((dx * dx) + (dy * dy), 0.5);
            //float distance = std::sqrt((dx * dx) + (dy * dy));

            // Si la distancia es menor que el radio de "vision" de la bola, esta se activa
            if(distance < distancia_max_tipo_3){
                activa = true;
                mov_horizontal = 1;
                mov_vertical = 1;
            }
        }
        
        if(dirGravedad != 3){
            if(colisionesMapa[2]){
                mov_horizontal = -1;
            }
            else if(colisionesMapa[3]){
                mov_horizontal = 1;
            }
        }
        else {
            if(colisionesMapa[1]){
                mov_horizontal = 0;
            }
            else if(colisionesMapa[0]){
                mov_horizontal = 1;
            }
        }

    }
    else if(tipo == 5){ 
        if(activa == false){ // si aun no te ha visto se comprueba siempre si esta en el rango de vision
            float y_player_min = p1->getY()-p1->getSprite()->getBounds("global").height/2.f;
            float y_player_max = y_player_min + p1->getSprite()->getSprite().getGlobalBounds().height;
            float y_enemigo_min = y;
            float x_player = p1->getX();
            
            if(y_player_min<y_enemigo_min && y_player_max>y_enemigo_min && x_player < x ){ // si te ve, empieza a moverse
                activa = true;
                mov_horizontal = -1;
            }
        }
        
        if(colisionesMapa[2]){
            mov_horizontal = -1.0;
        }
        else if(colisionesMapa[3]){
            mov_horizontal = 1.0;
        }
    }


    if(mov_horizontal == 1){
        velx =  velocidad_max;
    }
    else if(mov_horizontal == -1){
        velx = -velocidad_max;
    }
    else {
        velx = 0;
    }

    if(mov_vertical == 1){
        if(tipo != 3){
            vely = velocidad_max;
        }
        else{
            vely = vely + 3;
            if(vely > 30) vely = 30;
        }
    }
    else if(mov_vertical == -1){
        vely = -velocidad_max;
    }
    else{
        vely=0.f;
    }

    if(tipo == 3 && dirGravedad == 3){
        x = x + vely * dT;
        y = y + velx * dT;
    }
    else {
        x = x + velx * dT;
        y = y + vely * dT;
    }
    
    posicion->setPositionXY(x, y);
}

void Bolita::render(float tick){
    float factor = std::min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void Bolita::onCollisionPlayer(int g){

    dirGravedad = g;
    Player *player=Player::Instance();
    if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
          
        if(ofensiva){
            player->setMuere(true);
        }
        else{
            float alto_player = player->getSprite()->getBounds("global").height;
            player->setPosition(player->getX(), y-alto_player/2.f-9);
            player->setEncimaBolita(true);
        }
    }
}

void Bolita::cambiardirHorizontal(){

    if(mov_horizontal == 1){
        mov_horizontal = -1;
    }
    else if(mov_horizontal==-1){
        mov_horizontal = 1;
    }

}

void Bolita::transformarBolita(){
    mov_horizontal=0;
    mov_vertical=0;
    //sprite->setColor("blue");
    ofensiva = false;
    sprite->setTexture("BolaInofensiva", "png");
    sprite->setFrameSprite(0,0,192,192);

    //sprite->setScale(3.f, 3.f);

}