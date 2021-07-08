#ifndef PUERTA_H
#define PUERTA_H
#pragma once
#include "../Motor/Sprite.h"
#include "Entidad.h"
#include "Nivel.h"
#include "Player.h"
#include <vector>

class Puerta: public Entidad{
    
    
    public:
        Puerta();
        Puerta(int, int, int);
        ~Puerta();
        
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

        void agregarSensor(Sensor* sens){sensores.push_back(sens);};
        void comprobarApertura();


    private:

        Motor *motor;
        Player *player;
        Sprite *sprite;

        int height, width;
        int x;
        int y;

        int tipo; //0 vertical 1 horizontal
        int current_coin_frame;
        int i;
        bool abierta;
        bool alguna_vez_abierta = false;

        sf::Clock clock;
        vector<Sensor*> sensores;

        bool final_animacion = false;

};
#endif