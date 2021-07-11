#include "InGame.h"

// Singleton
InGame* InGame::pinstance = 0;
InGame* InGame::Instance(){
    if(pinstance == 0){
        pinstance = new InGame;

    }
    return pinstance;
}

// Constructor
InGame::InGame(){

    nivel = Nivel::Instance();
    motor = Motor::Instance();
    p1 = Player::Instance();
    cambiando_gravedad_izq = false;
    cambiando_gravedad_drcha = false;
    cambiando_gravedad_volando = false;
    cont_gravedad = 0;
    dir_gravedad = 0;
    gravedad = 2.0;
    //atravesarObj = false;

    // Texto inicio
    textoNivel = new Texto("Nivel 0 ");
    textoNivel->setSize(120);
    textoNivel->setColor(0,0,0);
    //textoNivel->setOrigin(textoNivel->getGlobalBounds().width/2.f, textoNivel->getGlobalBounds().height/2.f);
    textoNivel->setPosition(motor->getCamaraCenter().x,motor->getCamaraCenter().y);
    textoFondo = new Texto("Nivel 0 ");
    textoFondo->setSize(123);
    textoFondo->setColor(255,255,255);
    textoFondo->setPosition(motor->getCamaraCenter().x,motor->getCamaraCenter().y);
}

// Destructor
InGame::~InGame(){
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(textoNivel!=NULL){
        delete textoNivel;
        textoNivel=NULL;
    }
    if(textoFondo!=NULL){
        delete textoFondo;
        textoFondo=NULL;
    }
}


// Cambia de InGame a MenuMundo
void InGame::CambiarEstado(){
    dir_gravedad = 0;
    motor->setCamaraRotation(0);
    p1->getSprite()->setRotation(0);
    Hud::Instance()->setRotacion(0);

    if(nivel->getDentroPortal()) 
        Guardar::Instance()->setHabilidadesAtrib(Guardar::Instance()->getHabilidades()-1);

    MenuMundo::Instance()->actualiza_colores();

    if(nivel->getNumNivel()==15&&Guardar::Instance()->getTerminado()==0){
        Guardar::Instance()->setTerminado(1);//juego terminado
        Partida::setEstado(Creditos::Instance());
    }
    else
        Partida::setEstado(MenuMundo::Instance());
}


void InGame::render(float tick){

    if(subiendo_alpha && renderizar_texto){
        alpha+=4;
        if(alpha>=255) {
            alpha = 255;
            subiendo_alpha = false;
        }
    }
    else {
        alpha-=4;
        if(alpha<0){
            alpha = 0;
            subiendo_alpha = true;
            renderizar_texto = false;
        }
    }
    
    textoNivel->setColor(0,0,0,alpha);
    textoFondo->setColor(255,255,255,alpha);

    //int nivel = Nivel::Instance()->getNumNivel();
    motor->ventanaClear(0,0,0);

        

    
    FlotanteInterpolado *inter=p1->getPosicion();
    float factor = min(1.f, tick/(1/15.f));
    float interX = (inter->getX()-inter->getPrevX()) * factor + inter->getPrevX();
    float interY = (inter->getY()-inter->getPrevY()) * factor + inter->getPrevY();

    motor->setCameraCenter(interX, interY);
    motor->setView(1);

    nivel->render(tick);

    p1->getSprite()->setPosition(interX, interY);

    motor->ventanaDibuja(p1->getSprite()->getSprite());

    if(cambiando_gravedad_drcha || cambiando_gravedad_izq || cambiando_gravedad_volando)
        Hud::Instance()->render(factor, renderizar_texto,true);
    else
        Hud::Instance()->render(factor, renderizar_texto,false);


    if(renderizar_texto){
        textoNivel->setPosition(motor->getCamaraCenter().x-textoNivel->getWidthBounds()/2.f,motor->getCamaraCenter().y-textoNivel->getHeightBounds()/2.f-150);
        textoFondo->setPosition(motor->getCamaraCenter().x-textoFondo->getWidthBounds()/2.f-7,motor->getCamaraCenter().y-textoFondo->getHeightBounds()/2.f-150-5);
        //textoNivel->setPosition(Player::Instance()->getX(), Player::Instance()->getY());
        textoFondo->drawText();
        textoNivel->drawText();
    }

    motor->ventanaDisplay();

    
}

