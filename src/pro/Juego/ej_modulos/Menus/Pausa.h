#ifndef PAUSA_H
#define PAUSA_H
#pragma once
#include "JuegoState.h"
#include "Partida.h"
#include "InGame.h"
#include "Sprite.h"
#include "Motor.h"
#include "MenuMundo.h"
#include "Controles.h"

#include <iostream>

class Pausa : public JuegoState {
    private:        
        Pausa();
        ~Pausa();
        Pausa(const Pausa & );
        Pausa &operator= (const Pausa & );
        
        void MoveUp();
        void MoveDown();
        void CambiarEstado() override;

        int num_items=5;
        int selectedItem; // nivel seleccionado
        sf::Text opciones[5];  // Sprites de las casillas de cada nivel
        sf::Text opciones2[4];  // Sprites de las casillas de cada nivel
        sf::Font font;
        Sprite *fondo;
        Motor *motor=NULL;
        int estadoAnterior;
        
        static Pausa* pinstance;
        sf::RectangleShape r;
        bool primeraVez=false;
         
        

    public:
        static Pausa* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;
        void setEstadoAnterior(int est){estadoAnterior=est;};
        void setPrimeraVez(bool b){primeraVez=b;};
};

#endif