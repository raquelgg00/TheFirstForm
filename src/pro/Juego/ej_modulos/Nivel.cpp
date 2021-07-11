#include "Nivel.h"

// Singleton
Nivel* Nivel::pinstance = 0;
Nivel* Nivel::Instance(){
    if(pinstance == 0){
        pinstance = new Nivel();
    }
    return pinstance;
}

// Constructor
Nivel::Nivel()
{
    //empieza en el nivel 0, sin entidades y sin completar
    numNivel=0; 
    completado=false;
    contEntidades=0;
    contMundo2=0;
    portal=false;
    dentro_portal=false;
    resetea_gravedad = false;
    dir_gravedad=0;

    //carga el fichero de la lista de niveles solo cuando se crea
    listaMapas.LoadFile("mapas/lista_mapas.xml");  
    cargarMapa();
    
    player=Player::Instance();

    //colocamos player
    if(mapa != NULL) {
        
        player->setPosition(mapa->getInicioPersonaje()[0],mapa->getInicioPersonaje()[1]);
        player->getPosicion()->setPositionXY(mapa->getInicioPersonaje()[0],mapa->getInicioPersonaje()[1]);

        //si hay ayuda
        if(mapa->getAyuda()){
            
            ayuda=new Ayuda(numNivel,mapa->getInicioAyuda()[0],mapa->getInicioAyuda()[1]);
        }
        else
            ayuda=NULL;
   
        //si hay portal
        int hab_actual = Guardar::Instance()->getHabilidades();
        if((hab_actual==1&&numNivel==2) || (hab_actual==2&&numNivel==5) || (hab_actual==3&&numNivel==7) ||
            (hab_actual==4&&numNivel==9) || (hab_actual==5&&numNivel==13)){
                portal = false;
        }
        else{
            if(mapa->getPortal()){
                portal=true;
                inicioPortal[0]=mapa->getInicioPortal()[0];
                inicioPortal[1]=mapa->getInicioPortal()[1];
                finPortal[0]=mapa->getFinPortal()[0];
                finPortal[1]=mapa->getFinPortal()[1];
                
            }
            else
                portal=false;
        }

        //cargamos entidades
        entidades=NULL;
        cargarEntidades();

        cargarMundo2();
    }
}


// Destructor
Nivel::~Nivel(){
    if(mapa != NULL){
        delete mapa;
        mapa=NULL;
    }
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }
    int i =0;
    while(i<contEntidades){

        if (entidades[i] !=NULL){
            delete entidades[i];
            entidades[i]=NULL;
        }
        i++;
    }
    if(entidades!=NULL){
        delete[] entidades;
        entidades =NULL;
    }
    if(ayuda!=NULL){
        delete ayuda;
        ayuda=NULL;
    }

    for(int i=0;i<contMundo2;i++){
        if(mundo2[i]!=NULL){
            delete mundo2[i];
            mundo2[i]=NULL;
        }
    }
    if(mundo2!=NULL){
        delete[] mundo2;
        mundo2=NULL;
    }
}

// Al cambiar de nivel se debe hacer un set para actualizar el nivel en el que se encuentra y que pueda cambiar el nuevo nivel con el mapa y entidades que debe tener.
void Nivel::cambiarNivel(int num){
    numNivel=num;
    completado=false;
    dentro_portal=false;
    cargarMapa();
    cargarEntidades();
    player->setHabilidad(0);
    player->setArista(false);
    player->setDirGravedad(0);
    player->set_vel_plataforma(0);
    if(numNivel<6){//mundo1
        player->setFormaReset(0);
    }else if(numNivel>10){//mundo3
        player->setFormaReset(2);
    } else{//mundo2
        player->setFormaReset(1);
        
    }
    cargarMundo2();
    
    int hab_actual = Guardar::Instance()->getHabilidades();
    
    
        if(mapa!=NULL){
            player->setPosition(mapa->getInicioPersonaje()[0], mapa->getInicioPersonaje()[1]);

            //si hay ayuda
            if(ayuda!=NULL){
                delete ayuda;
                ayuda=NULL;
            }

            if(mapa->getAyuda()){
                
                ayuda=new Ayuda(numNivel,mapa->getInicioAyuda()[0],mapa->getInicioAyuda()[1]);
            }
            else
                ayuda=NULL;

            if((hab_actual>=1&&numNivel==2) || (hab_actual>=2&&numNivel==5) || (hab_actual>=3&&numNivel==7) ||
            (hab_actual>=4&&numNivel==9) || (hab_actual>=5&&numNivel==13)){
                portal = false;
            }
            else{
                if(mapa->getPortal()){
                    
                    portal=true;
                    inicioPortal[0]=mapa->getInicioPortal()[0];
                    inicioPortal[1]=mapa->getInicioPortal()[1];
                    finPortal[0]=mapa->getFinPortal()[0];
                    finPortal[1]=mapa->getFinPortal()[1];
                }
                else{
                    portal=false;
                }
            }
        }
}


