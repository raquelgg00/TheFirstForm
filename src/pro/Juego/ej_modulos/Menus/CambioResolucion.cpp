#include "CambioResolucion.h"

// Singleton 
CambioResolucion* CambioResolucion::pinstance = 0;
CambioResolucion* CambioResolucion::Instance(){
    if(pinstance == 0){
        pinstance = new CambioResolucion;

    }
    return pinstance;
}

// Constructor
CambioResolucion::CambioResolucion(){

   // Motor
    motor = Motor::Instance();

    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Opciones","png");
    if(motor->getTamHeight()==720)
        fondo->setScale(0.67,0.67);

    //Inicializamos los textos de las opciones
    nombres=new Texto("Para cambiar la resolucion necesitas reiniciar la aplicacion.\n \t\t\t- Presiona ESC para CANCELAR \n \t\t\t- Presiona SPACE para CONFIRMAR");
    if(motor->getTamHeight()==720)
        nombres->setSize(45);
    else
        nombres->setSize(67);

    nombres->setOrigin(nombres->getWidthBounds()/2.f, nombres->getHeightBounds()/2.f);
    nombres->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/2));
    nombres->setColor(255,255,255);
    
}

// Destructor
CambioResolucion::~CambioResolucion(){
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


void CambioResolucion::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp

    Partida::setEstado(Opciones::Instance());
}

void CambioResolucion::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());
    nombres->drawText();
    nombres->setColor(36,207,253);
    motor->ventanaDisplay();
}

void CambioResolucion::update(){

}

void CambioResolucion::input(){
  
    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }
        if(motor->isKeyPressedEscape()){
            motor->getSonidoSeleccion()->Play();
            CambiarEstado();
        } 
        if(motor->isKeyPressedSpace()){
            motor->getSonidoSeleccion()->Play();

            if(Guardar::Instance()->getResolucion() == 720){
                Guardar::Instance()->setResolucion(1080);
            }
            else {
                Guardar::Instance()->setResolucion(720);
            }
            motor->ventanaClose();
            exit(1);
        } 
    }    
}

