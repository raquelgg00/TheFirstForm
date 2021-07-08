#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#pragma once
#include "../Motor/Sprite.h"
#include "Entidad.h"
#include "Nivel.h"
#include "Player.h"
#include "FlotanteInterpolado.h"

class Plataforma: public Entidad{
    
    
    public:
        Plataforma();
        Plataforma(int, int, int, int, int, int, int, bool);
        ~Plataforma();
        
        void updatemover() override;
        void onCollisionPlayer(int) override;
        bool colisionLeft(), colisionRight(), colisionTop(),colisionDown();
        void render(float) override;

        int getPositionX(){return x;};
        int getPositionY(){return y;};
        void setPosition(int, int) override;

        float getX() override{return x;};
        float getY() override{return y;};
        float getWidth() {return width;};
        float getHeight() {return height;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *) override{};

        float getVelX(){return velx;};
        float getVelY(){return vely;};

        //FlotanteInterpolado *getPosicion(){return posicion;};
        //void colision(void);


    private:

        Motor *motor;
        Player *player;
        Sprite *sprite;

        int height, width;
        int x, x_fin, x_ini;
        int y, y_fin, y_ini;
        float velx, vely;

        FlotanteInterpolado *posicion;
        sf::Clock reloj;

        int id;
        int mov_vertical, mov_horizontal;
        bool en_movimiento_inicial;

        bool *colisiones;
};
#endif