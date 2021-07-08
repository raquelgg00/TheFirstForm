#ifndef BALA_H
#define BALA_H
#include "Sprite.h"
#include "Motor.h"
#include "FlotanteInterpolado.h"

class Bala{
    public:
        Bala();
        Bala(float, float);
        //Enemigo(float pos_x, float pos_y, int dir_x, int dir_y, bool en_movimiento);
        virtual ~Bala();
        Sprite* getSprite(){return sprite;};
        void mover();
        void render(float);
        bool getTengoPosFin();
        void setTengoPosFin(bool);
        float get_pos_inicial_x(){return pos_inicial_x;}
        float get_pos_inicial_y(){return pos_inicial_y;}
        float get_pos_final_x(){return pos_final_x;}
        float get_pos_final_y(){return pos_final_y;}
        float get_X(){return x;}
        float get_Y(){return y;}

        void setPosFin_x(float);
        void setPosFin_y(float);
        void setavanzo_x(float);
        void setavanzo_y(float);
        float getavanzo_x();
        float getavanzo_y();
        void resetea();
        

    private:
   
        Sprite *sprite;
        float x,y;
        FlotanteInterpolado *posicion;
        sf::Clock reloj;
        float pos_inicial_x;
        float pos_inicial_y;
        float pos_final_x;
        float pos_final_y;
        bool tengo_pos_fin;
        float avanzo_x;
        float avanzo_y;

};

#endif 