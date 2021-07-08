#ifndef OBJETOMUNDO2_H
#define OBJETOMUNDO2_H
#pragma once

#include "Sprite.h"
#include "Motor.h"
#include "Player.h"


class ObjetoMundo2{
    private:  
        Motor *motor;
        Sprite *sprite;
        int x,y;
        int width,height;
        bool activo;
        bool colisionDown(); 
        bool colisionTop(); 
        bool colisionLeft(); 
        bool colisionRight(); 

    public:
        ObjetoMundo2();
        ObjetoMundo2(int x_ini, int y_ini);
        ~ObjetoMundo2();
        void render() ;
        void onCollisionPlayer();
        void setPosition(float, float);
        int getX(){return x;};
        int getY(){return y;};
        void setActivo(bool b){activo=b;};
        bool getActivo(){return activo;};
};

#endif