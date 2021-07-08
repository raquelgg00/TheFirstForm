#ifndef OPCIONES_H
#define OPCIONES_H
#pragma once
#include "JuegoState.h"
#include "Partida.h"
#include "InGame.h"
#include "Sprite.h"
#include "Motor.h"
#include "MenuMundo.h"
#include "Texto.h"
#include "CambioResolucion.h"
#include <iostream>

class Opciones : public JuegoState {
    private:
        static Opciones* pinstance;
        Opciones();
        ~Opciones();
        Opciones(const Opciones & );
        Opciones &operator= (const Opciones & );

        int num_items=4;
        int selectedItem; // nivel seleccionado
        int resolucion; // nivel seleccionado
        Motor *motor=NULL;
        Texto *opciones[4];  // casillas opciones
        Sprite *flechitas[6];  // casillas opciones
        Texto *resoluciones[2];  // resoluciones posibles
        Sprite *fondo;
        Sprite *volumenMusica;
        Sprite *volumenSonido;
        int numMusica;
        int numSonido;
        float x_cursor, y_cursor; // posicion del raton
        int click_flechita = -1; //0 para la primera, 1 para la segunda, ...

        int estadoAnterior;
        
        void MoveUp();
        void MoveDown();
        void MoveRight();
        void MoveLeft();
        void CambiarEstado() override;
        
        

    public:
        static Opciones* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override; 
        void setEstadoAnterior(int est){estadoAnterior=est;}; 
};

#endif