// Se guarda en la variable mapa del nivel el puntero a la instancia de mapa que contiene los datos del nivel actual
void Nivel::cargarMapa(){
    //eliminamos memoria del mapa si la hay
    if(mapa!=NULL){
        delete mapa;
        mapa=NULL;
    }
    
    //buscamos el nombre del fichero de mapa que tenemos que abrir desde lista_mapas.xml
    XMLElement* niveles=(listaMapas.FirstChildElement("niveles"));
    if(niveles != NULL){

        XMLElement* nivel = niveles->FirstChildElement("nivel");
        if(nivel != NULL){

            int id=-1;

            // Iteramos hasta encontrar el nivel actual en el XML o hasta el final del fichero XML (cuando nivel == NULL)
            while(id!=numNivel&&nivel){

                // guardamos en la variable id el atributo idn de la etiqueta nivel del XML
                nivel->QueryIntAttribute("idn", &id); 

                if(id == numNivel){
                    break;
                }
                nivel=nivel->NextSiblingElement("nivel");
            }
            if(id!=-1){
                //creamos el nuevo mapa
                const char *ficheroMapa=nivel->Attribute("source");                    
                mapa = new Mapa(ficheroMapa);
            }
        }
    }
}

void Nivel::cargarMundo2(){
    for(int i=0;i<contMundo2;i++){
        if(mundo2[i]!=NULL){
            delete mundo2[i];
            mundo2[i]=NULL;
        }
    }
    if(mundo2!=NULL){
        delete[] mundo2;
        mundo2=NULL;
    }

    if(mapa!=NULL){
        contMundo2=mapa->getContMundo2();
        if(contMundo2>0){
            mundo2=new ObjetoMundo2*[contMundo2];

            int **datosMundo2=mapa->getDatosMundo2();
            for(int i=0;i<contMundo2;i++){
                mundo2[i]=new ObjetoMundo2(datosMundo2[i][0],datosMundo2[i][1]);
            }
        }
        
    }
}

void Nivel::cargarEntidades(){
    //eliminamos memoria de las entidades si hay
    
    int i =0;
    while(i<contEntidades){

        if(entidades[i] !=NULL){
            delete entidades[i];
            entidades[i]=NULL;
        }
        i++;
    }
    if(entidades!=NULL){
        delete[] entidades;
        entidades =NULL;
     }

    if(mapa!=NULL){
        // Reservamos memoria para las entidades
        contEntidades=mapa->getContDinamicos();

        entidades = new Entidad*[contEntidades];

        // Obtenemos las posiciones X de las entidades
        int **datosDinamicos = mapa->getDatosDinamicos();
        
        i = 0;
        while(i < contEntidades){

            int x_ini = datosDinamicos[i][1];
            int y_ini = datosDinamicos[i][2];

            Entidad *plat;
            if(datosDinamicos[i][0]==1){ // Es una PLATAFORMA
    
                
                int x_fin = datosDinamicos[i][4];
                int y_fin = datosDinamicos[i][5];
                int en_movimiento = datosDinamicos[i][3];

                // Comprobamos hacia donde se debe mover la plataforma (establecemos el mov_vertical y horizontal) 
                int mov_horizontal = 0;
                if(x_ini<x_fin) mov_horizontal = 1;
                else if (x_ini>x_fin) mov_horizontal = -1;

                int mov_vertical = 0;
                if(y_ini<y_fin) mov_vertical = 1;
                else if (y_ini>y_fin) mov_vertical = -1;

                plat = (Entidad*)new Plataforma(i, x_ini, y_ini, x_fin, y_fin, mov_horizontal, mov_vertical, en_movimiento);

            }
            else if(datosDinamicos[i][0]==2){ // Es una BOLITA

                //int x_ini = datosDinamicos[i][1];
                //int y_ini = datosDinamicos[i][2];
                int x_fin = datosDinamicos[i][4];
                int y_fin = datosDinamicos[i][5];
                int tipo = datosDinamicos[i][3];

                int distancia = -1;
                if(tipo==3) distancia = datosDinamicos[i][6];

                if(tipo == 1 || tipo==2){
                    x_fin = -1;
                    y_fin = -1;
                }
                plat = (Entidad*)new Bolita(x_ini, y_ini, x_fin, y_fin, tipo, distancia);

            }
            else if(datosDinamicos[i][0]==3){ // Es una PARED
                int pinchos = datosDinamicos[i][3];
                plat = (Entidad*)new Pared(x_ini, y_ini, pinchos);
            }
            else if(datosDinamicos[i][0]==4){ // Es un CANION
                plat = (Entidad*)new Canion(x_ini, y_ini);

            }
            else if(datosDinamicos[i][0]==6){ //Es un SECRETO
                plat = (Entidad*)new Secreto(x_ini,y_ini,datosDinamicos[i][1]);
            }
            else if(datosDinamicos[i][0]==7){ //Es una arista
                plat = (Entidad*)new Arista(x_ini,y_ini);
            }
            else if(datosDinamicos[i][0]==8){
                plat = (Entidad*)new Cubo(x_ini, y_ini, datosDinamicos[i][3]);

            }
            else if(datosDinamicos[i][0]==9){
                plat = (Entidad*)new Sensor(x_ini, y_ini);
            }
            else if(datosDinamicos[i][0]==10){
                plat = (Entidad*)new Molino(x_ini, y_ini, datosDinamicos[i][3]);
            }
            else if(datosDinamicos[i][0]==11){
                plat = (Entidad*)new CampoGravedad(x_ini, y_ini, datosDinamicos[i][3]);
            }
            else if(datosDinamicos[i][0]==12){
                plat = (Entidad*)new Puerta(x_ini, y_ini, datosDinamicos[i][3]);
            }
            else
                plat=NULL;
            
            entidades[i] = plat;
            //entidades[i]->setPosition(datosDinamicos[i][1], datosDinamicos[i][2]);
            i++;
        }
    }
    for(int i=0;i<contEntidades;i++){
        if(Puerta* p=dynamic_cast<Puerta *>(entidades[i])){
            for(int j=0;j<contEntidades;j++){
                if(Sensor* p2=dynamic_cast<Sensor *>(entidades[j])){
       
                    p->agregarSensor(p2);
                }
            }
            break;
        }
    }
}

