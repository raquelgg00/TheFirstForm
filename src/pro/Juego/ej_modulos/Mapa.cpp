#include "Mapa.h"

// Constructor por defecto
Mapa::Mapa(){
    width=0;
    height=0;
    tileWidth=0;
    tileHeight=0;
    spacing=0;
    capas=0;
    numGid=0;
    tileColumns=0;
    inicioPortal[0]=-1;
    inicioPortal[1]=-1;
    finPortal[0]=-1;
    finPortal[1]=-1;
    tilemap=NULL;
    tilemapSprite=NULL;
    tilesetSprite=NULL;
    motor = NULL;
    ayuda=0;
    datosEstaticos=NULL;
    datosDinamicos=NULL;
    contEstaticos=0;
    contDinamicos=0;
    initAyuda[0]=0;
    initAyuda[1]=0;
    initAyuda2[0]=0;
    initAyuda2[1]=0;
    initPersonaje[0]=0;
    initPersonaje[1]=0;
    datosMundo2=NULL;
    contMundo2=0;
}

// Constructor con el numbre del fichero del mapa que tiene que cargar
Mapa::Mapa(const char* nombre){
    Mapa();
    // Motor
    motor=Motor::Instance();

    // Cargo tmx
    XMLDocument doc;
    doc.LoadFile(nombre);

    // Tamaño del mapa y los tiles
    XMLElement* map=doc.FirstChildElement("map");
    
    if(map!=NULL){

        Mapa::cargarAtributos(map);
        Mapa::cargarCapas(map);
        Mapa::reservarMemoria();
        Mapa::cargarTilemap(map);
        Mapa::cargarSprites();
        Mapa::cargarTilesetSprites();
        Mapa::getDinamicoMapa(map);
        Mapa::getEstaticoMapa(map);
        Mapa::inicioNivel(map);
        Mapa::getDatosMundo2(map);

    }
}

Mapa::~Mapa() {
    
  // Mapa
  for(int i=0;i<capas;i++){
    for (int c = 0; c < height; c++){
        if(tilemap[i][c]!=0)
            delete[] tilemap[i][c];
    }
    if(tilemap[i]!=0)
        delete[] tilemap[i];
  }
  if(tilemap!=0)
    delete[] tilemap;


    // Sprites
    for(int i=0;i<capas;i++){
        for (int c = 0; c < height; c++)
        {
            if(tilemapSprite[i][c]!=0)
                delete[] tilemapSprite[i][c];
        }
        if(tilemapSprite[i]!=0)
            delete[] tilemapSprite[i];
    }
    if(tilemapSprite!=0)
        delete[] tilemapSprite;


    // Vector sprites
    if(tilesetSprite!=0)
        delete[] tilesetSprite;

    //matriz de datos estaticos
    for (int i = 0; i < contEstaticos; i++)
    {
        if(datosEstaticos[i]!=0)
            delete[] datosEstaticos[i];
    }
    if(datosEstaticos!=0)
        delete[] datosEstaticos;
      
    //matriz de datos dinamicos
    for (int i = 0; i < contDinamicos; i++)
    {
        if(datosDinamicos[i]!=0)
            delete[] datosDinamicos[i];
    }
    if(datosDinamicos!=0)
        delete[] datosDinamicos;

    //matriz datos mundo 2
    for (int i = 0; i < contMundo2; i++)
    {
        if(datosMundo2[i]!=0)
            delete[] datosMundo2[i];
    }
    if(datosMundo2!=0)
        delete[] datosMundo2;
}



