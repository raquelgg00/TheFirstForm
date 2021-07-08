#ifndef MOLINO_H
#define MOLINO_H
#pragma once
#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "Collision.h"
#include "Player.h"
#include "FlotanteInterpolado.h"

class Molino: public Entidad{

    private:      
        Motor *motor;
        Sprite *sprite;
        FlotanteInterpolado *posicion;
        int x,y;
        int velRotacion;
        int direccion; //-1 rotacion antihoraria y 1 horaria

    public:
        Molino();
        Molino(int x_ini, int y_ini, int dir);
        ~Molino();
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int) override;
        void setColisionesMapa(bool *colisones) override;
        float getX() override{return x;};
        float getY() override{return y;};
        FlotanteInterpolado* getPosicion(){return posicion;};
        Sprite* getSprite() override{return sprite;};
};

#endif
