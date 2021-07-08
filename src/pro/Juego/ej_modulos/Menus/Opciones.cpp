#include "Opciones.h"


// Singleton 
Opciones* Opciones::pinstance = 0;
Opciones* Opciones::Instance(){
    if(pinstance == 0){
        pinstance = new Opciones;

    }
    return pinstance;
}


// Constructor
Opciones::Opciones(){
    estadoAnterior=0;
    x_cursor=0.f;
    y_cursor=0.f;
     // Motor
    motor = Motor::Instance();

    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Opciones","png");

    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }
    //fondo->setScale(0.67,0.67);

    //Imegenes flechitas
    for(int i=0;i<6;i++){
        flechitas[i]=new Sprite();

        if(motor->getTamHeight()==720){
            flechitas[i]->setScale(0.75,0.75);
        }
     
        if(i%2==0)
            flechitas[i]->setTexture("Flecha1","png");
        else
            flechitas[i]->setTexture("Flecha2","png");

    }
    float TAM_WIDTH = motor->getTamWidth();
    float TAM_HEIGHT = motor->getTamHeight();
    flechitas[0]->setPosition((TAM_WIDTH/10)*(6)-64, (TAM_HEIGHT/9)*(3));
    flechitas[1]->setPosition((TAM_WIDTH/10)*(7)+64, (TAM_HEIGHT/9)*(3));
    flechitas[2]->setPosition((TAM_WIDTH/10)*(6)-64, (TAM_HEIGHT/9)*(4));
    flechitas[3]->setPosition((TAM_WIDTH/10)*(7)+64, (TAM_HEIGHT/9)*(4));
    flechitas[4]->setPosition((TAM_WIDTH/10)*(6)-90, (TAM_HEIGHT/9)*(5));
    flechitas[5]->setPosition((TAM_WIDTH/10)*(7)+100, (TAM_HEIGHT/9)*(5));

    //Imagen volumenes
    volumenMusica=new Sprite();
    volumenMusica->setTexture("Volumen","png");
    numMusica=Guardar::Instance()->getMusica()/20;
    volumenMusica->setFrameSprite(0,0,28*numMusica,72);
    volumenMusica->setPosition((TAM_WIDTH/10)*(6)+10, (TAM_HEIGHT/9)*(3)-11);
    if(motor->getTamHeight()==1080){
        volumenMusica->setScale(1.5,1.5);
    }

    volumenSonido=new Sprite();
    volumenSonido->setTexture("Volumen","png");
    numSonido=Guardar::Instance()->getSonido()/20;
    volumenSonido->setFrameSprite(0,0,28*numSonido,72);
    volumenSonido->setPosition((TAM_WIDTH/10)*(6)+10, (TAM_HEIGHT/9)*(4)-11);
    if(motor->getTamHeight()==1080){
        volumenSonido->setScale(1.5,1.5);
    }

  

    //Inicializamos los textos de las opciones
    selectedItem = 0;

    opciones[0]=new Texto("Volumen musica");
    opciones[1]=new Texto("Volumen sonidos");
    opciones[2]=new Texto("Resolucion");
    opciones[3]=new Texto("Volver");

    for(int i=0;i<num_items;i++){
        if(Guardar::Instance()->getResolucion() == 720){
            opciones[i]->setSize(45);
        }
        else {
            opciones[i]->setSize(67);
        }

        opciones[i]->setOrigin(opciones[i]->getWidthBounds()/2.f, opciones[i]->getHeightBounds()/2.f);
        if(i==num_items-1)//opcion de volver enmedio
            opciones[i]->setPosition(TAM_WIDTH/2, (TAM_HEIGHT/9)*(i+3));
        else{
            opciones[i]->setPosition(TAM_WIDTH/3, (TAM_HEIGHT/9)*(i+3));
        }

        if(i==0){
            opciones[i]->setColor(255,255,255);
        }
        else{
            opciones[i]->setColor(36,207,253);
        }
    }
    
    if(Guardar::Instance()->getResolucion() == 720){
        resolucion=0;    
    }
    else {
        resolucion=1;
    }
    
    resoluciones[0]=new Texto("1280x720");
    resoluciones[1]=new Texto("1920x1080");
    for(int i=0;i<2;i++){
        if(Guardar::Instance()->getResolucion() == 720){
            resoluciones[i]->setSize(40);
        }
        else {
            resoluciones[i]->setSize(50);
        }
        resoluciones[i]->setOrigin(resoluciones[i]->getWidthBounds()/2.f, resoluciones[i]->getHeightBounds()/2.f);
        resoluciones[i]->setPosition((TAM_WIDTH/10)*(i+6)+20, (TAM_HEIGHT/9)*(5));

        if(i==resolucion){
            resoluciones[i]->setColor(255,255,0);
            //resoluciones[i]->setColor(36,207,253);
        }
        else{
            resoluciones[i]->setColor(255,255,255);
        }

        
    }
    
}