//En teoría esta función busca las x de los object que son todas las plataformas. esta cadena se retorna.
 void Mapa::getDinamicoMapa(XMLElement* map){

    contDinamicos=0;
    int id = 0;
    bool salir = false;

    if(map!=NULL){
        XMLElement* plat = map->FirstChildElement("objectgroup");
        while(plat && salir == false){       

            plat->QueryIntAttribute("id", &id);
            if(strcmp(plat->Attribute("name"), "dinamicas")==0){
            
                if(plat!=NULL){
                    XMLElement* plataforma = plat->FirstChildElement("object");
                    while(plataforma){              
                        plataforma = plataforma->NextSiblingElement("object");
                        contDinamicos++;
                        
                    }
                    salir = true;
                }
           
                datosDinamicos = new int*[contDinamicos];
                for(int i=0;i<contDinamicos;i++){
                    datosDinamicos[i]=new int[7]; 
                }             
            }
            plat = plat->NextSiblingElement(); 
        }
     
        contDinamicos=0;
       
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        if(objectGroup!=NULL){
            while(objectGroup){
                
                objectGroup->QueryIntAttribute("id", &id);
                if(strcmp(objectGroup->Attribute("name"), "dinamicas")==0){
                //if(id==1){
           
                    XMLElement* objecto = objectGroup->FirstChildElement("object");

                    while(objecto){
                        objecto->QueryIntAttribute("x", &datosDinamicos[contDinamicos][1]);
                        objecto->QueryIntAttribute("y", &datosDinamicos[contDinamicos][2]);

                        if(strcmp(objecto->Attribute("name"), "plataforma")==0){
                            datosDinamicos[contDinamicos][0]=1; //es plataforma
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "movimiento")==0){
                                        bool mov;
                                        property->QueryBoolAttribute("value", &mov);
                                        if(mov) datosDinamicos[contDinamicos][3] = 1;
                                        else datosDinamicos[contDinamicos][3] = 0;
                                        
                                    }
                                    else if(strcmp(property->Attribute("name"), "x_fin")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][4]);
                                    }
                                    else if(strcmp(property->Attribute("name"), "y_fin")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][5]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                               
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "bola")==0){
                            datosDinamicos[contDinamicos][0]=2; //es bola
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "tipo")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                
                                    }
                                    else if(strcmp(property->Attribute("name"), "x_fin")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][4]);
                            
                                    }
                                    else if(strcmp(property->Attribute("name"), "y_fin")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][5]);
                                    }
                                    else if(strcmp(property->Attribute("name"), "distancia")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][6]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                              
                            }

                        }
                        else if(strcmp(objecto->Attribute("name"), "pared")==0){
                            datosDinamicos[contDinamicos][0]=3; //es pared
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "pinchos")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "canion")==0){
                            datosDinamicos[contDinamicos][0]=4; //es canion
                        }
                        else if(strcmp(objecto->Attribute("name"), "bala")==0){
                            datosDinamicos[contDinamicos][0]=5; //es canion
                        }
                        else if(strcmp(objecto->Attribute("name"), "moneda")==0){
                            datosDinamicos[contDinamicos][0]=6; //es moneda
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "arista")==0){
                            datosDinamicos[contDinamicos][0]=7; //es arista
                        }
                        else if(strcmp(objecto->Attribute("name"), "cubo")==0){
                            datosDinamicos[contDinamicos][0]=8; //es cubo
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "altura")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "sensor")==0){
                            datosDinamicos[contDinamicos][0]=9; 
                        }
                        else if(strcmp(objecto->Attribute("name"), "molino")==0){
                            datosDinamicos[contDinamicos][0]=10; 
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "direccion")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "campoGravedad")==0){
                            datosDinamicos[contDinamicos][0]=11; 
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "tipo")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        else if(strcmp(objecto->Attribute("name"), "puerta")==0){
                            datosDinamicos[contDinamicos][0]=12; 
                            XMLElement* properties = objecto->FirstChildElement("properties");
                            if(properties!=NULL){
                              
                                XMLElement* property = properties->FirstChildElement("property");
                                while(property!=NULL){
                                    if(strcmp(property->Attribute("name"), "tipo")==0){
                                        property->QueryIntAttribute("value", &datosDinamicos[contDinamicos][3]);
                                    }
                                    property=property->NextSiblingElement();
                                }
                            }
                        }
                        contDinamicos++;
                        objecto=objecto->NextSiblingElement();
                    }
                }
                objectGroup = objectGroup->NextSiblingElement();               
            }
        }   
    }
 }


