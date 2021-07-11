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

        Motor *motor=NULL;
        Sprite *fondo;
        Sprite *fondo2;
        sf::String playerInput;
        Texto *playerText;
        Texto *disponibilidad;
        
        void CambiarEstado() override;
        bool borrar; // para el input, me dice si se ha presionado backspace
        bool insert; //para cuando se envie el nombre, me dice si ha presionado Enter
        bool compruebaNombre;
        bool reiniciar;
        bool nombre_disponible = false;
        bool conect=false;

    public:
        static PreguntarNombre* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;
        void setConnect(bool b){conect=b;}
};

#endif