// Destructor
Opciones::~Opciones(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(volumenMusica!=NULL){
        delete volumenMusica;
        volumenMusica=NULL;
    }
    if(volumenSonido!=NULL){
        delete volumenSonido;
        volumenSonido=NULL;
    }
    for(int i=0;i<2;i++){
        if(resoluciones[i]!=NULL){
            delete resoluciones[i];
            resoluciones[i]=NULL;
        }
    }
    for(int i=0;i<num_items;i++){
        if(opciones[i]!=NULL){
            delete opciones[i];
            opciones[i]=NULL;
        }
    }
    for(int i=0;i<6;i++){
        if(flechitas[i]!=NULL){
            delete flechitas[i];
            flechitas[i]=NULL;
        }
    }
}

void Opciones::MoveUp(){ // seleccionamos la opcion de arriba
    if(selectedItem-1>=0){
        motor->getSonidoMover()->Play();
        opciones[selectedItem]->setColor(36,207,253);
        selectedItem--;
        opciones[selectedItem]->setColor(255,255,255);
    }
}

void Opciones::MoveDown(){ // seleccionamos la opcionde abajo
    if(selectedItem+1<num_items){
        motor->getSonidoMover()->Play();
        opciones[selectedItem]->setColor(36,207,253);
        selectedItem++;
        opciones[selectedItem]->setColor(255,255,255);
    }
}

void Opciones::MoveRight(){
    if(selectedItem==0&&motor->getMusica()->getVolume()<100){
        motor->getSonidoMover()->Play();
        numMusica++;
        volumenMusica->setFrameSprite(0,0,28*numMusica,72);
        motor->getMusica()->setVolume(motor->getMusica()->getVolume()+20);
        motor->getMusicaMenu()->setVolume(motor->getMusicaMenu()->getVolume()+20);
        motor->getMusicaAnimacion()->setVolume(motor->getMusicaAnimacion()->getVolume()+20);
        Guardar::Instance()->setMusica(motor->getMusica()->getVolume());
        
    }
    else if(selectedItem==1&&motor->getSonidoMover()->getVolume()<100){
        motor->getSonidoMover()->Play();
        numSonido++,
        volumenSonido->setFrameSprite(0,0,28*numSonido,72);
        motor->getSonidoMover()->setVolume(motor->getSonidoMover()->getVolume()+20);
        motor->getSonidoSeleccion()->setVolume(motor->getSonidoSeleccion()->getVolume()+20);
        motor->getSonidoMorision()->setVolume(motor->getSonidoMorision()->getVolume()+20);
        motor->getSonidoEvolucion()->setVolume(motor->getSonidoEvolucion()->getVolume()+20);
        motor->getSonidoNivelCompleto()->setVolume(motor->getSonidoNivelCompleto()->getVolume()+20);

        Guardar::Instance()->setSonido(motor->getSonidoSeleccion()->getVolume());

    }
    else if(selectedItem==2){
        if(resolucion+1<2){
            motor->getSonidoMover()->Play();
            Partida::setEstado(CambioResolucion::Instance());
        }
    }

}

void Opciones::MoveLeft(){
    if(selectedItem==0&&motor->getMusica()->getVolume()>0){
        motor->getSonidoMover()->Play();
        numMusica--;
        volumenMusica->setFrameSprite(0,0,28*numMusica,72);
        motor->getMusica()->setVolume(motor->getMusica()->getVolume()-20);
        motor->getMusicaMenu()->setVolume(motor->getMusicaMenu()->getVolume()-20);
        motor->getMusicaAnimacion()->setVolume(motor->getMusicaAnimacion()->getVolume()-20);
        Guardar::Instance()->setMusica(motor->getMusica()->getVolume());

    }
    else if(selectedItem==1&&motor->getSonidoMover()->getVolume()>0){
        motor->getSonidoMover()->Play();
        numSonido--,
        volumenSonido->setFrameSprite(0,0,28*numSonido,72);
        motor->getSonidoMover()->setVolume(motor->getSonidoMover()->getVolume()-20);
        motor->getSonidoSeleccion()->setVolume(motor->getSonidoSeleccion()->getVolume()-20);
        motor->getSonidoMorision()->setVolume(motor->getSonidoMorision()->getVolume()-20);
        motor->getSonidoEvolucion()->setVolume(motor->getSonidoEvolucion()->getVolume()-20);
        motor->getSonidoNivelCompleto()->setVolume(motor->getSonidoNivelCompleto()->getVolume()-20);

        Guardar::Instance()->setSonido(motor->getSonidoSeleccion()->getVolume());
    }
    else if(selectedItem==2){
        if(resolucion-1>=0){
            motor->getSonidoMover()->Play();
            Partida::setEstado(CambioResolucion::Instance());
        }
    }
}