// Se pasa por parametro el puntero que apunta a la etiqueta mapa del inicio del fichero tmx. Se obtienen obtienen los valores de los atributos necesarios con funciones de tinyxml2 y la variable capas se inicializa.
void Mapa::cargarAtributos(XMLElement* map){
    capas=0;//capas que tiene el mapa por defecto
    inicioPortal[0]=-1;
    inicioPortal[1]=-1;
    finPortal[0]=-1;
    finPortal[1]=-1;
    ayuda=0;

    // Se leen los atributos int de la etiqueta
    map->QueryIntAttribute("width", &width);
    map->QueryIntAttribute("height", &height);
    map->QueryIntAttribute("tilewidth", &tileWidth);
    map->QueryIntAttribute("tileheight", &tileHeight);
    map->FirstChildElement("tileset")->QueryIntAttribute("spacing", &spacing);
    map->FirstChildElement("tileset")->QueryIntAttribute("tilecount", &numGid);
    map->FirstChildElement("tileset")->QueryIntAttribute("columns", &tileColumns);
    
    // Direccion de la imagen para el mapa
    XMLElement* img=map->FirstChildElement("tileset")->FirstChildElement("image");
    if(img!=NULL){
        imgfile=img->Attribute("source");
    }
}

//Cuenta el número de capas del fichero pasando de una etiqueta layer a otra.
void Mapa::cargarCapas(XMLElement* map){
    XMLElement* capa=map->FirstChildElement("layer");
    while(capa){
        capas++;
        capa=capa->NextSiblingElement("layer");
    }
}

//Reserva memoria para la parte de memoria dinamica de la clase.
void Mapa::reservarMemoria(){

    //Tilemap almacena una matriz en 3D de enteros.
    tilemap=new int **[capas];
    for(int i=0;i<capas;i++){            
        tilemap[i]=new int*[height];
        for (int c = 0; c < height; c++)
        {
            tilemap[i][c]=new int[width];

            for (int k=0; k<width; k++) {
                tilemap[i][c][k] = 0;
            }
        }
    }

    // tilemapSprite almacena una matriz en 3D de punteros a sprite.
    tilemapSprite=new sf::Sprite ***[capas];
    for(int i=0;i<capas;i++){
        tilemapSprite[i]=new sf::Sprite**[height];
        for (int c = 0; c < height; c++)
        {
            tilemapSprite[i][c]=new sf::Sprite*[width];

            for (int k=0; k<width; k++) {
                tilemapSprite[i][c][k] = NULL;
            }
        }
    }
    
    //tilesetSprite almacena una vector de punteros a sprite que son todos los sprites necesarios para el mapa.
    tilesetSprite=new sf::Sprite *[numGid];
    for (int i=0; i<numGid; i++) {
        tilesetSprite[i] = NULL;
    }
    
}

/*CargarTilemap recorre el fichero tmx y almacena los valorer en una matriz de numeros. Estos valores son los que indicarán que sprite le corresponde a cada posicion*/
void Mapa::cargarTilemap(XMLElement* map){

    // Se apunta a la primera capa
    XMLElement* capa=map->FirstChildElement("layer");
    XMLElement *data;
    const char *p;
    for(int i=0;i<capas && capa != NULL;i++){
        //en data se guarda un puntero a la etiqueta data
        data=capa->FirstChildElement("data");
        if(data != NULL){
            //p es un puntero que apunta al primer caracter del contenido de data que es un "string"
            p=data->GetText();
            for (int j = 0; j < height; j++)
            {
                for (int c = 0; c < width; c++)
                {
                    //si el valor al que apunta p es uno de estos caracteres se pasa al siguiente porque estos no queremos almacenarlos
                    while(*p==','||*p=='\n'){
                        p++;
                    }
                    /*al encontrar el valor numerico se crea una variable auxiliar para almacenarlo en un vec tor de 2 posiciones porque los valores de la matriz pueden ser de dos digitos y el puntero va de uno en uno.*/
                    const char aux=*p;
                    char tmp[2];
                    tmp[0]=aux;
                    //se pasa al siguiente valor y si es un numero se coloca en el vector tambien.
                    p++;
                    if(*p!=','&&*p!='\n'){
                        tmp[1]=*p;
                        //se unen los valores del vector en un solo numero y se pasan a int para almacenarlo.
                        std::string s;
                        std::stringstream sst;
                        sst<<tmp[0]<<""<<tmp[1];
                        s=sst.str();
                        tilemap[i][j][c] = atoi(s.c_str());
                        p++;
                    }
                    else{
                        //si el siguiente valor ya era , o \n significa que el numero solo tenia un digito y el almacena en la matriz el valor de la variable auxiliar qy¡ue hemos guardado antes pasado a int.
                        tilemap[i][j][c] = aux-'0';
                    }
                }
            }
        }
        //se pasa a la siguiente capa
        capa=capa->NextSiblingElement("layer");
    }
}

