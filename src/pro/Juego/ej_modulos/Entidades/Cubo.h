#ifndef CUBO_H
#define CUBO_H

#pragma once
#include "../Motor/Sprite.h"
#include "Entidad.h"
#include "Nivel.h"
#include "Plataforma.h"

class Cubo: public Entidad{
    
    
    public:
        Cubo();
        Cubo(int, int, int);
        ~Cubo();
        
        void onCollisionPlayer(int g) override;
        bool colisionLeft(), colisionRight(), colisionTop(),colisionDown();
        
        void updatemover() override;
        void render(float) override;

        int getPositionX(){return x;};
        int getPositionY(){return y;};
        void setPosition(int, int) override;

        float getX() override{return x;};
        float getY() override{return y;};
        float getWidth() {return width;};
        float getHeight() {return height;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *colisones) override;
        void setColisionCuboCubo(bool b){colisionCuboCubo = b;};
        void setColisionCuboPlataforma(bool b){colisionCuboPlataforma = b;};
        void setVelocidadXPlataforma(float f){velocidadXPlataforma = f;};

        void setColisionesDinam(bool *);
        void setColisionesDinamRight(bool colisiones){colisionesDinam[2] = colisiones;};
        void setColisionesDinamLeft(bool colisiones){colisionesDinam[3] = colisiones;};
        void setColisionesDinamTop(bool colisiones){colisionesDinam[0] = colisiones;};
        void setColisionesDinamDown(bool colisiones){colisionesDinam[1]=colisiones;};

    private:

        int dir_grav = 0;
        Sprite *sprite = NULL;
        Motor* motor = NULL;
        int x;
        int y;
        float velocidad_x;
        float velocidad_y;
        int width, height;
        bool colisionesMapa[4];
        bool en_suelo;
        bool colisionCuboCubo;
        bool colisionCuboPlataforma;
        float velocidadXPlataforma; // se usa para cuando el cubo esta encima de una plataforma
        FlotanteInterpolado *posicion;
        bool colisionesDinam[4];

       

};
#endif