#ifndef HUD_H
#define HUD_H

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Sprite.h"
#include "Motor.h"
#include "Texto.h"
#include "Player.h"
#include "FlotanteInterpolado.h"

class Hud {

    public:
        static Hud* Instance();
        void update(int,int);
        void render(float, bool,bool);
        ~Hud();
        void setRotacion(float);
    protected:
        Hud();
        Hud(const Hud & );
        Hud &operator= (const Hud & );
    private:
        static Hud* pinstance;
        Sprite* habilidades;
        Sprite* secreto1;
        Sprite* secreto2;
        Sprite* secreto3;
        Sprite* bloqueo;
        Sprite* reloj;
        Sprite *fondo;
        Sprite *calavera;
        FlotanteInterpolado *posicion;//habilidades
        FlotanteInterpolado *posicion2;//nivel
        FlotanteInterpolado *posicion3;//reloj
        FlotanteInterpolado *posicion_moneda;
        FlotanteInterpolado *posicion_moneda2;
        FlotanteInterpolado *posicion_moneda3;
        FlotanteInterpolado *posicion_muertes;
        FlotanteInterpolado *posicion_calavera;
        FlotanteInterpolado *posicion_fondo;
        Texto* texto;
        Texto* cont_segundos;
        Motor* motor;
        Texto* muertes;
        int nivel;
        float x,y;

};

#endif