void Mapa::cargarTilesetSprites(){
    for(int i=0;i<capas;i++){
        for (int j = 0; j < height; j++)
        {
            for (int c = 0; c < width; c++)
            {
                int gid=tilemap[i][j][c]-1;
                if(gid>=0){
                    if(tilesetSprite[gid] != NULL) {
                        tilemapSprite[i][j][c]=new sf::Sprite(*(tilesetSprite[gid]->getTexture()),tilesetSprite[gid]->getTextureRect());
                        tilemapSprite[i][j][c]->setPosition(c*tileWidth,j*tileHeight);
                    }
                    else{
                        tilemapSprite[i][j][c]=NULL;
                    }
                    
                }
                else{
                    tilemapSprite[i][j][c]=NULL;
                }
            }
        }
    }
}
void Mapa::cargarSprites(){
    if (!tex.loadFromFile(imgfile)) {
            std::cerr << "Error cargando la imagen de sprites";
            exit(0);
        }
    int cont=0;
    if(tileColumns==0)
        tileColumns=1;
    int tileRows=numGid/tileColumns;
    
    int tamImgWidth=tileWidth+spacing;
    int tamImgHight=tileHeight+spacing;
    
    for(int i=0;i<tileRows;i++){
        for(int j=0;j<tileColumns&&cont<numGid;j++){
            sf::Sprite *sprite=new sf::Sprite(tex);
            //Le pongo el centroide donde corresponde
            sprite->setOrigin(0, 0);
            //Cojo el sprite que me interesa por defecto del sheet
            
            sprite->setTextureRect(sf::IntRect((j * tamImgWidth)+2, (i*tamImgHight)+2, tileWidth, tileHeight));
            

            tilesetSprite[cont]=sprite;
            cont++;
        } 
    }
}

void Mapa::render(){

    float xcam=motor->getCamaraCenter().x;
    float ycam=motor->getCamaraCenter().y;

    float minx=max((xcam-1100)/64.f,0.f);
    float miny=max((ycam-1100)/64.f,0.f);
    float maxx=min((xcam+1100)/64.f,width*1.f);
    float maxy=min((ycam+1100)/64.f,height*1.f);

    for(int i=0;i<capas;i++){
        for (int j = miny; j < maxy; j++)
        {
            for (int c = minx; c < maxx; c++)
            {
                if(tilemapSprite[i][j][c]!=NULL){
                    motor->ventanaDibuja(*tilemapSprite[i][j][c]);
                }
            }
        }
    }
}

//Obtener posicion inicial del personaje
void Mapa::inicioNivel(XMLElement* map){
    if(map!=NULL){
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        while(objectGroup!=NULL){
            if(strcmp(objectGroup->Attribute("name"), "personaje")==0){
                XMLElement* objecto = objectGroup->FirstChildElement("object");
                while(objecto){
                    if(strcmp(objecto->Attribute("name"), "inicio")==0){
                        objecto->QueryIntAttribute("x", &initPersonaje[0]);
                        objecto->QueryIntAttribute("y", &initPersonaje[1]);                        
                    }
                    else if(strcmp(objecto->Attribute("name"), "ayuda")==0){
                        ayuda++;
                        objecto->QueryIntAttribute("x", &initAyuda[0]);
                        objecto->QueryIntAttribute("y", &initAyuda[1]);
                    }
                    else if(strcmp(objecto->Attribute("name"), "ayuda2")==0){
                        ayuda++;
                        objecto->QueryIntAttribute("x", &initAyuda2[0]);
                        objecto->QueryIntAttribute("y", &initAyuda2[1]);
                    }
                    objecto = objecto->NextSiblingElement("object");
                    
                }
            }
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
        }
    }
}