void Nivel::render(float tick){
    if(mapa != NULL){
        mapa->render();
        if(ayuda!=NULL){
            ayuda->render();
        }
        int i =0;
        int contador = mapa->getContDinamicos();
        while(i<contador){
            if(entidades[i] != NULL){
                entidades[i]->render(tick);
            }
            i++;
        }
        for(int i=0;i<contMundo2;i++){
            if(mundo2[i]!=NULL){
                mundo2[i]->render();
            }
        }
        
    }
}

void Nivel::update(int dirGravedad){

    if(player->getMuere()){
        morision();
        player->setMuere(false);
    }
    else{
        colisionMapaPersonaje(dirGravedad);
        player->reseteaColisionesMapa();
        if(mapa != NULL) {
            int i =0;
            
            int contador = mapa->getContDinamicos();
        
            while(i<contador){    
                if(entidades[i] != NULL){
                    
                    if(Bolita* b=dynamic_cast<Bolita *>(entidades[i])){
                        colisionMapaEntidad(entidades[i]);

                        //Vemos colisiones de las bolas con la pared
                        for(int j =0;j<contador;j++){
                            if(Pared* p=dynamic_cast<Pared *>(entidades[j])){
                                if(b!=NULL&&b->getSprite()&&p!=NULL&&p->getSprite()){
                                    if(b->getSprite()->getBounds("global").intersects(p->getSprite()->getBounds("global"))){
                                        float b_w = b->getSprite()->getBounds("global").width;
                                        float b_h = b->getSprite()->getBounds("global").height;
                                        float p_w = p->getSprite()->getBounds("global").width;
                                        float p_h = p->getSprite()->getBounds("global").height;

                                        if(Motor::Instance()->colisionIzq(b->getX(),b->getY(),b_w,b_h, 
                                            p->getX()+p_w/2.f, p->getY()+p_h/2.f,p_w, p_h, false))
                                        {
                                            b->setPosition(p->getX()-b_w-1, b->getY());
                                            b->setColisionRight(true);
                                        }
                                        else if(Motor::Instance()->colisionDerecha(b->getX(),b->getY(),b_w,b_h, 
                                            p->getX()+p_w/2.f, p->getY()+p_h/2.f,p_w, p_h, false))
                                        {
                                            b->setPosition(p->getX()+p_w+1, b->getY());
                                            b->setColisionLeft(true);
                                        }
                                    }
                                } 
                            }
                    
                        }
                    }
                    else if(Cubo* c=dynamic_cast<Cubo *>(entidades[i])){

                        c->setColisionCuboCubo(false);
                        c->setColisionCuboPlataforma(false);
                        c->setVelocidadXPlataforma(0.f);
                        colisionMapaEntidad(entidades[i]);
                        bool col[4] = {false,false,false,false};
                        c->setColisionesDinam(col);
                        
                        Motor *motor = Motor::Instance();

                        // Datos del cubo al que yo muevo
                        float width2 = c->getWidth();
                        float height2 = c->getHeight();
                        float x2 = c->getX() + (width2/2.f);
                        float y2 = c->getY() + (height2/2.f);

                        for(int j =0;j<contador;j++){

                            // COlision CUbo-Cubo
                            if(Cubo* cubito=dynamic_cast<Cubo *>(entidades[j])){ // cubo actual (i) todos los demas cubos (j)
                                // Si el cubo choca con otro cubo entonces no lo muevo
                                if(c != cubito){
                                    if(c->getSprite()->getBounds("global").intersects(cubito->getSprite()->getBounds("global"))){

                                        // Datos del cubo con quien colisiona
                                        float x = cubito->getX();
                                        float y = cubito->getY();
                                        float width = cubito->getWidth();
                                        float height = cubito->getHeight();
                                        
                                        if (motor->colisionDerecha(x, y, width, height, x2, y2, width2, height2, false)){
                                            c->setPosition(c->getPositionX()-3, c->getPositionY());
                                            //cubito->setPosition(cubito->getPositionX()+1, cubito->getPositionY());
                                            c->setColisionCuboCubo(true);
                                            c->setColisionesDinamRight(true);
                                        }
                                        if(motor->colisionIzq(x, y, width, height, x2, y2, width2, height2, false)) {
                                            c->setPosition(c->getPositionX()+3, c->getPositionY());
                                            //cubito->setPosition(cubito->getPositionX()-1, cubito->getPositionY());
                                            c->setColisionCuboCubo(true);
                                            c->setColisionesDinamLeft(true);
                                        }
                                    }
                                }
                            }

                            // Colision Cubo - Plataforma Movil
                            else if(Plataforma* plat=dynamic_cast<Plataforma *>(entidades[j])){ //
                            
                                // Datos del cubo con quien colisiona
                                float x = plat->getX();
                                float y = plat->getY();
                                float width = plat->getWidth();
                                float height = plat->getHeight();

                                if(c->getSprite()->getBounds("global").intersects(plat->getSprite()->getBounds("global"))){
                                    if(motor->colisionAbajo(x, y, width, height, x2, y2, width2, height2, false))
                                    {
                                        c->setPosition(c->getX(), plat->getY()-height2+1);
                                        c->setColisionesDinamDown(true);
                                        c->setColisionCuboPlataforma(true);
                                        c->setVelocidadXPlataforma(plat->getVelX());
                                    }
                                    if(motor->colisionIzq(x, y, width, height, x2, y2, width2, height2, false))
                                    {
                                        //c->setPosition(plat->getX()+width-1, c->getY());
                                        c->setColisionesDinamLeft(true);
                                
                                    }
                                    if(motor->colisionDerecha(x, y, width, height, x2, y2, width2, height2, false))
                                    {
                                        //c->setPosition(plat->getX()-width2+1, c->getY());
                                        c->setColisionesDinamRight(true);
                                    }
                                    if(motor->colisionArriba(x, y, width, height, x2, y2, width2, height2, false, false))
                                    {
                                        //c->setPosition(c->getX(), plat->getY()+height-1);
                                        c->setColisionesDinamTop(true);
                                    }
                                }
                            
                            }
                            //Cubo-Pared
                            else if(Pared* p=dynamic_cast<Pared *>(entidades[j])){
                                if(c!=NULL&&c->getSprite()&&p!=NULL&&p->getSprite()!=NULL){
                                    if(c->getSprite()->getBounds("global").intersects(p->getSprite()->getBounds("global"))){
                                        float c_w = c->getSprite()->getBounds("global").width;
                                        float c_h = c->getSprite()->getBounds("global").height;
                                        float p_w = p->getSprite()->getBounds("global").width;
                                        float p_h = p->getSprite()->getBounds("global").height;

                                        if(motor->colisionIzq(p->getX(), p->getY(),p_w, p_h, c->getX()+c_w/2.f,c->getY()+c_h/2.f,c_w,c_h, false))
                                        {
                                            c->setPosition(p->getX()+p_w-1, c->getY());
                                            c->setColisionesDinamLeft(true);
                                    
                                        }
                                        if(motor->colisionDerecha(p->getX(), p->getY(),p_w, p_h, c->getX()+c_w/2.f,c->getY()+c_h/2.f,c_w,c_h, false))
                                        {
                                            c->setPosition(p->getX()-c_w+1, c->getY());
                                            c->setColisionesDinamRight(true);
                                        }
                                        if(motor->colisionAbajo(p->getX(), p->getY(),p_w, p_h, c->getX()+c_w/2.f,c->getY()+c_h/2.f,c_w,c_h, false))
                                        {
                                            c->setPosition(c->getX(), p->getY()-c_h-8);
                                            c->setColisionesDinamDown(true);
                                        }
                                        if(motor->colisionArriba(p->getX(), p->getY(),p_w, p_h, c->getX()+c_w/2.f,c->getY()+c_h/2.f,c_w,c_h, false, false))
                                        {
                                            c->setPosition(c->getX(), p->getY()+p_h-1);
                                            c->setColisionesDinamTop(true);
                                        }
                                    }
                                } 
                            }
                        }
                    
                    }
                    else if(dynamic_cast<Canion *>(entidades[i])){
                        colisionMapaEntidad(entidades[i]);
                    }
                    else if(Sensor* s=dynamic_cast<Sensor *>(entidades[i])){
                        bool hay_cubo = false;
                        for(int j =0;j<contador;j++){

                            //colision cubo sensor
                            if(Cubo* cubito=dynamic_cast<Cubo *>(entidades[j])){
                                hay_cubo = true;
                                if(s->getSprite()->getBounds("global").intersects(cubito->getSprite()->getBounds("global")) || s->getSprite()->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                                    s->setPresionado(true);
                                    break;
                                }
                                else{
                                    s->setPresionado(false);
                                }
                            }
                        }
                        if(!hay_cubo && s->getSprite()->getBounds("global").intersects(player->getSprite()->getBounds("global"))){
                            s->setPresionado(true);
                        }
                    }
                    entidades[i]->updatemover();
                    entidades[i]->onCollisionPlayer(dirGravedad);
                }
                i++;
            }

            if(mundo2!=NULL){
                for(int i=0;i<contMundo2;i++){
                    if(mundo2[i]!=NULL)
                        mundo2[i]->onCollisionPlayer();
                }
            }
            
        }
    }
}

