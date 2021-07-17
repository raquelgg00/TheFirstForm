#ifndef CANION_H
#define CANION_H

#include "Entidad.h"
#include "Sprite.h"
#include "Motor.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "math.h"
#include "Bala.h"

class Canion: public Entidad{

    private:  
        Motor *motor;
        Sprite *sprite;
        int x,y;
        int radio_grande, radio_peque;
        Bala *bala;

        // Reloj
        sf::Clock *reloj1;
        sf::Time *tiempo1;

    public:
        Canion();
        Canion(int, int);
        ~Canion();
        void setPosition(int, int) override;
        void updatemover() override;
        void render(float) override;
        void onCollisionPlayer(int g) override;
        float getX() override{return x;};
        float getY() override{return y;};
        Sprite* getSprite() override{return sprite;};
        void setColisionesMapa(bool *) override{};
        Sprite* getSpriteBala();
        Bala* getBala(){return bala;};

};
#endif