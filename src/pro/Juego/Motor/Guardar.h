#ifndef GUARDAR_H
#define GUARDAR_H
#include "../ej_modulos/tinyxml2/tinyxml2.h"
#include <iostream>
//#include <msxml.h>

//using namespace tinyxml2;


class Guardar{
    public:
        ~Guardar();
        static Guardar* Instance();

        //getters
        int getMusica(){return musica;};
        int getSonido(){return sonido;};
        int getResolucion(){return resolucion;};
        int getNivel(){return nivelMax;};
        int getSecreto1(){return secreto1;};
        int getSecreto2(){return secreto2;};
        int getSecreto3(){return secreto3;};
        int getHabilidades(){return habilidades;};
        int getMuertes(){return num_muertes;};
        std::string getNombre();

        int getTerminado(){return terminado;};
        
        //setters
        void setMusica(int vol);
        void setSonido(int vol);
        void setResolucion(int res);
        void setResolucionAtr(int res);
        void setNivel(int niv);
        void setTerminado(int fin);
        void setMuertes(int muertes);
        //void setNivelReinicio();
        void setMonedas(int mon);
        void setHabilidades(int hab);
        //void setHabilidReinicio();
        void setHabilidadesAtrib(int hab);
        void setNombre(std::string);

        void reiniciarPartida();

    private:
        Guardar();
        static Guardar* pinstance;
        int musica;
        int sonido;
        int resolucion;
        int nivelMax;
        int secreto1;
        int secreto2;
        int secreto3;
        int habilidades;
        int num_muertes;
        std::string nombre;
        int terminado;
		tinyxml2::XMLDocument doc;
};

#endif