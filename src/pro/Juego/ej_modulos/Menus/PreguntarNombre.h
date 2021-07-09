#ifndef PREGUNTARNOMBRE_H
#define PREGUNTARNOMBRE_H
#pragma once
#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include <iostream>

class PreguntarNombre : public JuegoState {
    private:
        static PreguntarNombre* pinstance;
        PreguntarNombre();
        ~PreguntarNombre();
        PreguntarNombre(const PreguntarNombre & );
        PreguntarNombre &operator= (const PreguntarNombre & );

        int num_items=2;
        Motor *motor=NULL;
        Texto *nombres[2];  // casillas opciones
        Sprite *fondo;
        Sprite *logo;
        sf::String playerInput;
        Texto *playerText;
        
        void CambiarEstado() override;
        bool borrar; // para el input, me dice si se ha presionado backspace
        

    public:
        static PreguntarNombre* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
};

#endif