void Opciones::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
    if(estadoAnterior==0)
        Partida::setEstado(MenuPrincipal::Instance());
    else
        Partida::setEstado(Pausa::Instance());

}

void Opciones::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());
    if(numSonido>0)
        motor->ventanaDibuja(volumenSonido->getSprite());
    if(numMusica>0)
        motor->ventanaDibuja(volumenMusica->getSprite());
    for(int i=0;i<num_items;i++){
        opciones[i]->drawText();
    }
    for(int i=0;i<2;i++){
        resoluciones[i]->drawText();
    }
    for(int i=0;i<6;i++){
        motor->ventanaDibuja(flechitas[i]->getSprite());
    }
    motor->ventanaDisplay();
}

void Opciones::update(){
    float x_ventana = motor->getWindow()->getPosition().x;
    float y_ventana = motor->getWindow()->getPosition().y;
    x_cursor = sf::Mouse::getPosition().x - x_ventana;
    y_cursor = sf::Mouse::getPosition().y - y_ventana - 27;

    if(click_flechita==0){
        selectedItem = 0;
        MoveLeft();
    }
    else if(click_flechita==1){
        selectedItem = 0;
        MoveRight();
 
    }
    else if(click_flechita==2){
        selectedItem = 1;
        MoveLeft();
    }
    else if(click_flechita==3){
        selectedItem = 1;
        MoveRight();
    }
    else if(click_flechita==4){
        selectedItem = 2;
        MoveLeft();
    }
    else if(click_flechita==5){
        selectedItem = 2;
        MoveRight();
    }
    click_flechita = -1;
}

void Opciones::input(){
    
    while(motor->ventanaPollEvent()) {
        sf::Event *event =  motor->getEvent();
    //while(motor->getWindow()->pollEvent(event)){
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }

        if(motor->isKeyPressedUp()){
                MoveUp();
        }
        else if(motor->isKeyPressedDown()){
                MoveDown();
        }
        else if(motor->isKeyPressedRight()){
                MoveRight();
        }
        else if(motor->isKeyPressedLeft()){
                MoveLeft();
        }
        else if(motor->isKeyPressedEnter()){
            if(selectedItem==3){//volver
                motor->getSonidoSeleccion()->Play();
                CambiarEstado();
            }
        }

        // input para el click del ratón
        for(int i=0; i<num_items; i++){  
            opciones[i]->setColor(255,255,255);           
            if(opciones[i]->getGlobalBounds().contains(x_cursor,y_cursor)){
                opciones[i]->setColor(36,207,253);
                selectedItem = i;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(selectedItem==3){//volver
                        motor->getSonidoSeleccion()->Play();
                        CambiarEstado();
                    }
                }
            }
            opciones[selectedItem]->setColor(36,207,253);
        }

        for(int i=0; i<2; i++){
            if(resolucion==i) resoluciones[i]->setColor(255,255,0);
            else resoluciones[i]->setColor(255,255,255);
            
            if(resoluciones[i]->getGlobalBounds().contains(x_cursor,y_cursor)){
                resoluciones[i]->setColor(36,207,253);

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && i != resolucion){                 
                    //resolucion = i;
                    motor->getSonidoSeleccion()->Play();
                    /*if(i==0){
                        motor->setSizeVentana(1280,720);
                        Guardar::Instance()->setResolucion(720);
                    }
                    else {
                        motor->setSizeVentana(1920,1080);
                        Guardar::Instance()->setResolucionAtr(1080);     
                    }*/
                    Partida::setEstado(CambioResolucion::Instance());
                }
            }
        }  

        for(int i=0; i<6; i++){
            flechitas[i]->setColor(255,255,255);
            if(flechitas[i]->getSprite().getGlobalBounds().contains(x_cursor,y_cursor)){
                flechitas[i]->setColor(36,207,253);
                if (event->type == sf::Event::MouseButtonPressed){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){  
                        if(i==0){
                            click_flechita = 0;
                            break;
                        }
                        else if(i==1){
                            click_flechita = 1;
                            break;
                        }
                        else if(i==2){
                            click_flechita = 2;
                            break;
                        }
                        else if(i==3){
                            click_flechita = 3;
                            break;

                        }
                        else if(i==4){
                            click_flechita = 4;
                            break;

                        }
                        else if(i==5){
                            click_flechita = 5;
                            break;

                        }
                    }
                }
            }
        }      
    } 
}

