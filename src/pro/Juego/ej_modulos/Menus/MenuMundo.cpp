#include "MenuMundo.h"

// Singleton 
MenuMundo* MenuMundo::pinstance = 0;
MenuMundo* MenuMundo::Instance(){
    if(pinstance == 0){
        pinstance = new MenuMundo;

    }
    return pinstance;
}


// Constructor
MenuMundo::MenuMundo(){

   // Motor
    motor = Motor::Instance();

    fondo=new Sprite();
    fondo->setTexture("FondoMundo","png");
    fondo->setOrigin(fondo->getBounds("global").width/2.f,fondo->getBounds("global").height/2.f);
    fondo->setPosition(motor->getCamaraCenter().x,motor->getCamaraCenter().y);

    //Inicializamos los sprites del menu del mundo
    selectedItem = 0;
    for(int i=0; i<num_items;i++){
        sprite[i] = new Sprite();
        std::stringstream sstream;
        sstream << i;
        std::string numero_del_nivel = sstream.str();
        sprite[i]->setTexture(numero_del_nivel,"png");
        sprite[i]->setScale(0.09,0.09);
        
     
        if(i==0){//nivel 0
            
            sprite[i]->setPosition(0, 500);
        }
        else if(i>0 && i<6){//mundo 1
            sprite[i]->setPosition(i*300+300, 500);
        }
        else if(i>5 && i<11){//mundo 2
            sprite[i]->setPosition(i*300+600, 500);
        }
        else{//mundo 3
            sprite[i]->setPosition(i*300+900, 500);
        }

        flechita = new Sprite();
        flechita->setTexture("flecha","png");
        flechita->setScale(0.1,0.1);

        posicion=new FlotanteInterpolado();

        /*
        if(i<Guardar::Instance()->getNivel() && i!=0){
            sprite[i]->setColor("blue");
        }
        else if(i==Guardar::Instance()->getNivel()){
            sprite[i]->setColor("red");
        }
        else if(i==0){
            sprite[i]->setColor("yellow");
        }
        else {
            sprite[i]->setColor("black");
        }
        */
    }
    actualiza_colores();
}

// Destructor
MenuMundo::~MenuMundo(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    
    for(int i=0;i<num_items;i++){
        if(sprite[i]!=NULL){
            delete sprite[i];
            sprite[i]=NULL;
        }
    }

    if(flechita!=NULL){
            delete flechita;
            flechita=NULL;
        }
    if(posicion!=NULL){
        delete posicion;
        posicion=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
}

void MenuMundo::MoveLeft(){ // seleccionamos el nivel de la izquierda
    if(selectedItem-1>=0){
        motor->getSonidoMover()->Play();
        /*
        if(selectedItem==Guardar::Instance()->getNivel()){
            sprite[selectedItem]->setColor("red");
        }
        else {
            sprite[selectedItem]->setColor("blue");
        }
        */
        selectedItem--;
        //sprite[selectedItem]->setColor("yellow");
    }
}

void MenuMundo::MoveRight(){ // seleccionamos el nivel de la derecha
    if((selectedItem+1<num_items) && selectedItem<Guardar::Instance()->getNivel()){
        motor->getSonidoMover()->Play();
        //sprite[selectedItem]->setColor("blue");
        selectedItem++;
        //sprite[selectedItem]->setColor("yellow");
    }
}

void MenuMundo::CambiarEstado(){ // Cuando seleccionamos un nivel, cambiamos a InGame.cpp
  Nivel::Instance()->cambiarNivel(selectedItem);
  InGame::Instance()->reseteaRenderizarTexto();
  Partida::setEstado(InGame::Instance());
}

void MenuMundo::render(float tick){
    float factor=min(1.f, tick/(1/15.f));
    float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
    float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();
    motor->ventanaClear(140,140,140);

    fondo->setPosition(interX,interY);
    motor->ventanaDibuja(fondo->getSprite());
    for(int i=0;i<num_items;i++){
        motor->ventanaDibuja(sprite[i]->getSprite());
    }
    flechita->setPosition(interX+23,interY-53);
    motor->ventanaDibuja(flechita->getSprite());
    Hud::Instance()->render(factor, false, false);
    
    motor->setView(1);

    motor->ventanaDisplay();
}

void MenuMundo::update(){

    

    float x_centro = sprite[selectedItem]->getXPosition();
    float y_centro = sprite[selectedItem]->getYPosition();
    motor->setCameraCenter(x_centro, y_centro);

    posicion->setPositionXY(x_centro, y_centro);
    Hud::Instance()->update(selectedItem,0);
}

void MenuMundo::input(){
  
    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }

        if(motor->isKeyPressedRight()){
            MoveRight();
        }
        else if(motor->isKeyPressedLeft()){
            MoveLeft();
        }
        else if(motor->isKeyPressedP()){ // esto es para desbloquear todos los niveles
            Guardar::Instance()->setNivel(15);
            Guardar::Instance()->setHabilidades(5);
            actualiza_colores();
        }
        else if(motor->isKeyPressedEscape()){
            motor->getMusica()->pause();
            motor->getMusicaMenu()->Play();
            Pausa::Instance()->setEstadoAnterior(0);
            Partida::setEstado(Pausa::Instance());
        }
        else if(motor->isKeyPressedEnter()){
            motor->getSonidoSeleccion()->Play();
            CambiarEstado();
        }
    }
    

}


void MenuMundo::actualiza_colores(){
    for(int i=0; i<num_items;i++){

        if(i>Guardar::Instance()->getNivel()){
            sprite[i]->setTexture("nivelBloqueado","png");
            sprite[i]->setScale(0.5,0.5);
        }
        else {
            std::stringstream sstream;
            sstream << i;
            std::string numero_del_nivel = sstream.str();
            sprite[i]->setTexture(numero_del_nivel,"png");
            sprite[i]->setScale(0.09,0.09);
        }



    
    }
}