//Metodo que lee los datos de los objetos que estan dentro del grupo de los estaticos en el tmx del mapa
void Mapa::getEstaticoMapa(XMLElement* map){
    contEstaticos=0;


    if(map!=NULL){
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        if(objectGroup!=NULL){
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
                if(objectGroup!=NULL){
                    XMLElement* objecto = objectGroup->FirstChildElement("object");
                    while(objecto){
                        if(strcmp(objecto->Attribute("name"), "finPortal")!=0)
                            contEstaticos++;
                        objecto = objecto->NextSiblingElement("object");
                    }
                }
        }
    }

    datosEstaticos = new int*[contEstaticos];
    for(int i=0;i<contEstaticos;i++){
        datosEstaticos[i]=new int[5];
    }

    contEstaticos=0;
    if(map!=NULL){
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        if(objectGroup!=NULL){
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
                if(objectGroup!=NULL){
                    XMLElement* objecto = objectGroup->FirstChildElement("object");
                    while(objecto){
                        if(strcmp(objecto->Attribute("name"), "plataforma")==0){
                            datosEstaticos[contEstaticos][0]=1; //es plataforma
                            objecto->QueryIntAttribute("width", &datosEstaticos[contEstaticos][3]);
                            objecto->QueryIntAttribute("height", &datosEstaticos[contEstaticos][4]);
                        }
                        else if(strcmp(objecto->Attribute("name"), "suelo")==0){
                            datosEstaticos[contEstaticos][0]=2; //es suelo
                            XMLElement* poligonos = objecto->FirstChildElement("polyline");
                            const char* p = poligonos->Attribute("points");
                            while(*p!=' '){
                                p++;
                            }
                            vector<char> coord;
                            p++;
                            while(*p!=','){
                                coord.push_back(*p);
                                p++;
                            }
                            stringstream sst;
                            string s;
                            for(unsigned int i=0;i<coord.size();i++){
                                if(i==coord.size()-1){
                                    sst<<coord[i];
                                }
                                else{
                                    sst<<coord[i]<<"";
                                }
                            }
                            s=sst.str();
                            datosEstaticos[contEstaticos][3] = atoi(s.c_str());
                            datosEstaticos[contEstaticos][4] = 0;

                        }
                        else if(strcmp(objecto->Attribute("name"), "fin")==0){
                            datosEstaticos[contEstaticos][0]=3; //es fin
                            //Cogemos datos del primer numero
                            XMLElement* poligonos = objecto->FirstChildElement("polygon"); //Cogemos la linea de poligonos
                            const char* p = poligonos->Attribute("points"); //Accedemos a los puntos del triangulo
                            while(*p!=' '){ //Nos movemos hasta el primer espacio para saltarnos los 0,0
                                p++;
                            }
                            vector<char> coord; //Hacemos uso de un vector dinamico para almacenar el tamaño del numero sin saberlo previamente
                            p++;
                            while(*p!=','){
                                coord.push_back(*p); //Metemos el contenido del puntero al texto dentro de cada posicion del vector
                                p++;
                            }
                            stringstream sst;
                            string s;
                            for(unsigned int i=0;i<coord.size();i++){ //Recorremos el vector para concatenar cada valor en un stringstream
                                if(i==coord.size()-1){
                                    sst<<coord[i];
                                }
                                else{
                                    sst<<coord[i]<<"";
                                }
                            }
                            s=sst.str();
                            datosEstaticos[contEstaticos][3] = atoi(s.c_str()); //Pasamos el valor a entero y lo metemos dentro de la posicion de la matriz que corresponde

                            //Aqui se repite todo para obtener el segundo numero
                            vector<char> coord2;
                            p++;
                            while(*p!=' '){
                                coord2.push_back(*p);
                                p++;
                            }
                            stringstream sst2;
                            string s2;
                            for(unsigned int i=0;i<coord2.size();i++){
                                if(i==coord2.size()-1){
                                    sst2<<coord2[i];
                                }
                                else{
                                    sst2<<coord2[i]<<"";
                                }
                            }
                            s2=sst2.str();
                            datosEstaticos[contEstaticos][4] = atoi(s2.c_str());

                        }
                        else if(strcmp(objecto->Attribute("name"), "pincho")==0){
                            datosEstaticos[contEstaticos][0]=4; //es pincho
                            objecto->QueryIntAttribute("width", &datosEstaticos[contEstaticos][3]);
                            objecto->QueryIntAttribute("height", &datosEstaticos[contEstaticos][4]);
                        }
                        else if(strcmp(objecto->Attribute("name"), "verde")==0){
                            datosEstaticos[contEstaticos][0]=5; //verde
                            objecto->QueryIntAttribute("width", &datosEstaticos[contEstaticos][3]);
                            objecto->QueryIntAttribute("height", &datosEstaticos[contEstaticos][4]);
                        }
                        else if(strcmp(objecto->Attribute("name"), "portal1")==0){
                            datosEstaticos[contEstaticos][0]=6; //portal
                            objecto->QueryIntAttribute("width", &datosEstaticos[contEstaticos][3]);
                            objecto->QueryIntAttribute("height", &datosEstaticos[contEstaticos][4]);
                            portal=true;

                        }
                        else if(strcmp(objecto->Attribute("name"), "portal2")==0){
                            datosEstaticos[contEstaticos][0]=7; //portal
                            objecto->QueryIntAttribute("width", &datosEstaticos[contEstaticos][3]);
                            objecto->QueryIntAttribute("height", &datosEstaticos[contEstaticos][4]);
                        }
                        else
                            datosEstaticos[contEstaticos][0]=8; //otros

                        
                        if(strcmp(objecto->Attribute("name"), "inicioPortal")==0){
                            objecto->QueryIntAttribute("x", &inicioPortal[0]);
                            objecto->QueryIntAttribute("y", &inicioPortal[1]);
                        }
                        else if(strcmp(objecto->Attribute("name"), "finPortal")==0){
                            objecto->QueryIntAttribute("x", &finPortal[0]);
                            objecto->QueryIntAttribute("y", &finPortal[1]);
                        }
                        else{
                            objecto->QueryIntAttribute("x", &datosEstaticos[contEstaticos][1]);
                            objecto->QueryIntAttribute("y", &datosEstaticos[contEstaticos][2]);
                            contEstaticos++;

                        }
                        objecto = objecto->NextSiblingElement("object");
                    }
            }
        }
    }
}

