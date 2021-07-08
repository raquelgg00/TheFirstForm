#include "Creditos.h"

// Singleton 
Creditos* Creditos::pinstance = 0;
Creditos* Creditos::Instance(){
    if(pinstance == 0){
        pinstance = new Creditos;

    }
    return pinstance;
}

// Constructor
Creditos::Creditos(){

    // Motor
    motor = Motor::Instance();
    
    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Creditos","png");
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }

    //Fondo del menu
    logo=new Sprite();
    logo->setTexture("Logo1","png");
    logo->setOrigin(logo->getBounds("global").width/2.f, logo->getBounds("global").height/2.f);

    logo->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(10));
    if(motor->getTamHeight()==720)
        logo->setScale(0.15,0.15);
    else
        logo->setScale(0.22,0.22);
   

    //Inicializamos los textos de las opciones
    nombres[0]=new Texto("Raquel Garcia Guillem");
    nombres[1]=new Texto("Gaspar Mora Rico");
    nombres[2]=new Texto("Diego Valero Bueno");
    nombres[3]=new Texto("Laura Gil Lopez");
    nombres[4]=new Texto("Vanessa Davo Parreno");
    nombres[5]=new Texto("Guillermo Novelda Mortes");

    for(int i=0;i<num_items;i++){
        if(motor->getTamHeight()==720){
            nombres[i]->setSize(45);

        }
        else
            nombres[i]->setSize(67);

        nombres[i]->setOrigin(nombres[i]->getWidthBounds()/2.f, nombres[i]->getHeightBounds()/2.f);
        nombres[i]->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(i+12));
        nombres[i]->setColor(255,255,255);
    }
    
}

// Destructor
Creditos::~Creditos(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(logo!=NULL){
        delete logo;
        logo=NULL;
    }
    for(int i=0;i<num_items;i++){
        if(nombres[i]!=NULL){
            delete nombres[i];
            nombres[i]=NULL;
        }
    }
}


void Creditos::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
//reseteo creditos y luego cambio
    logo->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(10));

    for(int i=0;i<num_items;i++){
        nombres[i]->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(i+12));
    }
    Partida::setEstado(MenuPrincipal::Instance());
}

void Creditos::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());

    motor->ventanaDibuja(logo->getSprite());
    for(int i=0;i<num_items;i++){
        nombres[i]->drawText();
    }

    motor->ventanaDisplay();
}

void Creditos::update(){
    logo->setPosition(logo->getXPosition(),logo->getYPosition()-2);
    for(int i=0;i<num_items;i++){
        nombres[i]->setPosition(nombres[i]->getXPosition(),nombres[i]->getYPosition()-2);
    }
    if(nombres[5]->getYPosition()<-45){
        CambiarEstado();
    }
}

void Creditos::input(){
  
    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }
    }
     
}

