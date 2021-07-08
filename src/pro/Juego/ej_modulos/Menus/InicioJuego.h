#ifndef INICIOJUEGO_H
#define INICIOJUEGO_H
#pragma once
#include "Partida.h"
#include "JuegoState.h"
#include "Sprite.h"
#include "Texto.h"
#include "MenuPrincipal.h"
#include "SFML/Graphics/Image.hpp"



class InicioJuego : public JuegoState {

    private:
        static InicioJuego* pinstance;
        InicioJuego();
        ~InicioJuego();
        void CambiarEstado() override;
        Sprite *fondoTransicion;
        Sprite *sprite;
        Sprite *texto_sprite;
        Motor *motor;
        bool aumentando_tamanio;
        int alpha;


    public:
        static InicioJuego* Instance(); 
        void render(float ) override;
        void update() override;
        void input() override;  

};
#endif