void Mapa::getDatosMundo2(XMLElement *map){
    contMundo2=0;

    if(map!=NULL){
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        while(objectGroup!=NULL){
            if(strcmp(objectGroup->Attribute("name"), "mundo2")==0){
                XMLElement* objecto = objectGroup->FirstChildElement("object");
                while(objecto){
                    contMundo2++;
                    objecto = objecto->NextSiblingElement("object");
                    
                }
            }
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
        }
    }

    datosMundo2 = new int*[contMundo2];
    for(int i=0;i<contMundo2;i++){
        datosMundo2[i]=new int[2];
    }

    contMundo2=0;
    if(map!=NULL){
        XMLElement* objectGroup = map->FirstChildElement("objectgroup");
        while(objectGroup!=NULL){
            if(strcmp(objectGroup->Attribute("name"), "mundo2")==0){
                XMLElement* objecto = objectGroup->FirstChildElement("object");
                while(objecto){
                    objecto->QueryIntAttribute("x", &datosMundo2[contMundo2][0]);
                    objecto->QueryIntAttribute("y", &datosMundo2[contMundo2][1]);                        
                    contMundo2++;
                    objecto = objecto->NextSiblingElement("object");
                    
                }
            }
            objectGroup = objectGroup->NextSiblingElement("objectgroup");
        }
    }
}