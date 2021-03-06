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
    opciones[5].setString("Soporte");

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
        if(Conexion::Instance()->getConexion()){
            if(Guardar::Instance()->getNombre() != "nuevo"){
                // Borramos de la BD los datos de la persona anterior
                std::string consult = "DELETE FROM `usuario` WHERE nombre='"+Guardar::Instance()->getNombre()+"'";
                Conexion::Instance()->update_bd(consult);
            }
            Guardar::Instance()->reiniciarPartida();
            MenuMundo::Instance()->resetSelect();
            Nivel::Instance()->cambiarNivel(0);
            PreguntarNombre::Instance()->setConnect(true);
        }
        else
            PreguntarNombre::Instance()->setConnect(false);
            
        Partida::setEstado(PreguntarNombre::Instance());

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
        if(Conexion::Instance()->getConexion()){
             // Se hacen los updates en la BD con los nuevos datos

            update_datos_player();
            Ranking::Instance()->setConnect(true);
            Ranking::Instance()->actualiza_ranking();
        }
        else{
            Ranking::Instance()->setConnect(false);
        }
        Partida::setEstado(Ranking::Instance());
    }
    else if(selectedItem==5){//Soporte
        Partida::setEstado(Soporte::Instance());
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
            CambiarEstado();
        }      

        
        // input para el click del rat??n
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
                        CambiarEstado();
                    }
                }
            }
            opciones[selectedItem].setColor(Motor::Instance()->new_color(36,207,253));
        }
    }
}


void MenuPrincipal::update_datos_player(){
      int nivel_actual = Guardar::Instance()->getNivel();
    int num_secretos=0;
    if(Guardar::Instance()->getSecreto1()==1)
        num_secretos++;
    if(Guardar::Instance()->getSecreto2()==1)
        num_secretos++;
    if(Guardar::Instance()->getSecreto3()==1)
        num_secretos++;

    std::string nombre_actual = Guardar::Instance()->getNombre();
    int muertes_actual = Guardar::Instance()->getMuertes();
    
    // Pasamos a string lo que obtenemos de save.xml
    std::string moneda;
    stringstream ss;  
    ss << num_secretos;  
    ss >> moneda;

    std::string muertes_s;
    stringstream ss2;  
    ss2 << muertes_actual;  
    ss2 >> muertes_s;

    std::string nivel;
    stringstream ss3; 
    ss3 << nivel_actual;
    ss3 >> nivel;

    // Hacemos la consulta
    std::string consult = "UPDATE `usuario` SET `muertes`="+muertes_s+",`monedas`="+moneda+",`niveles`="+nivel+" WHERE nombre = '"+nombre_actual+"'";
    if(Conexion::Instance()->getConexion())
        Conexion::Instance()->update_bd(consult);
}