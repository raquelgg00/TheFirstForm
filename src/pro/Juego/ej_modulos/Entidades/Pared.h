#ifndef PARED_H
#define PARED_H
#pragma once

#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "Enemigos/PinchoPared.h"

class Pared: public Entidad{

    private:
        Motor *motor;
        Sprite *sprite;
        float x,y;
        float alto, ancho;
        PinchoPared *pinchos[3];
        bool romper = false;
        int i = 0;

    public:
        Pared();
        Pared(int, int, int);
        ~Pared();
        
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int g) override;

        bool onCollisionPlayerTop();
        bool onCollisionPlayerDown();
        bool onCollisionPlayerRight();
        bool onCollisionPlayerLeft();

        float getX() override{return x;};
        float getY() override{return y;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *) override{};
        PinchoPared* getPincho1(){return pinchos[0];};
        PinchoPared* getPincho2(){return pinchos[1];};
        PinchoPared* getPincho3(){return pinchos[2];};


};

#endif