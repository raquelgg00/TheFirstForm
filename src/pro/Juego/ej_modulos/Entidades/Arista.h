#ifndef ARISTA_H
#define ARISTA_H

#pragma once
#include "../Motor/Sprite.h"
#include "Entidad.h"
#include "Nivel.h"
#include "Plataforma.h"

class Arista: public Entidad{
    
    
    public:
        Arista();
        Arista(int, int);
        ~Arista();
        
        void onCollisionPlayer(int) override;
       
        
        void updatemover() override;
        void render(float ) override;

        int getPositionX(){return x;};
        int getPositionY(){return y;};
        void setPosition(int, int) override;

        float getX() override{return x;};
        float getY() override{return y;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *) override{};


    private:

        Sprite *sprite = NULL;
        Motor* motor = NULL;
        int x;
        int y;
        int width, height;
        sf::Clock clock;
        int current_coin_frame;
        int i;
      

};
#endif