void InGame::update(){

    if(p1->getReseteaGravedad()){
        dir_gravedad=0;
        p1->reseteaGravedad(false);
        motor->setCamaraRotation(0);
        p1->getSprite()->setRotation(0);
        Hud::Instance()->setRotacion(0);
    }

    if(cambiando_gravedad_drcha || cambiando_gravedad_izq){

        int invertir = 1;
        if(cambiando_gravedad_izq) invertir = -1;
        

        motor->setCamaraRotation(motor->getCamaraRotation() + 1.0 * invertir);
        float rotacion_player = p1->getSprite()->getRotation();
        p1->getSprite()->setRotation(rotacion_player+ 1.0 * invertir);
        Hud::Instance()->setRotacion(rotacion_player+1.0*invertir);
        cont_gravedad+=1;
        if(cont_gravedad == 90){
            if(cambiando_gravedad_drcha){
                
                cambiando_gravedad_drcha=false;
                dir_gravedad++;
                if(dir_gravedad==4) dir_gravedad=0;
                cambiando_gravedad_volando = true;
                
            }
            else {
                cambiando_gravedad_izq=false;
                dir_gravedad = dir_gravedad - 1;
                if(dir_gravedad<0) dir_gravedad=3;
                cambiando_gravedad_volando = true;
            }
            cont_gravedad = 0;   
            p1->setEnSuelo(false);  
        }       
    }
    else {

        if(cambiando_gravedad_volando) {
            if(p1->getEnSuelo()){
                cambiando_gravedad_volando = false;
            }
        }

        if(nivel->getCompletado()){
            Guardar::Instance()->setNivel(nivel->getNumNivel()+1);//guardo partida
            motor->setShader(false);



            // Al completar el  nivel se hacen los updates en la BD con los nuevos datos
            int nivel_actual = Guardar::Instance()->getNivel();
            int monedas_actual = Guardar::Instance()->getMonedas();
            std::string nombre_actual = Guardar::Instance()->getNombre();
            int muertes_actual = Guardar::Instance()->getMuertes();
            
            // Pasamos a string lo que obtenemos de save.xml
            std::string moneda;
            stringstream ss;  
            ss << monedas_actual;  
            ss >> moneda;

            std::string muertes;
            stringstream ss2;  
            ss2 << muertes_actual;  
            ss2 >> muertes;

            std::string nivel;
            stringstream ss3; 
            ss3 << nivel_actual;
            ss3 >> nivel;

            // Hacemos la consulta
            std::string consult = "UPDATE `usuario` SET `muertes`="+muertes+",`monedas`="+moneda+",`niveles`="+nivel+" WHERE nombre = '"+nombre_actual+"'";
            Conexion::Instance()->update_bd(consult);


            CambiarEstado();
        } else {
            nivel->update(dir_gravedad);
            p1->update(dir_gravedad);
            motor->setCameraCenter(p1->getX(), p1->getY());
            Hud::Instance()->update(nivel->getNumNivel(),dir_gravedad);
        }
        
    }


    // Texto de la animacion inicial
    int n = nivel->getNumNivel();
    std::string mon;
    if(n<6) mon="1";
    else if(n<11){
        mon="2";
        n=n-5;
    }
    else{
        mon="3";
        n=n-10;
    }

    std::stringstream sstream;
    sstream << n;
    std::string text = sstream.str();
    textoNivel->setTexto("Mundo "+mon+" - Nivel "+text);
    textoFondo->setTexto("Mundo "+mon+" - Nivel "+text);
}



