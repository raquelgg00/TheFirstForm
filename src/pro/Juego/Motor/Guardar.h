#ifndef GUARDAR_H
#define GUARDAR_H
#include "../ej_modulos/tinyxml2/tinyxml2.h"
#include <iostream>
using namespace tinyxml2;


class Guardar{
    public:
        ~Guardar();
        static Guardar* Instance();

        //getters
        int getMusica(){return musica;};
        int getSonido(){return sonido;};
        int getResolucion(){return resolucion;};
        int getNivel(){return nivelMax;};
        int getMonedas(){return numMonedas;};
        int getHabilidades(){return habilidades;};
        
        //setters
        void setMusica(int vol);
        void setSonido(int vol);
        void setResolucion(int res);
        void setResolucionAtr(int res);
        void setNivel(int niv);
        //void setNivelReinicio();
        void setMonedas(int mon);
        void setHabilidades(int hab);
        //void setHabilidReinicio();
        void setHabilidadesAtrib(int hab);

        void reiniciarPartida();

    private:
        Guardar();
        static Guardar* pinstance;
        int musica;
        int sonido;
        int resolucion;
        int nivelMax;
        int numMonedas;
        int habilidades;
        XMLDocument doc;
};

#endif