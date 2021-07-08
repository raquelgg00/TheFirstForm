#include "Plataforma.h"

Plataforma::Plataforma(){
    motor = NULL;
    player = NULL;
    sprite = NULL;
    height = 0; 
    width = 0;
    x = 0; 
    y = 0;
    x_ini = 0;
    x_fin = 0;
    x_fin = 0; 
    y_fin = 0;
    velx = 0.f; 
    vely = 0.f;
    id=-1;
    mov_vertical = 0;
    mov_horizontal = 0;
    en_movimiento_inicial = true;
    posicion = NULL;
    colisiones=NULL;
}

Plataforma::Plataforma(int idd, int m1, int m2, int n1, int n2, int m_hor, int m_ver, bool b){

    motor = Motor::Instance();
    player = Player::Instance();

    velx = 0.f;
    vely = 0.f;
    
    x_ini = m1;
    y_ini = m2;

    x = x_ini;
    y = y_ini;

    x_fin = n1;
    y_fin = n2;

    sprite = new Sprite();
    if(m_ver==0)
        sprite->setTexture("plataforma1", "png");
    else
        sprite->setTexture("plataforma2", "png");

    sprite->setPosition(x,y);
    
    height = sprite->getBounds("global").height;
    width = sprite->getBounds("global").width;
    id = idd;
    mov_horizontal = m_hor;
    mov_vertical = m_ver;
    en_movimiento_inicial = b;

    

    posicion = new FlotanteInterpolado(x, y);

    colisiones=new bool[4];
    for(int i=0;i<4;i++){
        colisiones[i]=false;
    }
}

Plataforma::~Plataforma(){
    if(sprite != NULL){
        delete sprite;
        sprite = NULL;
    }
    if(posicion != NULL){
        delete posicion;
        posicion = NULL;
    }
    if(colisiones!=NULL){
        delete[] colisiones;
        colisiones=NULL;
    }
}
//Creamos un XMLElement. Llamamos a getmapanivel y eso se lo pasamos
//a getPosiciones de mapa. En teoría va buscando las x.
void Plataforma::setPosition(int n1, int n2){
   
  x=n1;
  y=n2;
}


void Plataforma::updatemover(){
    
    reloj.restart();
    float dT = motor->getDeltaTime();
    float velocidadMax=15;

    bool al_reves = false;
    bool al_reves_y = false;

    if(x_ini>x_fin) al_reves = true;
    if(y_ini>y_fin) al_reves_y = true;

    if(!al_reves){
        if(x > x_fin) mov_horizontal = -1;
        else if(x < x_ini) mov_horizontal = 1;
    }
    else {
        if(x<x_fin) mov_horizontal = 1;
        else if(x>x_ini) mov_horizontal = -1;
    }
    
    if(!al_reves_y){
        if(y > y_fin) mov_vertical = -1;
        else if(y < y_ini) mov_vertical = 1;
    }
    else {
        if(y < y_fin) mov_vertical = 1;
        else if(y>y_ini) mov_vertical = -1;
    }


    if(mov_horizontal == 1){
        velx =  velocidadMax;
    }
    else if(mov_horizontal == -1){
        velx =  velocidadMax * -1;
    }
    else {
        velx = 0.f;
    }


    if(mov_vertical == 1){
        vely = velocidadMax;
    }
    else if(mov_vertical == -1){
        vely = velocidadMax * -1;
    }
    else{
        vely=0.f;
    }


    if(en_movimiento_inicial){
        y = y+vely*dT;
        x = x+velx*dT;
    }

    
    //sprite->setPosition(x,y);
    //setPosition(x,y);
    posicion->setPositionXY(x, y);
}

void Plataforma::render(float tick){
    float factor = fmin(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

    if(sprite!=NULL){
        sprite->setPosition(interX, interY);
        motor->ventanaDibuja(sprite->getSprite());
    }
}

void Plataforma::onCollisionPlayer(int g){
    g=0;
    Player *player = Player::Instance();
    
    for(int i=0;i<4;i++){//reseteo colisiones
        colisiones[i]=false;
    }

    if(sprite != NULL){
        if(sprite->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
            colisiones[0]=colisionTop();
            colisiones[1]=colisionDown();//abajo
            colisiones[2]=colisionRight();
            colisiones[3]=colisionLeft();
            en_movimiento_inicial = true;
            player->setColisionesDinam(colisiones);

            if(colisiones[1]){
                player->set_vel_plataforma(velx);
            }
            else {
                player->set_vel_plataforma(0.f);
            }
        }
    }
    
}

bool Plataforma::colisionDown(){
    
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height;
    int widthPlayer=player->getSprite()->getBounds("global").width;

    if(motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){

        player->setPosition(xPlayer, y-heightPlayer/2.f+1);
        player->setEnSuelo(true);
       
        return true;
    } 
    return false;
}



bool Plataforma::colisionTop(){
     Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    if(motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false, false)){
        
        player->setPosition(xPlayer, y+height+heightPlayer/2.f);
        player->setVelocidad_y(0);
        return true;
    }
    return false;
}

bool Plataforma::colisionLeft(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
        player->setPosition(x+width+widthPlayer/2.f-1, yPlayer);
        return true;
    }
    return false;
}

bool Plataforma::colisionRight(){
    Player *player = Player::Instance();
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;
      
    if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
        player->setPosition(x-widthPlayer/2.f+1, yPlayer);
        return true;
    }

    return false;
}






