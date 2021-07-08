#ifndef BOLITA_H
#define BOLITA_H
#pragma once
#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "FlotanteInterpolado.h"

class Bolita: public Entidad{

    private:      
        Motor *motor;
        Sprite *sprite;
        int x,y;
        int x_ini, x_fin;
        int y_ini, y_fin;
        FlotanteInterpolado *posicion;
        sf::Clock reloj;
        int velx, vely;
        int mov_horizontal, mov_vertical;
        bool hace_rectangulos;
        bool activa;
        int tipo;
        bool colisionesMapa[4];
        bool ofensiva;
        int dirGravedad=0;
        int iter = 0;
        sf::Clock clock;
        
        /* tipo=0 ira en vertical, horizontal o siguiendo un cuadrado
            tipo=1 ira en horizontal hasta que choque con una pared a la izquierda y cambia de direccion a la derecha
            tipo=2 ira en horizontal pero al principio esta parada y luego se mueve como la de arriba
            tipo=3 bola por plano inclinado  
        */
        float distancia_max_tipo_3=0;

    public:
        Bolita();
        Bolita(int, int, int, int, int, int);
        ~Bolita();
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int) override;
        void setColisionesMapa(bool *colisones) override;
        float getX() override{return x;};
        float getY() override{return y;};
        FlotanteInterpolado* getPosicion(){return posicion;};
        Sprite* getSprite() override{return sprite;};
        void cambiardirHorizontal();
        int getDirHorizontal(){return mov_horizontal;};
        int getTipo(){return tipo;};
        void setColisionRight(bool b){colisionesMapa[2]=b;};
        void setColisionLeft(bool b){colisionesMapa[3]=b;};
        void transformarBolita();
        bool getOfensiva(){return ofensiva;};
       
};

#endif
