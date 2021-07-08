#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "../Motor/Sprite.h"
#include "../Motor/Motor.h"
#include "Entidades/Pared.h"
#include "FlotanteInterpolado.h"

class Player{
    public:
        Player();
        Player(const Player & );
        Sprite *getSprite();
        static Player* Instance();

        // Getters y setters - Posicion
        float getX() {return x;};
        float getY() {return y;};
        void setPosition(float, float);

        // Getters y setters - Velocidad
        void setVelocidad_y(float vy){velocidad_y=vy;};
        float getVelocidad_y(){return velocidad_y;};
        void setVelocidad_x(float vx){velocidad_x=vx;};
        float getVelocidad_x(){return velocidad_x;};

        // Getters y setters - Aceleracion
        float getAceleracion_x(){return aceleracion_x;};
        float getAceleracion_y(){return aceleracion_y;};
        void setAceleracion_x(float ax){aceleracion_x=ax;};
        void setAceleracion_y(float ay){aceleracion_y=ay;};

        // Otros Getters y setters
        void setSaltando(bool b){saltando = b;};
        bool getSaltando(){return saltando;};
        bool getRebotando(){return rebotando;};
        void setRebotando(bool b){rebotando = b;};
        void setEnMovimiento(bool b){en_movimiento = b;};
        bool getEnMovimiento(){return en_movimiento;};
        bool getEnSuelo(){return en_suelo;};
        void setEnSuelo(bool b){en_suelo = b;};
        int getHabilidadActiva(){return habilidadActiva;};
        void setHabilidad(int n);
        void setForma();
        void setFormaReset(int form);
        FlotanteInterpolado* getPosicion(){return posicion;};
        sf::Clock getReloj(){return reloj;};
        
        void setMoverDerecha(bool movimiento){movimiento_derecha=movimiento;};
        void setMoverIzquierda(bool movimiento){movimiento_izquierda=movimiento;};

        // Otros metodos
        void update(int);
        void input();
        void mover_derecha(), mover_izquierda();
        void usarHabilidad();
        void saltar(), rebote(), romper(), hacerse_peque();
        bool getArista(){return tengoArista;};
        void setArista(bool ar){tengoArista=ar;};
        void setEncimaBolita(bool b){encimaBolita = b;};

        // Gravedad
        void update_gravedad0(bool);
        void update_gravedad1(bool);
        void setDirGravedad(int n) {dir_gravedad = n;};
        int getDirGravedad(){return dir_gravedad;};
        void reseteaGravedad(bool b){resetea_gravedad=b;};
        bool getReseteaGravedad(){return resetea_gravedad;};
 
        // Colisiones
        void reseteaColisionesMapa();
        void setColisionesMapa(bool *colision);
        void setColisionesDinam(bool *colision);
        void setColisionesPared(bool *colision);
        

        void setContactoVerdeDer(bool valor){contactoVerdeDer=valor;};
        void setContactoVerdeIzq(bool valor){contactoVerdeIzq=valor;};
        void setContactoVerdeDown(bool valor){contactoVerdeDown=valor;};

        void set_vel_plataforma(float f){vel_plataforma = f;};
        //float **getVertices(){return vertices;};

        void setAtravesarObj(bool b){atravesarObj = b;};
        bool getAtravesarObj(){return atravesarObj;};

        bool getMuere(){return muere;};
        void setMuere(bool v){muere=v;};

        int getTiempo_q_activa(){return tiempo_q_activa;};
        void setTiempo_q_activa(int v){tiempo_q_activa=v;};

        


        
    private:
        ~Player();
        //Player &operator= (const Player & );
        static Player* pinstance;

        Motor *motor;
        Sprite *sprite = NULL;
        
        float x,y;
        FlotanteInterpolado *posicion;
        sf::Clock reloj;
        sf::Clock clock;
        
        float velocidad_x, velocidad_y;
        float valorVelociadadX; // valor maximo de la velocidad
        float aceleracion_x, aceleracion_y;
        float alto, ancho;

        bool saltando, rebotando;
        bool en_movimiento;    
        bool en_suelo;
        bool movimiento_derecha=false;
        bool movimiento_izquierda=false;
        
        int habilidadActiva;
        int formaActiva;
        bool colisionesMapa[4];
        bool colisionesDinam[4];
        bool colisionesPared[4];
        bool tengoArista;
        bool muere = false;
        int tiempo_q_activa = 0;
        
        //si esta en contacto con una plataforma verde para rebotar
        bool contactoVerdeDown, contactoVerdeDer, contactoVerdeIzq, contactoRojo;

        int dir_gravedad;
        bool resetea_gravedad;

        bool encimaBolita; // cuando estoy encima de la bola del plano inclinado
        bool atravesarObj;
        
        float vel_plataforma;
        int i;
        int current_coin_frame;
     

};

#endif 