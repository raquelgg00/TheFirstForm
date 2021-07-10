#include "PreguntarNombre.h"

// Singleton 
PreguntarNombre* PreguntarNombre::pinstance = 0;
PreguntarNombre* PreguntarNombre::Instance(){
    if(pinstance == 0){
        pinstance = new PreguntarNombre;

    }
    return pinstance;
}

// Constructor
PreguntarNombre::PreguntarNombre(){

    // Motor
    motor = Motor::Instance();
    
    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Creditos","png");
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }

    //Fondo del menu
    logo=new Sprite();
    logo->setTexture("Logo1","png");
    logo->setOrigin(logo->getBounds("global").width/2.f, logo->getBounds("global").height/2.f);
    logo->setPosition(motor->getTamWidth()/2, 150);

    if(motor->getTamHeight()==720)
        logo->setScale(0.15,0.15);
    else
        logo->setScale(0.22,0.22);
   

    //Inicializamos los textos de las opciones
    nombres[0]=new Texto("Introduce tu nombre");
    nombres[1]=new Texto("(se mostrara publicamente en el Ranking si estas entre los mejores)");
    
    for(int i=0;i<num_items;i++){
        if(motor->getTamHeight()==720){
            nombres[i]->setSize(75 - (i*30));
        }
        else
            nombres[i]->setSize(100 - (i*30));

        nombres[i]->setOrigin(nombres[i]->getWidthBounds()/2.f, nombres[i]->getHeightBounds()/2.f);
        nombres[i]->setPosition(motor->getTamWidth()/2, 200+(i*75));
        nombres[i]->setColor(255,255,255);
    }
    
    
    // Texto del input
    playerText = new Texto("");
    playerText->setOrigin(playerText->getWidthBounds()/2.f, playerText->getHeightBounds()/2.f);
    playerText->setPosition(motor->getTamWidth()/2.5, (motor->getTamHeight()/2));
    playerText->setColor(36,207,253);
    playerText->setSize(80);

    // Texto de disponibilidad
    disponibilidad = new Texto("");
    disponibilidad->setSize(60);
    disponibilidad->setOrigin(disponibilidad->getWidthBounds()/2.f, disponibilidad->getHeightBounds()/2.f);
    disponibilidad->setPosition(motor->getTamWidth()/3.f, (motor->getTamHeight()/2+100));
    disponibilidad->setColor(255,0,0);
    


    borrar = false;
    insert = false;
    compruebaNombre = false;
    nombre_disponible = false;
}

// Destructor
PreguntarNombre::~PreguntarNombre(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(logo!=NULL){
        delete logo;
        logo=NULL;
    }
    for(int i=0;i<num_items;i++){
        if(nombres[i]!=NULL){
            delete nombres[i];
            nombres[i]=NULL;
        }
    }
    if(playerText!=NULL){
        delete playerText;
        playerText=NULL;
    }
}


void PreguntarNombre::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
//reseteo creditos y luego cambio
    logo->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(10));

    for(int i=0;i<num_items;i++){
        nombres[i]->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(i+12));
    }
    Partida::setEstado(AnimacionInicial::Instance());
}

void PreguntarNombre::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());

    for(int i=0;i<num_items;i++){
        nombres[i]->drawText();
    }
    playerText->drawText();

    if(playerInput.getSize() > 0){
        disponibilidad->drawText();
    }

    motor->ventanaDisplay();
}

void PreguntarNombre::update(){

    if (borrar){
        playerInput.erase(playerInput.getSize()-1, 1);
    }
    playerText->setTexto(playerInput);

    string consult;

    

    if(compruebaNombre && playerInput.getSize() > 0){
        consult = "SELECT * FROM usuario WHERE nombre='"+playerInput+"'";
        string** select_nombres = Conexion::Instance()->select_bd(consult, 1);


        if(select_nombres[0][0] == playerInput){
            disponibilidad->setTexto("Nombre no disponible");
            disponibilidad->setColor(255,0,0);
            nombre_disponible = false;
        }
        else {
            disponibilidad->setTexto("Nombre disponible");
            disponibilidad->setColor(0,255,0);
            nombre_disponible = true;

        }
    }
    if(insert && nombre_disponible){
        consult = "INSERT INTO `usuario`(`nombre`, `muertes`, `monedas`, `niveles`) VALUES ('"+playerInput+"',0,0,0)";
                          
        Conexion::Instance()->insert_bd(consult);
        Guardar::Instance()->setNombre(playerInput);
        CambiarEstado();
    }
}

void PreguntarNombre::input(){
    borrar = false;
    insert = false;
    compruebaNombre = false;

    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        } 
       

        if(motor->isKeyPressedEnter()){
            if(playerInput != ""){
                insert = true;
               
            }
        }
        else if(motor->isKeyBorrar()){
            if(playerInput != ""){
                borrar = true;
                compruebaNombre = true;
            }
        }
        else if(motor->isKeyPressedEscape()){
            Partida::setEstado(MenuPrincipal::Instance());
        }
        else if (motor->getEvent()->type == sf::Event::TextEntered){
            if(playerInput.getSize() < 10){

                sf::Uint32 unicode = motor->getEvent()->text.unicode;
                if(motor->getEvent()->text.unicode >= 65 && motor->getEvent()->text.unicode <= 90){
                    unicode += 32;
                }

                playerInput += unicode;
                compruebaNombre = true;
            }
        }
    }
}

