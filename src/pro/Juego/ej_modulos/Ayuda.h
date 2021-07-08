#ifndef AYUDA_H
#define AYUDA_H

#pragma once
#include "../Motor/Sprite.h"
#include "../Motor/Motor.h"

class Ayuda{
    
    
    public:
        Ayuda();
        Ayuda(int,int,int);
        ~Ayuda();
        void render();
        Sprite* getSprite() {return sprite;};


    private:

        Sprite *sprite = NULL;
        Motor *motor=NULL;
        int x;
        int y;
};
#endif