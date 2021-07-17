#include "AnimacionInicial.h"

// Singleton 
AnimacionInicial* AnimacionInicial::pinstance = 0;
AnimacionInicial* AnimacionInicial::Instance(){
    if(pinstance == 0){
        pinstance = new AnimacionInicial;

    }
    return pinstance;
}


// Constructor
AnimacionInicial::AnimacionInicial(){

    // Motor
    motor = Motor::Instance();

    // Frame inicial
    frame = new Sprite();
    frame->setTexture("../AnimacionConExplicacion/AnimacionFinal_000000","jpeg");
    cont = 0;
      
}


// Destructor
AnimacionInicial::~AnimacionInicial(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }


    if(frame!=NULL){
        delete frame;
        frame=NULL;
    }
}

void AnimacionInicial::CambiarEstado(){
    //motor->getMusicaAnimacion()->pause();
    //motor->getMusica()->Play();
    Partida::setEstado(InGame::Instance());
}

void AnimacionInicial::input() {

	enter_pulsado = false;

	while (motor->ventanaPollEvent()) {
		if (motor->eventTypeClosed()) {
			motor->ventanaClose();
		}
	}
	if (motor->isKeyPressedEnter()) {
		enter_pulsado = true;
	}
}

void AnimacionInicial::update(){

    // Usando un solo frame a la vez
    
    std::string path = "../AnimacionConExplicacion/AnimacionFinal_";

    std::ostringstream ss;
    ss << cont;
    ss.str();
    
    std::string numero = ss.str();
    while(numero.length() < 6){
        numero = "0" + numero;
    }
    
    frame->setTexture(path+numero,"jpeg");
    if(motor->getTamHeight()==720)
        frame->setScale(0.67, 0.67);
    

	if (cont == 1058 || cont == 1242 || cont == 1392 || cont == 1548) {
		if (enter_pulsado) {
			cont++;
		}
		enter_pulsado = false;
	}
	else {
		// Si cargo todos en el constructor solo dejo esto
		cont += 1;

		if (cont >= 1574) {
			cont = 0;
			CambiarEstado();
		}
	}
}


void AnimacionInicial::render(float tick){
    tick = 0.f;
    motor->ventanaClear(0,0,0);
    motor->ventanaDibuja(frame->getSprite());
    motor->ventanaDisplay();
}