void Nivel::colisionMapaEntidad(Entidad* ent){
    if(mapa != NULL) {
        int ** matriz=mapa->getDatosEstaticos();//recuperamos daatos del mapa
    
        // Colisiones de la Bala (solo con intersects)
        if(Canion* can=dynamic_cast<Canion *>(ent)){
            int cont=mapa->getContEstaticos();
            //con el mapa
            for(int i=0;i<cont;i++){
                int x=matriz[i][1];
                int y=matriz[i][2];
                if(matriz[i][0]<6){ // hasta el 5 son colisiones

                    int width=matriz[i][3];
                    int height=matriz[i][4];

                    sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);
                    if(can->getBala()!=NULL && can->getBala()->getSprite()!=NULL){
                        if(rectangle.intersects(can->getBala()->getSprite()->getBounds("global"))){
                            can->getBala()->resetea();
                        }
                    }
                }
            }
            int cont_dinam = mapa->getContDinamicos();
            //con el cubo y plataforma
            for(int j =0;j<cont_dinam;j++){
                if(can->getBala()!=NULL && can->getBala()->getSprite()!=NULL){
                    if(Cubo* cubito=dynamic_cast<Cubo *>(entidades[j])){
                        if(cubito->getSprite()->getBounds("global").intersects(can->getBala()->getSprite()->getBounds("global"))){
                            can->getBala()->resetea();
                        }
                    }
                    else if(Plataforma* cubito=dynamic_cast<Plataforma *>(entidades[j])){
                        if(cubito->getSprite()->getBounds("global").intersects(can->getBala()->getSprite()->getBounds("global"))){
                            can->getBala()->resetea();
                        }
                    }
                }
            }
        }
        // Colisiones de las demas entidades con el Mapa por los 4 lados (Cubo, Bolita...)
        else {
            bool colisiones[4];
            colisiones[0]=getColisionTopEntidad(matriz,ent);//arriba
            colisiones[1]=getColisionDownEntidad(matriz,ent);//abajo
            colisiones[2]=getColisionRigthEntidad(matriz,ent);//derecha
            colisiones[3]=getColisionLeftEntidad(matriz,ent);//izquierda
            ent->setColisionesMapa(colisiones);
        }
    }
}