void InGame::input(){

    while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        }
    }
    

    p1->setEnMovimiento(false);

    if(motor->isKeyPressedRight())  {
        if(!cambiando_gravedad_volando){
            p1->setMoverDerecha(true);
        }
    }

    if(motor->isKeyPressedLeft()){
        if(!cambiando_gravedad_volando){
            p1->setMoverIzquierda(true);
        }
    }
    if(!cambiando_gravedad_izq && !cambiando_gravedad_drcha){
        if(motor->isKeyPressedNum0())   p1->setHabilidad(0);
        if(motor->isKeyPressedNum1())   p1->setHabilidad(1);
        if(motor->isKeyPressedNum2())   p1->setHabilidad(2);
        if(motor->isKeyPressedNum3())   p1->setHabilidad(3);
        if(motor->isKeyPressedNum4())   p1->setHabilidad(4);
        if(motor->isKeyPressedNum5())   p1->setHabilidad(5);
        if(motor->isKeyPressedSpace())  p1->usarHabilidad();
    }

    if(nivel->getNumNivel()<6){//mecanica mundo 1
        if(motor->getTamHeight()==720)
            motor->setRadioShader((nivel->getNumNivel()+1)*150*0.67);
        else
            motor->setRadioShader((nivel->getNumNivel()+1)*150);

        motor->setShader(true);
        //p1->setWorld2(false);
    }
    else if(nivel->getNumNivel()>5&&nivel->getNumNivel()<11){//mecanica mundo 2
        motor->setShader(false);
        if(mundo2reloj.getElapsedTime().asSeconds() > 5){
            p1->setAtravesarObj(false);
            mundo2reloj.restart();
        }
        else{
            if(motor->isKeyPressedQ()){
                if(!p1->getAtravesarObj()){
                    p1->setAtravesarObj(true);
                    p1->setTiempo_q_activa(5);
                    mundo2reloj.restart();
                }
            }
            if(mundo2reloj.getElapsedTime().asSeconds() > 0 && mundo2reloj.getElapsedTime().asSeconds() < 1){
                p1->setTiempo_q_activa(5);
            }
            else if(mundo2reloj.getElapsedTime().asSeconds() > 1 && mundo2reloj.getElapsedTime().asSeconds() < 2){
                p1->setTiempo_q_activa(4);
            }
            else if(mundo2reloj.getElapsedTime().asSeconds() > 2 && mundo2reloj.getElapsedTime().asSeconds() < 3){
                p1->setTiempo_q_activa(3);
            }
            else if(mundo2reloj.getElapsedTime().asSeconds() > 3 && mundo2reloj.getElapsedTime().asSeconds() < 4){
                p1->setTiempo_q_activa(2);
            }
            else if(mundo2reloj.getElapsedTime().asSeconds() > 4 && mundo2reloj.getElapsedTime().asSeconds() < 5){
                p1->setTiempo_q_activa(1);
            }
            else {
                p1->setTiempo_q_activa(0);
            }
        
        }
        /*if(motor->isKeyPressedQ() && !p1->getAtravesarObj()){
            p1->setAtravesarObj(true);
        }
        else if(motor->isKeyPressedQ() && p1->getAtravesarObj()){
            p1->setAtravesarObj(false);
        }*/
    }
    else if(nivel->getNumNivel()>10){//mecanica mundo 3
        motor->setShader(false);
       // p1->setWorld2(false);
        if(motor->isKeyPressedG()){
            if(!cambiando_gravedad_izq && !cambiando_gravedad_drcha && !p1->getSaltando() && p1->getEnSuelo()){
                cambiando_gravedad_izq = true;
                cambiando_gravedad_volando = true;
                //p1->setSaltando(true);
            }
        }

        if(motor->isKeyPressedF()){
            if(!cambiando_gravedad_izq && !cambiando_gravedad_drcha && !p1->getSaltando() && p1->getEnSuelo()){
                cambiando_gravedad_volando = true;
                cambiando_gravedad_drcha = true;
                //p1->setSaltando(true);
            }
        }
    }
    if(motor->isKeyPressedEscape()){
        if(!cambiando_gravedad_izq && !cambiando_gravedad_drcha && !cambiando_gravedad_volando){
            motor->setShader(false);
            motor->getMusica()->pause();
            motor->getMusicaMenu()->Play();
            Pausa::Instance()->setEstadoAnterior(1);
            Pausa::Instance()->setPrimeraVez(true);
            Hud::Instance()->setRotacion(0);
            p1->reseteaGravedad(true);
            
            Partida::setEstado(Pausa::Instance());
        }
    } 

 

    // Para hacer pruebas si le da a la I salta mucho 
    if(motor->isKeyPressedI()) p1->saltar();
   
    //p1->input();
}

