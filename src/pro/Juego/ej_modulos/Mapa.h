#include <iostream>
#include <sstream>
#include <algorithm>
#include "tinyxml2/tinyxml2.h"
#include "Motor.h"

using namespace tinyxml2;
using namespace std;

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
        bool getAyuda(){return ayuda;};
        int *getInicioAyuda(){return initAyuda;};

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
        bool ayuda;

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
        void cargarTilemap(XMLElement* map);
        void cargarAtributos(XMLElement* map);
        void cargarCapas(XMLElement* map);
        void getDinamicoMapa(XMLElement* map); //Sirve para coger informacion dinamica sobre el mapa
        void getEstaticoMapa(XMLElement* map); //Sirve para coger informacion estatica sobre el mapa
        void inicioNivel(XMLElement* map);
        void getDatosMundo2(XMLElement* map);
};