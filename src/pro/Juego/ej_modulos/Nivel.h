#ifndef NIVEL_H
#define NIVEL_H
#pragma once
#include "Mapa.h"
#include "Entidad.h"
#include "Entidades/Plataforma.h"
#include "Enemigos/Bolita.h"
#include "Player.h"
#include "Enemigos/Canion.h"
#include "Entidades/Cubo.h"
#include "Entidades/Sensor.h"
#include "Entidades/Pared.h"
#include "Entidades/Arista.h"
#include "Enemigos/Molino.h"
#include "Collision.h"
#include "Ayuda.h"
#include "CampoGravedad.h"
#include "Entidades/Puerta.h"
#include "Entidades/Secreto.h"
#include "ObjetoMundo2.h"

class Nivel{

    public:
        static Nivel* Instance();
        ~Nivel();
        void cambiarNivel(int num);
        void render(float);
        void update(int);
        //colision personaje mapa
        void colisionMapaPersonaje(int);        
        bool getColisionTop(int**,bool);
        bool getColisionDown(int**,bool);
        bool getColisionLeft(int**,bool);
        bool getColisionRigth(int**,bool);

        //colision entidad mapa
        void colisionMapaEntidad(Entidad*);
        bool getColisionTopEntidad(int**,Entidad*);
        bool getColisionDownEntidad(int**,Entidad*);
        bool getColisionLeftEntidad(int**,Entidad*);
        bool getColisionRigthEntidad(int**,Entidad*);

        //getters y setters
        int getNumNivel(){return numNivel;};
        void setNumNivel(int num){numNivel=num;};
        bool getCompletado(){return completado;};
        bool getDentroPortal(){return dentro_portal;};

        //inline sf::IntRect FToIRect(sf::FloatRect);
        //bool PixelPerfectCollision(Sprite, Sprite, sf::Image, sf::Image);
        
    protected:
        Nivel();
        Nivel(const Nivel & );
        Nivel &operator= (const Nivel & );
        void cargarMapa();
        void cargarEntidades();
        void cargarMundo2();
        void morision();
        bool evolucionBuena();
        
    private:
        bool completado;
        static Nivel* pinstance;
        int numNivel; // numero del nivel actual
        int contEntidades;
        Mapa* mapa = NULL;
        Ayuda* ayuda = NULL;
        Player* player = NULL;
        XMLDocument listaMapas;
        Entidad** entidades = NULL;
        ObjetoMundo2 **mundo2=NULL;
        int contMundo2;
        bool portal;
        int inicioPortal[2];
        int finPortal[2];
        bool dentro_portal;
        bool resetea_gravedad;
        int dir_gravedad;   
};
#endif