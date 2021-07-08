#include "Partida.h"

Partida* Partida::pinstance = 0;
JuegoState* Partida::state_ = NULL;

// Singleton
Partida* Partida::Instance(){
    if(pinstance == 0){
        pinstance = new Partida;

    }
    return pinstance;
}

// Constructor
Partida::Partida(){
    motor = Motor::Instance();
    
    // Inicializamos el Estado inicial a MenuPrincipal
    state_=InicioJuego::Instance();
    
    gameLoop();
}

// Destructor
Partida::~Partida(){
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }
}

// Actualiza el estado de Partida. Puede ser InGame, MenuMundo, ...
void Partida::setEstado(JuegoState *state) {
    state_ = state;
}


 void Partida::gameLoop(){
    
    while(motor->ventanaIsOpen()){
        state_->input();

        if(relojInterpo.getElapsedTime().asSeconds() > (1/25.f)-0.18){
            motor->setDeltaTime(relojUpdate.restart().asSeconds());
            relojInterpo.restart();
            state_->update();
            
        }
        tickTime=relojInterpo.getElapsedTime().asSeconds();
        state_->render(tickTime);
    }
}