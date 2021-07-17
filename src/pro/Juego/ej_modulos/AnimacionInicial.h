#ifndef ANIMACIONINICIAL_H
#define ANIMACIONINICIAL_H
#pragma once
#include "Partida.h"
#include "JuegoState.h"
#include "Sprite.h"
#include "Motor.h"
#include <string>
#include <sstream>


class AnimacionInicial : public JuegoState {

    private:
        AnimacionInicial();
        ~AnimacionInicial();
        void CambiarEstado() override;
        static AnimacionInicial* pinstance;
        Sprite *frame;
        Motor *motor=NULL;
        int cont;
		bool enter_pulsado = false;

    public:
        static AnimacionInicial* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  

};

#endif