bool Nivel::getColisionDownEntidad(int **datos, Entidad *ent){

    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int heightPlayer=ent->getSprite()->getBounds("global").height;
    int widthPlayer=ent->getSprite()->getBounds("global").width;
    int xPlayer=ent->getX()+widthPlayer/2.f;
    int yPlayer=ent->getY()+heightPlayer/2.f;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        
        if(datos[i][0]<6){ // hasta el 5 son colisiones
            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(ent->getSprite()->getBounds("global"))){

                if (motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
                    ent->setPosition(xPlayer-widthPlayer/2.f, y-heightPlayer+1);
                    if(Bolita* bol=dynamic_cast<Bolita *>(ent)){
                        if(datos[i][0] == 4){
                            bol->transformarBolita(); // cambia de bolita a plataforma
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool Nivel::getColisionTopEntidad(int **datos, Entidad *ent){
    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos

    int heightPlayer=ent->getSprite()->getBounds("global").height;
    int widthPlayer=ent->getSprite()->getBounds("global").width;
    int xPlayer=ent->getX()+widthPlayer/2.f;
    int yPlayer=ent->getY()+heightPlayer/2.f;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<6){ // hasta el 5 son colisiones

            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(ent->getSprite()->getBounds("global"))){
                if (motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false, false)){
                    ent->setPosition(xPlayer-widthPlayer/2.f, y+height);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Nivel::getColisionLeftEntidad(int **datos, Entidad *ent){
    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int heightPlayer=ent->getSprite()->getBounds("global").height;
    int widthPlayer=ent->getSprite()->getBounds("global").width;
    int xPlayer=ent->getX()+widthPlayer/2.f;
    int yPlayer=ent->getY()+heightPlayer/2.f;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<6){ // hasta el 5 son colisiones

            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(ent->getSprite()->getBounds("global"))){
                
                if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
                    ent->setPosition(x+width-1, yPlayer-heightPlayer/2.f);
                    return true;
                    
                }
            }
        }
    }
    return false;
}

bool Nivel::getColisionRigthEntidad(int **datos, Entidad *ent){

    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int heightPlayer=ent->getSprite()->getBounds("global").height;
    int widthPlayer=ent->getSprite()->getBounds("global").width;
    int xPlayer=ent->getX()+widthPlayer/2.f;
    int yPlayer=ent->getY()+heightPlayer/2.f;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<6){ // hasta el 5 son colisiones

            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(ent->getSprite()->getBounds("global"))){
                if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, false)){
                    ent->setPosition(x-widthPlayer+1, yPlayer-heightPlayer/2.f);
                    return true;
                }
            }
        }
    }
    return false;
}

