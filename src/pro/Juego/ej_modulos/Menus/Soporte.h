#ifndef SOPORTE_H
#define SOPORTE_H
#pragma once
#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include <iostream>

class Soporte : public JuegoState {
    private:
        static Soporte* pinstance;
        Soporte();
        ~Soporte();
        Soporte(const Soporte & );
        Soporte &operator= (const Soporte & );
        Motor *motor=NULL;
        Texto *nombres;  // casillas opciones
        Sprite *fondo;
        void CambiarEstado() override;


    public:
        static Soporte* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
};

#endif