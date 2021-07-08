#ifndef CONTROLES_H
#define CONTROLES_H
#pragma once
#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include <iostream>

class Controles : public JuegoState {
    private:
        static Controles* pinstance;
        Controles();
        ~Controles();
        Controles(const Controles & );
        Controles &operator= (const Controles & );

        Motor *motor=NULL;
        Texto *nombres;  // casillas opciones
        Sprite *fondo;
        
        void CambiarEstado() override;
        
        int estadoAnterior;

    public:
        static Controles* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
        void setEstadoAnterior(int est){estadoAnterior=est;};
};

#endif