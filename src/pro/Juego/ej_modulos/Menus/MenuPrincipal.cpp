#include "MenuPrincipal.h"


// Singleton 
MenuPrincipal* MenuPrincipal::pinstance = 0;
MenuPrincipal* MenuPrincipal::Instance(){
    if(pinstance == 0){
        pinstance = new MenuPrincipal;

    }
    return pinstance;
}


// Constructor
MenuPrincipal::MenuPrincipal(){
    x_cursor=0.f;
    y_cursor=0.f;

    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Menu","png");
   
    sprite_antes = new Sprite();
    sprite_antes->setTexture("CaratulaGrande","png");

    // Motor
    motor = Motor::Instance();


    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
        sprite_antes->setScale(0.67,0.67);
    }
    
    //Prueba para mejorar el menu
    r = sf::RectangleShape(sf::Vector2f(0,0));

   
    //Inicializamos los textos de las opciones
    selectedItem = 0;
    if(Guardar::Instance()->getNivel()==0){
        selectedItem=1;
    }

    if(!font.loadFromFile("resources/fonts/aAnekdot.ttf")){
        std::cout<<"No se ha podido cargar la fuente"<<std::endl;
        exit(1);
    }
    opciones[0].setString("Continuar partida");
    opciones[1].setString("Nueva partida");
    opciones[2].setString("Opciones");
    opciones[3].setString("Controles");
    opciones[4].setString("Ranking");
    opciones[5].setString("Salir");

    for(int i=0;i<num_items;i++){
        opciones[i].setFont(font);

        if(Guardar::Instance()->getResolucion() == 720){
            opciones[i].setCharacterSize(45);
        }
        else {
            opciones[i].setCharacterSize(67);
        }

        opciones[i].setPosition(sf::Vector2f(motor->getTamWidth()/2, (motor->getTamHeight()/11)*(i+4)));
        opciones[i].setOrigin(opciones[i].getGlobalBounds().width/2.f, opciones[i].getGlobalBounds().height/2.f);

        if((i==0 && Guardar::Instance()->getNivel()!=0) || (i==1 && Guardar::Instance()->getNivel()==0)){
            opciones[i].setColor(Motor::Instance()->new_color(255,255,255));
            //opciones[i].setStyle(sf::Text::Underlined);
        }
        else if(i==0){
            opciones[i].setColor(Motor::Instance()->new_color(50,50,50));
        }
        else{
            //opciones[i].setColor(Motor::Instance()->new_color(36,207,253));
        }
    }
    
    opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));

    alpha = 255;
    fondoTransicion = new Sprite();
    fondoTransicion->setTexture("fondoNegro","png");
    if(motor->getTamHeight()==720){
        fondoTransicion->setScale(0.67,0.67);
    }
}

// Destructor
MenuPrincipal::~MenuPrincipal(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(fondoTransicion!=NULL){
        delete fondoTransicion;
        fondoTransicion=NULL;
    }
    if(sprite_antes!=NULL){
        delete sprite_antes;
        sprite_antes=NULL;
    }
}

void MenuPrincipal::MoveUp(){ // seleccionamos la opcion de arriba
    if((selectedItem-1>=0 && Guardar::Instance()->getNivel()>0) || 
        (selectedItem-1>0 && Guardar::Instance()->getNivel()==0))
    {        
        motor->getSonidoMover()->Play();
        opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
        opciones[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        opciones[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        //opciones[selectedItem].setStyle(sf::Text::Underlined);
    }
}

void MenuPrincipal::MoveDown(){ // seleccionamos la opcionde abajo
    if(selectedItem+1<num_items){
        motor->getSonidoMover()->Play();
        opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
        opciones[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        opciones[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        //opciones[selectedItem].setStyle(sf::Text::Underlined);
    }
}

void MenuPrincipal::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
    if(selectedItem==0){//Continuar
        Partida::setEstado(MenuMundo::Instance());
        motor->getMusicaMenu()->pause();
        motor->getMusica()->Play();
    }
    else if(selectedItem==1){//Nueva partida
        Guardar::Instance()->reiniciarPartida();
        Nivel::Instance()->cambiarNivel(0);
        Partida::setEstado(AnimacionInicial::Instance());
        motor->getMusicaMenu()->pause();
        //motor->getMusicaAnimacion()->Play();

    }
    else if(selectedItem==2){//menu de opciones
        Opciones::Instance()->setEstadoAnterior(0);
        Partida::setEstado(Opciones::Instance());
    }
    else if(selectedItem==3){//menu de opciones
        Controles::Instance()->setEstadoAnterior(0);
        Partida::setEstado(Controles::Instance());
    }
    else if(selectedItem==4){//Ranking
        Partida::setEstado(Ranking::Instance());
    }
}

void MenuPrincipal::render(float tick){
    tick = 0.f;

    motor->ventanaClear(140,140,140);

    motor->ventanaDibuja(fondo->getSprite());
    for(int i=0;i<num_items;i++){
        motor->ventanaDibuja(opciones[i]);
    }
    //motor->ventanaDibuja(fondoTransicion->getSprite());
    motor->ventanaDibuja(sprite_antes->getSprite());
    motor->setView(0);
    motor->ventanaDisplay();
}

void MenuPrincipal::update(){

    if(alpha > 0) alpha-=4;
    if(alpha < 150) alpha-=4;
    if(alpha<0) alpha = 0;
    sprite_antes->setColor(255,255,255,alpha);

    float x_ventana = motor->getWindow()->getPosition().x;
    float y_ventana = motor->getWindow()->getPosition().y;
    x_cursor = sf::Mouse::getPosition().x - x_ventana;
    y_cursor = sf::Mouse::getPosition().y - y_ventana - 27;
}

void MenuPrincipal::input(){
  
    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }

        
        if(motor->isKeyPressedUp()){
                MoveUp();
        }
        else if(motor->isKeyPressedDown()){
                MoveDown();
        }
        

        if(motor->isKeyPressedEnter()){
            motor->getSonidoSeleccion()->Play();
            if(selectedItem==5){
                motor->ventanaClose();
            }
            else{
                CambiarEstado();
            }
        }      

        
        // input para el click del ratón
        for(int i=0; i<num_items; i++){
    
            if (Guardar::Instance()->getNivel()==0 && i == 0){
                opciones[i].setColor(Motor::Instance()->new_color(50,50,50));
            }
            else {
                opciones[i].setColor(Motor::Instance()->new_color(255,255,255));
            }

            if(opciones[i].getGlobalBounds().contains(x_cursor, y_cursor)){
                if(Guardar::Instance()->getNivel()!=0 || i != 0){
                    opciones[i].setColor(Motor::Instance()->new_color(36,207,253));
                    selectedItem = i;
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        motor->getSonidoSeleccion()->Play();
                        if(selectedItem==5){
                            motor->ventanaClose();
                        }
                        else{
                            CambiarEstado();
                        }
                    }
                }
            }
            opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
        }
    }
}

