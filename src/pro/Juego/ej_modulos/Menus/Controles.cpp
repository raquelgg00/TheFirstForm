#include "Controles.h"

// Singleton 
Controles* Controles::pinstance = 0;
Controles* Controles::Instance(){
    if(pinstance == 0){
        pinstance = new Controles;

    }
    return pinstance;
}

// Constructor
Controles::Controles(){

   // Motor
    motor = Motor::Instance();

    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Controles","png");
    if(motor->getTamHeight()==720)
        fondo->setScale(0.67,0.67);

    //Inicializamos los textos de las opciones
    nombres=new Texto("Volver");
    if(motor->getTamHeight()==720)
        nombres->setSize(45);
    else
        nombres->setSize(67);

    nombres->setOrigin(nombres->getWidthBounds()/2.f, nombres->getHeightBounds()/2.f);
    nombres->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/11)*(5+4));
    nombres->setColor(255,255,255);
    
}

// Destructor
Controles::~Controles(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(nombres!=NULL){
        delete nombres;
        nombres=NULL;
    }
}


void Controles::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
    if(estadoAnterior==0)
        Partida::setEstado(MenuPrincipal::Instance());
    else
        Partida::setEstado(Pausa::Instance());
}

void Controles::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());
    nombres->drawText();
    nombres->setColor(36,207,253);
    motor->ventanaDisplay();
}

void Controles::update(){

}

void Controles::input(){
  
    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }
        if(motor->isKeyPressedEnter()){
            motor->getSonidoSeleccion()->Play();
            CambiarEstado();
        } 

        float x_ventana = motor->getWindow()->getPosition().x;
        float y_ventana = motor->getWindow()->getPosition().y;
        float x_cursor = sf::Mouse::getPosition().x - x_ventana;
        float y_cursor = sf::Mouse::getPosition().y - y_ventana - 27;

            nombres->setColor(255,255,255);

            if(nombres->getGlobalBounds().contains(x_cursor, y_cursor)){
                nombres->setColor(6,207,253);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    motor->getSonidoSeleccion()->Play();
                    CambiarEstado();
                }
            }
    }    
}