void Nivel::colisionMapaPersonaje(int gravedad){
    dir_gravedad=gravedad;
    if(mapa != NULL) {
        int ** matriz=mapa->getDatosEstaticos();//recuperamos daatos del mapa
        bool colisiones[4];
        if(gravedad==0){
            colisiones[0]=getColisionTop(matriz, false);//arriba
            colisiones[1]=getColisionDown(matriz, false);//abajo
            colisiones[2]=getColisionRigth(matriz, false);//derecha
            colisiones[3]=getColisionLeft(matriz, false);//izquierda
        }
        else if(gravedad == 1){
            
            colisiones[0]=getColisionRigth(matriz,true);//derecha
            colisiones[1]=getColisionLeft(matriz, true);//izquierda
            colisiones[2]=getColisionDown(matriz, true);//arriba
            colisiones[3]=getColisionTop(matriz, true);//abajo            
            
        }
        else if(gravedad == 2){
            
            colisiones[0]=getColisionDown(matriz,false);//derecha
            colisiones[1]=getColisionTop(matriz, false);//izquierda
            colisiones[2]=getColisionLeft(matriz, false);//arriba
            colisiones[3]=getColisionRigth(matriz, false);//abajo            
            
        }
        else if(gravedad == 3){
            
            colisiones[0]=getColisionLeft(matriz, true);//izquierda
            colisiones[1]=getColisionRigth(matriz, true);//derecha
            colisiones[2]=getColisionTop(matriz, true);//arriba
            colisiones[3]=getColisionDown(matriz, true);//abajo  
        }
        
        player->setColisionesMapa(colisiones);
    }
   
}

