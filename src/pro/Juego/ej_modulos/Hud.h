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
        Sprite* monedas;
        Sprite* bloqueo;
        Sprite* reloj;
        FlotanteInterpolado *posicion;//habilidades
        FlotanteInterpolado *posicion2;//nivel
        FlotanteInterpolado *posicion3;//reloj
        FlotanteInterpolado *posicion_moneda;
        FlotanteInterpolado *posicion_muertes;
        Texto* texto;
        Texto* textoFondo;
        Texto* cont_segundos;
        Motor* motor;
        Texto* muertes;
        int nivel;
        float x,y;

};

#endif