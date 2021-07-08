#include "InicioJuego.h"


// Singleton 
InicioJuego* InicioJuego::pinstance = 0;
InicioJuego* InicioJuego::Instance(){
    if(pinstance == 0){
        pinstance = new InicioJuego;

    }
    return pinstance;
}


// Constructor
InicioJuego::InicioJuego(){
    motor = Motor::Instance();

    texto_sprite = new Sprite();
    if(motor->getTamHeight()==720)
        texto_sprite->setTexture("Inicio1","png");
    else
        texto_sprite->setTexture("Inicio2","png");

    
    texto_sprite->setOrigin(texto_sprite->getBounds("global").width/2.f, texto_sprite->getBounds("global").height/2.f);
    texto_sprite->setPosition(motor->getTamWidth()/2.f ,motor->getTamHeight()*0.75);
   
    sprite = new Sprite();
    sprite->setTexture("CaratulaGrande","png");

    fondoTransicion = new Sprite();
    fondoTransicion->setTexture("fondoNegro","png");

    if(motor->getTamHeight()==720){
        fondoTransicion->setScale(0.67,0.67);
        sprite->setScale(0.67,0.67);
    }

    aumentando_tamanio = true;
    alpha = 255;

    motor->getSonidoInicio()->Play();
}


// Destructor
InicioJuego::~InicioJuego(){
 if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(texto_sprite!=NULL){
        delete texto_sprite;
        texto_sprite=NULL;
    }
    if(sprite!=NULL){
        delete sprite;
        sprite=NULL;
    }
    if(fondoTransicion!=NULL){
        delete fondoTransicion;
        fondoTransicion=NULL;
    }
}



void InicioJuego::CambiarEstado(){
    motor->getSonidoInicio()->pause();
    motor->getMusicaMenu()->Play();
    Partida::setEstado(MenuPrincipal::Instance());
}


void InicioJuego::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(sprite->getSprite());
    motor->ventanaDibuja(texto_sprite->getSprite());
    if(alpha > 0)
        motor->ventanaDibuja(fondoTransicion->getSprite());
    motor->setView(0);
    motor->ventanaDisplay();
}


void InicioJuego::update(){

    if(alpha > 0) alpha--;
    if(alpha < 150) alpha--;
    if(alpha<0) alpha = 0;

    
    fondoTransicion->setColor(0,0,0,alpha);

    if(aumentando_tamanio){
        texto_sprite->setScale(texto_sprite->getScale().x+0.005, texto_sprite->getScale().y+0.005);
    }
    else {
        texto_sprite->setScale(texto_sprite->getScale().x-0.005, texto_sprite->getScale().y-0.005);
    }
    
    if(texto_sprite->getScale().x > 1.15){
        aumentando_tamanio = false;
    }
    else if(texto_sprite->getScale().x < 1){
        aumentando_tamanio = true;
    }
}


void InicioJuego::input(){
    while(motor->ventanaPollEvent()){

        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }

        sf::Event *event = motor->getEvent();
        if (event->type == sf::Event::KeyPressed){
            motor->getSonidoSeleccion()->Play();
            CambiarEstado();
        }
    }
}