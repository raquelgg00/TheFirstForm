#include "Pausa.h"


// Singleton 
Pausa* Pausa::pinstance = 0;
Pausa* Pausa::Instance(){
    if(pinstance == 0){
        pinstance = new Pausa;

    }
    return pinstance;
}


// Constructor
Pausa::Pausa(){
    estadoAnterior=0;

    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Pausa","png");

    // Motor
    motor = Motor::Instance(); 
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }
    
    //Prueba para mejorar el menu
    r = sf::RectangleShape(sf::Vector2f(0,0));

   

    //Inicializamos los textos de las opciones
    selectedItem = 0;

    if(!font.loadFromFile("resources/fonts/aAnekdot.ttf")){
        std::cout<<"No se ha podido cargar la fuente"<<std::endl;
        exit(1);
    }
    opciones[0].setString("Continuar partida");
    opciones[1].setString("Opciones");
    opciones[2].setString("Controles");
    opciones[3].setString("Elegir nivel");
    opciones[4].setString("Salir de la partida");

    for(int i=0;i<num_items;i++){
        opciones[i].setFont(font);
        if(motor->getTamHeight()==720){
            opciones[i].setCharacterSize(45);
        }
        else
            opciones[i].setCharacterSize(67);
        
        opciones[i].setPosition(sf::Vector2f(motor->getTamWidth()/2, -20+(motor->getTamHeight()/11)*(i+4)));
        opciones[i].setOrigin(opciones[i].getGlobalBounds().width/2.f, opciones[i].getGlobalBounds().height/2.f);
        opciones[i].setColor(Motor::Instance()->new_color(255,255,255));

    }
    opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));

    opciones2[0].setString("Continuar partida");
    opciones2[1].setString("Opciones");
    opciones2[2].setString("Controles");
    opciones2[3].setString("Salir de la partida");

    for(int i=0;i<num_items-1;i++){
        opciones2[i].setFont(font);
        if(motor->getTamHeight()==720){
            opciones2[i].setCharacterSize(45);
        }
        else
            opciones2[i].setCharacterSize(67);
        
        opciones2[i].setPosition(sf::Vector2f(motor->getTamWidth()/2, 30+(motor->getTamHeight()/11)*(i+4)));
        opciones2[i].setOrigin(opciones2[i].getGlobalBounds().width/2.f, opciones2[i].getGlobalBounds().height/2.f);
        opciones2[i].setColor(Motor::Instance()->new_color(255,255,255));

    }
    opciones2[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
    motor->getMusicaMenu()->Play();
}

// Destructor
Pausa::~Pausa(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
}

void Pausa::MoveUp(){ // seleccionamos la opcion de arriba
    if(estadoAnterior==1){
        if(selectedItem-1>=0){        
            motor->getSonidoMover()->Play();
            opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            selectedItem--;
            opciones[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        }
    }
    else{
        if(selectedItem-1>=0){        
            motor->getSonidoMover()->Play();
            opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            selectedItem--;
            opciones[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        }
}
}

void Pausa::MoveDown(){ // seleccionamos la opcionde abajo
    if(estadoAnterior==1){
        if(selectedItem+1<num_items){
            motor->getSonidoMover()->Play();
            opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            selectedItem++;
            opciones[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        }
    }
    else{
        if(selectedItem+1<num_items-1){
            motor->getSonidoMover()->Play();
            opciones2[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            selectedItem++;
            opciones2[selectedItem].setColor(Motor::Instance()->new_color(255,255,255));
        }
    }
    
}

void Pausa::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
    if(selectedItem==0){//Continuar
        if(estadoAnterior==1){
            Partida::setEstado(InGame::Instance());
        }
        else
            Partida::setEstado(MenuMundo::Instance());

        motor->getMusicaMenu()->pause();
        motor->getMusica()->Play();
        
    }
    else if(selectedItem==2){//Controles
        Opciones::Instance()->setEstadoAnterior(1);
        Partida::setEstado(Controles::Instance());

    }
    else if(selectedItem==1){//Opciones
        Opciones::Instance()->setEstadoAnterior(1);
        Partida::setEstado(Opciones::Instance());
    }
    else if(selectedItem==3){//Ir a menu mundo
        if(estadoAnterior==1){
            motor->setCamaraRotation(0);
            InGame::Instance()->reseteaGravedad();
            motor->getMusicaMenu()->pause();
            motor->getMusica()->Play();
            
            if(InGame::Instance()->getDentroPortal()&&primeraVez){
                primeraVez=false;
                Guardar::Instance()->setHabilidadesAtrib(Guardar::Instance()->getHabilidades()-1);
            }
            Partida::setEstado(MenuMundo::Instance());
        }
        else
            Partida::setEstado(MenuPrincipal::Instance());
    }
    else if(selectedItem==4){//Menu principal
        Partida::setEstado(MenuPrincipal::Instance());
    }
}

void Pausa::render(float tick){
    tick = 0.f;

    motor->ventanaClear(140,140,140);

    motor->ventanaDibuja(fondo->getSprite());
    if(estadoAnterior==0){
        for(int i=0;i<num_items-1;i++){
            motor->ventanaDibuja(opciones2[i]);
        }
    }else{
        for(int i=0;i<num_items;i++){
            motor->ventanaDibuja(opciones[i]);
        }
    }
    
    motor->setCameraCenter(motor->getTamWidth()/2,motor->getTamHeight()/2);
    motor->setView(0);
    motor->ventanaDisplay();
}

void Pausa::update(){

}

void Pausa::input(){
  
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
            CambiarEstado();
        }      

        float x_ventana = motor->getWindow()->getPosition().x;
        float y_ventana = motor->getWindow()->getPosition().y;
        float x_cursor = sf::Mouse::getPosition().x - x_ventana;
        float y_cursor = sf::Mouse::getPosition().y - y_ventana - 27;

        if(estadoAnterior==1){
            for(int i=0; i<num_items; i++){
        
                opciones[i].setColor(Motor::Instance()->new_color(255,255,255));

                if(opciones[i].getGlobalBounds().contains(x_cursor, y_cursor)){
                    if(Guardar::Instance()->getNivel()!=0 || i != 0){
                        opciones[i].setColor(Motor::Instance()->new_color(36,207,253));
                        selectedItem = i;
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            motor->getSonidoSeleccion()->Play();
                            CambiarEstado();
                        }
                    }
                }
                opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            }
        }
        else{
            for(int i=0; i<num_items-1; i++){
        
                opciones2[i].setColor(Motor::Instance()->new_color(255,255,255));

                if(opciones2[i].getGlobalBounds().contains(x_cursor, y_cursor)){
                    if(Guardar::Instance()->getNivel()!=0 || i != 0){
                        opciones2[i].setColor(Motor::Instance()->new_color(36,207,253));
                        selectedItem = i;
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            motor->getSonidoSeleccion()->Play();
                            CambiarEstado();
                        }
                    }
                }
                opciones2[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
            }
        }
    }
}

