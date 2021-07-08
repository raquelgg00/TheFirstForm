#include "Audio.h"
#include <iostream>

Audio::Audio(){
    
}
Audio::~Audio(){
    
}

// Cambia el volumen
void Audio::setVolume(int n1){
    sonido.setVolume(n1);
    volumen=n1;
}

// Carga el sonido del fichero que se le pasa como parametro
void Audio::setBuffer(std::string s){    
	if (!buffer.loadFromFile(s))
	{
		std::cout<<"ERROR AL CARGAR EL SONIDO\n";
        exit(1);
	}
    sonido.setBuffer(buffer);
}

// Reproduce el audio
void Audio::Play(){
    sonido.play();    
}

// Si le pasamos true pone en bucle el audio; false lo deja de poner en bucle
void Audio::SetLoop(bool b){
    sonido.setLoop(b);
}

void Audio::pause(){
    sonido.pause();
}