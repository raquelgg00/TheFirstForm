#ifndef CAMBIORESOLUCION_H
#define CAMBIORESOLUCION_H
#pragma once
#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include <iostream>

class CambioResolucion : public JuegoState {
    private:
        static CambioResolucion* pinstance;
        CambioResolucion();
        ~CambioResolucion();
        CambioResolucion(const CambioResolucion & );
        CambioResolucion &operator= (const CambioResolucion & );

        Motor *motor=NULL;
        Texto *nombres;  // casillas opciones
        Sprite *fondo;
        
        void CambiarEstado() override;
        
        int estadoAnterior;

    public:
        static CambioResolucion* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
        void setEstadoAnterior(int est){estadoAnterior=est;};
};

#endif