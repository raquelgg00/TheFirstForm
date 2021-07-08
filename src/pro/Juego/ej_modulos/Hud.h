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
        Sprite* bloqueo;
        Sprite* reloj;
        FlotanteInterpolado *posicion;
        FlotanteInterpolado *posicion2;
        FlotanteInterpolado *posicion3;
        Texto* texto;
        Texto* textoFondo;
        Texto* cont_segundos;
        Motor* motor;
        int nivel;
        float x,y;

};

#endif