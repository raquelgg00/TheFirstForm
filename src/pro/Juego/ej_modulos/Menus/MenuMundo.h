#ifndef MENUMUNDO_H
#define MENUMUNDO_H
#pragma once
#include "JuegoState.h"
#include "Partida.h"
#include "InGame.h"
#include "Pausa.h"
#include "Sprite.h"
#include "Motor.h"
#include "Hud.h"
#include "Nivel.h"
#include <iostream>

class MenuMundo : public JuegoState {
    private:
        static MenuMundo* pinstance;
        MenuMundo();
        ~MenuMundo();
        MenuMundo(const MenuMundo & );
        MenuMundo &operator= (const MenuMundo & );

        int num_items=16;
        int selectedItem; // nivel seleccionado
        Motor *motor=NULL;
        Sprite *sprite[16];  // Sprites de las casillas de cada nivel 
        Sprite *flechita;
        Sprite *fondo;

        void MoveRight();
        void MoveLeft();
        void CambiarEstado() override;
        
        FlotanteInterpolado *posicion=NULL;
        

    public:
        static MenuMundo* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
        void actualiza_colores();
};

#endif