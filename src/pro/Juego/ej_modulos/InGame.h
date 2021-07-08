#ifndef INGAME_H
#define INGAME_H
#pragma once
#include "JuegoState.h"
#include "Menus/MenuMundo.h"
#include "Partida.h"
#include "Player.h"
#include "Motor.h"
#include "Hud.h"
#include "Nivel.h"
#include <iostream>

class InGame : public JuegoState {
    private:

        InGame();
        ~InGame();
        InGame(const InGame & );
        InGame &operator= (const InGame & );

        static InGame* pinstance;
          
        Motor *motor=NULL;
        Nivel* nivel=NULL;
        Player *p1=NULL;
        sf::Clock updateClock;
        Texto *textoNivel;
        Texto *textoFondo;
        int alpha = 0;
        bool subiendo_alpha = true;
        bool renderizar_texto = true;
        
        float gravedad;
        bool cambiando_gravedad_izq; //animacion 
        bool cambiando_gravedad_drcha; //animacion 
        bool cambiando_gravedad_volando; //vale true desde que se acaba la animacion hasta que aterrizo
        int cont_gravedad; //lleva el contador de 0 a 90 grados para la animacion
        int dir_gravedad; // direccion de la gravedad (0 normal, 1 rotada 90º, ...)
        sf::Clock mundo2reloj;

    public:
        static InGame* Instance();
         
        void render(float ) override;
        void update() override;
        void input() override;
        
        void CambiarEstado() override;
        void reseteaGravedad(){dir_gravedad=0;};
        void reseteaRenderizarTexto(){renderizar_texto=true; alpha=0;};
        bool getDentroPortal(){return nivel->getDentroPortal();};
};

#endif