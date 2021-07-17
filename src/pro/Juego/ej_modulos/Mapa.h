#include <iostream>
#include <sstream>
#include <algorithm>
//#include <msxml.h>
#include "tinyxml2/tinyxml2.h"
#include "Motor.h"

using namespace std;
//using namespace tinyxml2;

class Mapa{
    
    public:
        Mapa(const char* nombre);
        ~Mapa();
        Mapa();
        void render();
        Mapa(const Mapa & );
        Mapa &operator= (const Mapa & );

        int **getDatosDinamicos(){return datosDinamicos;};
        int getContDinamicos(){return contDinamicos;};
        int **getDatosEstaticos(){return datosEstaticos;};
        int getContEstaticos(){return contEstaticos;};

        int *getInicioPersonaje(){return initPersonaje;};
        int getAyuda(){return ayuda;};
        int *getInicioAyuda(){return initAyuda;};
        int *getInicioAyuda2(){return initAyuda2;};

        int **getDatosMundo2(){return datosMundo2;};
        int getContMundo2(){return contMundo2;};
                            
        bool getPortal(){ return portal;};
        int *getInicioPortal(){return inicioPortal;};
        int *getFinPortal(){return finPortal;};
    private:
        int width;
        int height;
        int tileWidth;
        int tileHeight;
        int spacing;
        int capas;
        int numGid;
        int tileColumns;
        int ***tilemap;
        const char* imgfile;
        sf::Texture tex;
        sf::Sprite ****tilemapSprite;
        sf::Sprite **tilesetSprite;
        Motor *motor = NULL;

        //COLISIONES
        int **datosEstaticos; //Matriz que contiene los datos de los objetos estaticos
        int **datosDinamicos; //Matriz que contiene los datos de los objetos dinamicos
        int contEstaticos; //Cantidad de objetos estaticos
        int contDinamicos; //Cantidad de objetos dinamicos
        
        //DATO INICIAL PERSONAJE 
        int initPersonaje[2];//x e y inicial del personaje

        //DATO INICIAL AYUDA
        int initAyuda[2];//x e y inicial de la ayuda
        int initAyuda2[2];//x e y inicial de la ayuda
        int ayuda;

        //DATO MUNDO2
        int **datosMundo2;
        int contMundo2;

        //DATO PORTAL
        int inicioPortal[2], finPortal[2];
        bool portal=false;
        
        //METODOS PARA EL CONSTRUCTOR
        void cargarSprites();
        void cargarTilesetSprites();
        void reservarMemoria();
        void cargarTilemap(tinyxml2::XMLElement* map);
        void cargarAtributos(tinyxml2::XMLElement* map);
        void cargarCapas(tinyxml2::XMLElement* map);
        void getDinamicoMapa(tinyxml2::XMLElement* map); //Sirve para coger informacion dinamica sobre el mapa
        void getEstaticoMapa(tinyxml2::XMLElement* map); //Sirve para coger informacion estatica sobre el mapa
        void inicioNivel(tinyxml2::XMLElement* map);
        void getDatosMundo2(tinyxml2::XMLElement* map);
};