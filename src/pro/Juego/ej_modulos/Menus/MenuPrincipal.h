#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#pragma once
#include "JuegoState.h"
#include "Partida.h"
#include "Sprite.h"
#include "Motor.h"
#include "MenuMundo.h"
#include "Creditos.h"
#include "Controles.h"
#include "Opciones.h"
#include "Ranking.h"
#include "AnimacionInicial.h"
#include "PreguntarNombre.h"

#include <iostream>

class MenuPrincipal : public JuegoState {
    private:        
        MenuPrincipal();
        ~MenuPrincipal();
        MenuPrincipal(const MenuPrincipal & );
        MenuPrincipal &operator= (const MenuPrincipal & );
        
        void MoveUp();
        void MoveDown();
        void CambiarEstado() override;

        int num_items=6;
        int selectedItem; // nivel seleccionado
        sf::Text opciones[6];  // Sprites de las casillas de cada nivel
        sf::Font font;
        Sprite *fondo;
        Sprite *sprite_antes;
        Motor *motor=NULL;
        
        static MenuPrincipal* pinstance;
        sf::RectangleShape r;

        float x_cursor, y_cursor; // posicion del raton
        int alpha;
        Sprite *fondoTransicion;
        void update_datos_player();

    public:
        static MenuPrincipal* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  
};

#endif