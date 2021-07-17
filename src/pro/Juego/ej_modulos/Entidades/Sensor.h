#ifndef SENSOR_H
#define SENSOR_H
#pragma once
#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "Player.h"

class Sensor: public Entidad{
    
    public:
        Sensor();
        Sensor(int, int);
        ~Sensor();
    
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int g) override;

        int getPositionX(){return x;};
        int getPositionY(){return y;};
        bool getPresionado(){return presionado;};
        void setPresionado(bool presion){presionado=presion;};
        void setPosition(int, int) override;

        float getX() override{return x;};
        float getY() override{return y;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *) override{};

      
    private:
        Player *p;
        Motor* motor;
        Sprite *sprite;
        int x;
        int y;
        float velx;
        float vely;
        bool presionado;
        bool tiene_que_sonar;

};
#endif