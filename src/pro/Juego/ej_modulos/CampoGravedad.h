#ifndef CAMPOGRAVEDAD_H
#define CAMPOGRAVEDAD_H
#pragma once
#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "Player.h"
#include "FlotanteInterpolado.h"

class CampoGravedad: public Entidad{

    private:      
        Motor *motor;
        Sprite *sprite;
        FlotanteInterpolado *posicion;
        int x,y, tipo;

    public:
        CampoGravedad();
        CampoGravedad(int x_ini, int y_ini, int t);
        ~CampoGravedad();
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int) override;
        void setColisionesMapa(bool *colisones) override;
        float getX() override{return x;};
        float getY() override{return y;};
        int getTipo(){return tipo;};
        FlotanteInterpolado* getPosicion(){return posicion;};
        Sprite* getSprite() override{return sprite;};

        sf::Clock clock;
        int current_coin_frame = 0;
        int i_max = 11;
};

#endif
