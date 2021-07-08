#ifndef CREDITOS_H
#define CREDITOS_H
#pragma once
#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include <iostream>

class Creditos : public JuegoState {
    private:
        static Creditos* pinstance;
        Creditos();
        ~Creditos();
        Creditos(const Creditos & );
        Creditos &operator= (const Creditos & );

        int num_items=6;
        Motor *motor=NULL;
        Texto *nombres[6];  // casillas opciones
        Sprite *fondo;
        Sprite *logo;
        
        void CambiarEstado() override;
        
        

    public:
        static Creditos* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
};

#endif