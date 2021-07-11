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
    fondo->setTexture("Nombre","png");
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }
    
    // Texto del input
    playerText = new Texto("");
    playerText->setOrigin(playerText->getWidthBounds()/2.f, playerText->getHeightBounds()/2.f);
    playerText->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/2)+50);
    playerText->setColor(36,207,253);
 

    
    // Texto de disponibilidad
    disponibilidad = new Texto("");
    disponibilidad->setSize(60);
    disponibilidad->setOrigin(disponibilidad->getWidthBounds()/2.f, disponibilidad->getHeightBounds()/2.f);
    disponibilidad->setPosition(motor->getTamWidth()/2.f, (motor->getTamHeight()/2+150));
    disponibilidad->setColor(255,0,0);
    
    if(Guardar::Instance()->getResolucion() == 720){
            playerText->setSize(60);
            disponibilidad->setSize(60);
        }
        else {
            playerText->setSize(90);
            disponibilidad->setSize(90);
        }


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

    if(playerText!=NULL){
        delete playerText;
        playerText=NULL;
    }
}


void PreguntarNombre::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
//reseteo creditos y luego cambio
    Partida::setEstado(AnimacionInicial::Instance());
}

void PreguntarNombre::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    if(conect){
        motor->ventanaDibuja(fondo->getSprite());

        playerText->drawText();

        if(playerInput.getSize() > 0){
            disponibilidad->drawText();
        } 
    }
    

    motor->ventanaDisplay();
}

void PreguntarNombre::update(){
    if(conect){
        if (borrar){
            playerInput.erase(playerInput.getSize()-1, 1);
        }
        playerText->setTexto(playerInput);

        string consult;

        

        if(compruebaNombre && playerInput.getSize() > 0){
            //centramos nombre
            playerText->setOrigin(playerText->getWidthBounds()/2.f, playerText->getHeightBounds()/2.f);
            if(motor->getTamHeight()==720)
                playerText->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/2)+25);
            else
                playerText->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/2)+50);


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
            disponibilidad->setOrigin(disponibilidad->getWidthBounds()/2.f, disponibilidad->getHeightBounds()/2.f);
            if(motor->getTamHeight()==720)
                disponibilidad->setPosition(motor->getTamWidth()/2.f, (motor->getTamHeight()/2+120));
            else
                disponibilidad->setPosition(motor->getTamWidth()/2.f, (motor->getTamHeight()/2+160));

        }
        if(insert && nombre_disponible){
            consult = "INSERT INTO `usuario`(`nombre`, `muertes`, `monedas`, `niveles`) VALUES ('"+playerInput+"',0,0,0)";
                            
            Conexion::Instance()->insert_bd(consult);
            Guardar::Instance()->setNombre(playerInput);
            CambiarEstado();
        }
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
            if(conect){
                if(playerInput != ""){
                    insert = true;
                
                }
            }
            else{
                Partida::setEstado(MenuPrincipal::Instance());

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

