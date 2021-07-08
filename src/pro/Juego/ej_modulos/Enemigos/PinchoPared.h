#ifndef PINCHOPARED_H
#define PINCHOPARED_H
#pragma once

#include "Sprite.h"
#include "Motor.h"
#include "FlotanteInterpolado.h"


class PinchoPared{

    private:      
        Motor *motor;
        Sprite *sprite;
        FlotanteInterpolado *posicion;
        int x,y;
        int direccion; // 0 arriba, 1 drcha, 2 abajo, 3 izq

    public:
        PinchoPared();
        PinchoPared(int x_ini, int y_ini, int rotacion);
        ~PinchoPared();
        /*
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer() override;
        void setColisionesMapa(bool *colisones) override;
        float getX() override{return x;};
        float getY() override{return y;};
        Sprite* getSprite() override{return sprite;};
        */
        void setPosition(int, int);
        void updatemover() ;
        void render(float) ;
        void onCollisionPlayer() ;
        void setColisionesMapa(bool *colisones) ;
        float getX() {return x;};
        float getY() {return y;};
        Sprite* getSprite() {return sprite;};
        FlotanteInterpolado* getPosicion(){return posicion;};
};

#endif