bool Nivel::getColisionDown(int **datos, bool cambia_margen){

    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height;
    int widthPlayer=player->getSprite()->getBounds("global").width;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        
        if(datos[i][0]<8){ // hasta el 7 son rectangulos
            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(player->getSprite()->getBounds("global"))){
                if (motor->colisionAbajo(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, cambia_margen)){
                    if(datos[i][0]==4){
                        morision();
                        break;
                    }
                    else if(datos[i][0]==6&&portal==false){ 
                        //return false;
                    }
                    else if(datos[i][0]==6&&portal==true){
                        player->setPosition(inicioPortal[0],inicioPortal[1]);
                        dentro_portal=true;

                        if(numNivel == 2) 
                            Guardar::Instance()->setHabilidadesAtrib(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidadesAtrib(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidadesAtrib(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidadesAtrib(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidadesAtrib(5);
                        return true;

                    }
                    else if(datos[i][0]==7&&portal==true){
                        player->setPosition(finPortal[0],finPortal[1]);
                        dentro_portal=false;
                        portal=false;
                         if(numNivel == 2) 
                            Guardar::Instance()->setHabilidades(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidades(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidades(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidades(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidades(5);
                        return true;

                    }
                    else{
                        if(datos[i][0]==5){//plataforma verde
                            //en contacto con plataforma verde
                            if(dir_gravedad==0)
                                player->setContactoVerdeDown(true);
                            else if(dir_gravedad==1)
                                player->setContactoVerdeDer(true);
                            else if(dir_gravedad==3)
                                 player->setContactoVerdeIzq(true);
                        }
                        
                        if(datos[i][0]==3){//fin
                            if(evolucionBuena() && dir_gravedad==0){
                                completado=true;
                                motor->getSonidoNivelCompleto()->Play();
                            }
                        }
                        else{
                            player->setPosition(xPlayer, y-heightPlayer/2.f+1);
                            return true;
                        }

                    }
                }
            }
        }
    }
    //en contacto con plataforma verde
    if(dir_gravedad==0)
        player->setContactoVerdeDown(false);
    else if(dir_gravedad==1)
        player->setContactoVerdeDer(false);
    else if(dir_gravedad==3)
        player->setContactoVerdeIzq(false);
        
    return false;
}

bool Nivel::getColisionTop(int **datos, bool cambia_margen){
    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos

    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<8){ // hasta el 7 son rectangulos
            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(player->getSprite()->getBounds("global"))){
                if(datos[i][0]==4){
                    if(motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,true, cambia_margen)){
                        morision();
                        break;
                    }
                }
                else if (motor->colisionArriba(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer,false, cambia_margen)){
                    if(datos[i][0]==6&&portal==true){
                        player->setPosition(inicioPortal[0],inicioPortal[1]);
                        dentro_portal=true;
                        if(numNivel == 2) 
                            Guardar::Instance()->setHabilidadesAtrib(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidadesAtrib(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidadesAtrib(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidadesAtrib(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidadesAtrib(5);
                        return true;

                    }
                    else if(datos[i][0]==6&&portal==false){
                        //return false;
                    }
                    else if(datos[i][0]==7&&portal==true){
                        dentro_portal=false;
                        player->setPosition(finPortal[0],finPortal[1]);
                         if(numNivel == 2) 
                            Guardar::Instance()->setHabilidades(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidades(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidades(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidades(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidades(5);
                        portal=false;
                        return true;

                    }
                    else{
                        if(datos[i][0]==5){//plataforma verde
                            //en contacto con plataforma verde
                            if(dir_gravedad==2)
                                player->setContactoVerdeDown(true);
                            else if(dir_gravedad==3)
                                player->setContactoVerdeDer(true);
                            else if(dir_gravedad==1)
                                player->setContactoVerdeIzq(true);
                        }
                        if(datos[i][0]==3){//fin
                            if(evolucionBuena() && dir_gravedad==0){
                                completado=true;
                                motor->getSonidoNivelCompleto()->Play();
                            }
                        }
                        else{
                            player->setPosition(xPlayer, y+height+heightPlayer/2.f-1);
                            //player->setVelocidad_y(0);
                            return true;
                        }

                    }
                }
            }
        }
    }
    if(dir_gravedad==2)
        player->setContactoVerdeDown(false);
    else if(dir_gravedad==3)
        player->setContactoVerdeDer(false);
    else if(dir_gravedad==1)
        player->setContactoVerdeIzq(false);

    return false;
}

bool Nivel::getColisionLeft(int **datos, bool cambia_margen){
    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int heightPlayer=player->getSprite()->getBounds("global").height * player->getSprite()->getScale().y;
    int widthPlayer=player->getSprite()->getBounds("global").width * player->getSprite()->getScale().x;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<8){ // hasta el 7 son rectangulos
            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(player->getSprite()->getBounds("global"))){
                
                if(motor->colisionIzq(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, cambia_margen)){
                    if(datos[i][0]==4){
                        morision();
                        break;
                    }
                    else if(datos[i][0]==6&&portal==false){
                        //return false;
                    }
                    else if(datos[i][0]==6&&portal==true){
                         dentro_portal=true;
                        player->setPosition(inicioPortal[0],inicioPortal[1]);
                        if(numNivel == 2) 
                            Guardar::Instance()->setHabilidadesAtrib(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidadesAtrib(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidadesAtrib(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidadesAtrib(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidadesAtrib(5);
                        return true;

                    }
                    else if(datos[i][0]==7&&portal==true){
                        player->setPosition(finPortal[0],finPortal[1]);
                         dentro_portal=false;
                         if(numNivel == 2) 
                            Guardar::Instance()->setHabilidades(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidades(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidades(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidades(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidades(5);
                        portal=false;
                        return true;

                        
                    }
                    else {
                        if(datos[i][0]==5){
                            //en contacto con plataforma verde
                            if(dir_gravedad==0)
                                player->setContactoVerdeIzq(true);
                            else if(dir_gravedad==1){
                                player->setContactoVerdeDown(true);
                            }
                            else if(dir_gravedad==2)
                                player->setContactoVerdeDer(true);
                        }
                        
                        if(datos[i][0]==3){//fin
                            if(evolucionBuena() && dir_gravedad==0){
                                completado=true;
                                motor->getSonidoNivelCompleto()->Play();
                            }
                        }
                        else{
                            player->setPosition(x+width+widthPlayer/2.f-1, yPlayer);
                            return true;
                        }
                        
                    }   
                }
            }
        }
    }

    //en contacto con plataforma verde
    if(dir_gravedad==0)
        player->setContactoVerdeIzq(false);
    else if(dir_gravedad==1)
        player->setContactoVerdeDown(false);
    else if(dir_gravedad==2)
        player->setContactoVerdeDer(false);

    return false;
}

bool Nivel::getColisionRigth(int **datos, bool cambia_margen){

    int cont=mapa->getContEstaticos();//recuperamos cantidad de objetos estaticos
    int xPlayer=player->getX();
    int yPlayer=player->getY();
    int widthPlayer=player->getSprite()->getBounds("global").width;
    int heightPlayer=player->getSprite()->getBounds("global").height;

    for(int i=0;i<cont;i++){
        int x=datos[i][1];
        int y=datos[i][2];
        if(datos[i][0]<8){ // hasta el 7 son rectangulos
            int width=datos[i][3];
            int height=datos[i][4];

            Motor *motor = Motor::Instance();
            sf::FloatRect rectangle = sf::FloatRect(x, y, width, height);

            if(rectangle.intersects(player->getSprite()->getBounds("global"))){
                if(motor->colisionDerecha(x, y, width, height, xPlayer, yPlayer, widthPlayer, heightPlayer, cambia_margen)){
                    if(datos[i][0]==4){
                        morision();
                        break;  
                    }
                    else if(datos[i][0]==6&&portal==false){
                        //return false;
                    }
                    else if(datos[i][0]==6&&portal==true){
                        player->setPosition(inicioPortal[0],inicioPortal[1]);
                         dentro_portal=true;
                        if(numNivel == 2) 
                            Guardar::Instance()->setHabilidadesAtrib(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidadesAtrib(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidadesAtrib(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidadesAtrib(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidadesAtrib(5);
                        return true;

                        
                    }
                    else if(datos[i][0]==7&&portal==true){
                        player->setPosition(finPortal[0],finPortal[1]);
                         dentro_portal=false;
                        portal=false;
                        if(numNivel == 2) 
                            Guardar::Instance()->setHabilidades(1);
                        else if(numNivel == 5)
                            Guardar::Instance()->setHabilidades(2);
                        else if(numNivel == 7)
                            Guardar::Instance()->setHabilidades(3);
                        else if(numNivel == 9)
                            Guardar::Instance()->setHabilidades(4);
                        else if(numNivel == 13)
                            Guardar::Instance()->setHabilidades(5);
                        return true;

                       
                    }
                    else {    
                        if(datos[i][0]==5){
                            //en contacto con plataforma verde
                            if(dir_gravedad==0)
                                player->setContactoVerdeDer(true);
                            else if(dir_gravedad==3)
                                player->setContactoVerdeDown(true);
                            else if(dir_gravedad==2)
                                player->setContactoVerdeIzq(true);
                        }
                        
                        if(datos[i][0]==3){//fin
                            if(evolucionBuena() && dir_gravedad==0){
                                completado=true;
                                motor->getSonidoNivelCompleto()->Play();
                            }
                        }
                        else{
                            player->setPosition(x-widthPlayer/2.f+1, yPlayer);
                            return true;
                        }
                    }
                }
            }
        }
    }
    //en contacto con plataforma verde
    if(dir_gravedad==0)
        player->setContactoVerdeDer(false);
    else if(dir_gravedad==3)
        player->setContactoVerdeDown(false);
    else if(dir_gravedad==2)
        player->setContactoVerdeIzq(false);
    return false;
}

//reinicio del nivel cuando muere el personaje
void Nivel::morision(){
    Motor::Instance()->getSonidoMorision()->Play();
    
    Guardar::Instance()->setMuertes(Guardar::Instance()->getMuertes()+1);
    if(dentro_portal){
        player->setPosition(inicioPortal[0], inicioPortal[1]);
    }
    else{
        player->setPosition(mapa->getInicioPersonaje()[0],mapa->getInicioPersonaje()[1]);
    }

    player->setVelocidad_x(0.f);
    player->setVelocidad_y(0.f);
    player->setRebotando(false);
    player->setArista(false);
    if(numNivel<6){//mundo1
        player->setFormaReset(0);
    }else if(numNivel>10){//mundo3
        player->setFormaReset(2);
    } else{//mundo2
        player->setFormaReset(1);
    }
    cargarEntidades();

    player->reseteaGravedad(true);
    
}

bool Nivel::evolucionBuena(){
    if(numNivel==5||numNivel==10||numNivel==15){
        if(!player->getArista())
            return false;
    }
    return true;
}