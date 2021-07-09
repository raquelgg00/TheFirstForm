#ifndef RANKING_H
#define RANKING_H
#pragma once

#include "JuegoState.h"
#include "Motor.h"
#include "Texto.h"
#include "Sprite.h"
#include "Partida.h"
#include "../ej_modulos/mysql/mysql.h"
#include <string>
#include <sstream>



class Ranking : public JuegoState {

    private:
        static Ranking* pinstance;
        Ranking();
        ~Ranking();
        Ranking(const Ranking & );
        Ranking &operator= (const Ranking & );    
        void CambiarEstado() override;

        Motor *motor=NULL;
        Texto *nombres[10];  // casillas opciones
        Sprite *fondo;
        Sprite *logo;
        int num_items = 10;


    public:
        static Ranking* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override; 

};
#endif


