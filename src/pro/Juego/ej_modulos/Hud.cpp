#include "Hud.h"

Hud* Hud::pinstance = 0;
Hud* Hud::Instance(){
    if(pinstance == 0){
        pinstance = new Hud;

    }
    return pinstance;
}

Hud::Hud(){
    nivel=0;

    posicion = new FlotanteInterpolado();//habilidades
    posicion2 = new FlotanteInterpolado();//nivel
    posicion3 = new FlotanteInterpolado();//reloj
    posicion_moneda = new FlotanteInterpolado();//monedas
    posicion_moneda2 = new FlotanteInterpolado();//monedas
    posicion_moneda3 = new FlotanteInterpolado();//monedas
    posicion_muertes = new FlotanteInterpolado();//muertes
    posicion_calavera = new FlotanteInterpolado();//muertes
    posicion_fondo = new FlotanteInterpolado();//muertes
    
    motor=Motor::Instance();

    fondo=new Sprite();
    fondo->setTexture("FondoHud","png");

    habilidades=new Sprite();
    habilidades->setTexture("HudHab","png");
    habilidades->setFrameSprite(0,0,320,64);

    secreto1=new Sprite();
    secreto1->setTexture("Secreto1No","png");
    secreto1->setScale(0.8,0.8);
    secreto2=new Sprite();
    secreto2->setTexture("Secreto2No","png");
    secreto2->setScale(0.8,0.8);
    secreto3=new Sprite();
    secreto3->setTexture("Secreto5No","png");
    secreto3->setScale(0.8,0.8);

    calavera=new Sprite();
    calavera->setTexture("Muertes","png");
    calavera->setScale(0.9,0.9);


    muertes=new Texto("0");
    muertes->setSize(67);
    muertes->setColor(0,0,0);
   
    x=motor->getCamaraCenter().x-motor->getTamWidth()/2.f;
    y=motor->getCamaraCenter().y-motor->getTamHeight()/2.f;
    if(motor->getTamHeight()==720){
        x=x-128;
        y=y-51;
    }
    else{
        x=x+20;
        y=y+20;
    }

    fondo->setPosition(x,y);
    posicion_fondo->setPositionXY(x, y);

    habilidades->setPosition(x,y);
    posicion->setPositionXY(x, y);

    secreto1->setPosition(motor->getTamWidth()/4, y);
    secreto2->setPosition(motor->getTamWidth()/4, y);
    secreto3->setPosition(motor->getTamWidth()/4, y);
    posicion_moneda->setPositionXY(motor->getTamWidth()/4, y);

    calavera->setPosition(x,y);
    muertes->setPosition(x,y);
    posicion_muertes->setPositionXY(x, y);
    posicion_calavera->setPositionXY(x, y);

    
    texto=new Texto("Nivel");
    texto->setSize(67);
    texto->setColor(0,0,0);
    texto->setPosition(x-motor->getTamWidth()/4.f,y-20);
    posicion2->setPositionXY(x-motor->getTamWidth()/4.f, y-20);

    bloqueo=new Sprite();
    bloqueo->setTexture("bloqueo","png");
    bloqueo->setOrigin(bloqueo->getBounds("global").width/2.f,bloqueo->getBounds("global").height/2.f);
    bloqueo->setPosition(motor->getCamaraCenter().x,motor->getCamaraCenter().y);

    reloj=new Sprite();
    reloj->setTexture("Reloj","png");
    reloj->setPosition(x-motor->getTamWidth()/4.f, y-20);
    posicion3->setPositionXY(x-motor->getTamWidth()/4.f, y-20);

    cont_segundos=new Texto("0");
    cont_segundos->setSize(75);
    cont_segundos->setColor(0,0,0);
    cont_segundos->setPosition(x-motor->getTamWidth()/4.f,y-50);

    


    //posicion4->setPositionXY(x-motor->getTamWidth()/4.f, y-20);
}

Hud::~Hud(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(habilidades!=NULL){
        delete habilidades;
        habilidades=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(secreto1!=NULL){
        delete secreto1;
        secreto1=NULL;
    }
    if(secreto2!=NULL){
        delete secreto2;
        secreto2=NULL;
    }
    if(secreto3!=NULL){
        delete secreto3;
        secreto3=NULL;
    }
    if(reloj!=NULL){
        delete reloj;
        reloj=NULL;
    }
    if(calavera!=NULL){
        delete calavera;
        calavera=NULL;
    }
    if(bloqueo!=NULL){
        delete bloqueo;
        bloqueo=NULL;
    }

    if(posicion!=NULL){
        delete posicion;
        posicion=NULL;
    }
    if(posicion_fondo!=NULL){
        delete posicion_fondo;
        posicion_fondo=NULL;
    }
    if(posicion2!=NULL){
        delete posicion2;
        posicion2=NULL;
    }
    if(posicion3!=NULL){
        delete posicion3;
        posicion3=NULL;
    }
    if(posicion_moneda!=NULL){
        delete posicion_moneda;
        posicion_moneda=NULL;
    }
    if(posicion_moneda2!=NULL){
        delete posicion_moneda2;
        posicion_moneda2=NULL;
    }
    if(posicion_moneda3!=NULL){
        delete posicion_moneda3;
        posicion_moneda3=NULL;
    }
    if(posicion_muertes!=NULL){
        delete posicion_muertes;
        posicion_muertes=NULL;
    }
    if(posicion_calavera!=NULL){
        delete posicion_calavera;
        posicion_calavera=NULL;
    }
    if(texto!=NULL){
        delete texto;
        texto=NULL;
    }
    if(cont_segundos!=NULL){
        delete cont_segundos;
        cont_segundos=NULL;
    } 
    if(muertes!=NULL){
        delete muertes;
        muertes=NULL;
    }
}

void Hud::update(int item, int gravedad){
    nivel=item;
    //Texto mostrado
    std::string mon;

    if(item<6){
        mon="1";
    }
    else if(item<11){
        mon="2";
        item=item-5;
    }
    else{
        mon="3";
        item=item-10;

    }

    std::stringstream sstream;
    sstream << item;
    std::string text = sstream.str();

    texto->setTexto("Mundo "+mon+" - Nivel "+text);

    int tiempo = Player::Instance()->getTiempo_q_activa();
    std::stringstream sstream2;
    sstream2 << tiempo;
    std::string text2 = sstream2.str();
    cont_segundos->setTexto(text2);


    // Actualizamos texto del contador de muertes
    std::string muertes_str;
    std::stringstream ss;
    ss << Guardar::Instance()->getMuertes();
    muertes_str = ss.str();
    muertes->setTexto(muertes_str);
    


    // Sprite de habilidades
    int hab=Guardar::Instance()->getHabilidades();
    habilidades->setFrameSprite(0,hab*64,320,64);

    // Sprite de Secretos
    if(sec1==false&&Guardar::Instance()->getSecreto1()==1){
        secreto1->setTexture("Secreto1","png");
        sec1=true;
    }
    if(sec2==false&&Guardar::Instance()->getSecreto2()==1){
        secreto2->setTexture("Secreto2","png");
        sec2=true;
    }
    if(sec3==false&&Guardar::Instance()->getSecreto3()==1){
        sec3=true;
        secreto3->setTexture("Secreto5","png");
    }

    x=motor->getCamaraCenter().x;
    y=motor->getCamaraCenter().y;

    //habilidades y texto
    float x1=0.f;
    float x2=0.f;
    float y1=0.f;
    float y2=0.f;
    //secretos
    float x3=0.f;
    float y3=0.f;
    float x32=0.f;
    float y32=0.f;
    float x33=0.f;
    float y33=0.f;
    //muertes
    float x4=0.f;
    float y4=0.f;
    float x42=0.f;
    float y42=0.f;
    //fondo
    float x5=0.f;
    float y5=0.f;

    if(gravedad==0){
        
        if(motor->getTamHeight()==720){
            x1=x-128-motor->getTamWidth()/2.f;
            y1=y-70-motor->getTamHeight()/2.f;
            x3=x-motor->getTamWidth()/4.f;
            y3=y1-10;
            x32=x3+100;
            x33=x3+200;
            y32=y3;
            y33=y3;

            x5=x1-70;
            y5=y1-20;

            

        }
        else{
            x1=x+100-motor->getTamWidth()/2.f;
            y1=y+20-motor->getTamHeight()/2.f;
            x3=x+100-motor->getTamWidth()/4.f;
            y3=y1-10;
            x32=x3+100;
            x33=x3+200;
            y32=y3;
            y33=y3;

            x5=x1-110;
            y5=y1-20;
        }
        
        x2=x+motor->getTamWidth()/4.f;
        y2=y1-20;

        x4=x2-210;
        y4=y2;
        
        x42=x4-75;
        y42=y4+20;

  
    }
    else if(gravedad==1){
        if(motor->getTamHeight()==720){
            y1=y-128-motor->getTamWidth()/2.f;
            x1=x+70+motor->getTamHeight()/2.f;
            x5=x1+20;
            y5=y1-70;

            y3=y-motor->getTamWidth()/4.f;
            x3=x1+10;
            y32=y3+100;
            y33=y3+200;
            x32=x3;
            x33=x3;
        }
        else{
            y1=y+100-motor->getTamWidth()/2.f;
            x1=x-20+motor->getTamHeight()/2.f;
            x5=x1+20;
            y5=y1-110;

            y3=y+100-motor->getTamWidth()/4.f;
            x3=x1+10;
            y32=y3+100;
            y33=y3+200;
            x32=x3;
            x33=x3;
        }

        y2=y+motor->getTamWidth()/4.f;
        x2=x1+20;

        x4=x2;
        y4=y2-210;

        x42=x4-20;
        y42=y4-75;
    }
    else if(gravedad==2){
        if(motor->getTamHeight()==720){
            x1=x+128+motor->getTamWidth()/2.f;
            y1=y+70+motor->getTamHeight()/2.f;
            x3=x+motor->getTamWidth()/4.f;
            y3=y1+10;
            x32=x3-100;
            x33=x3-200;
            y32=y3;
            y33=y3;
            x5=x1+70;
            y5=y1+20;
        }
        else{
            x1=x-100+motor->getTamWidth()/2.f;
            y1=y-20+motor->getTamHeight()/2.f;
            x5=x1+110;
            y5=y1+20;

            x3=x-100+motor->getTamWidth()/4.f;
            y3=y1+10;
            x32=x3-100;
            x33=x3-200;
            y32=y3;
            y33=y3;
        }

        x2=x-motor->getTamWidth()/4.f;
        y2=y1+20;

        x4=x2+210;
        y4=y2;

        x42=x4+75;
        y42=y4-20;
        
    }
    else if(gravedad==3){
        if(motor->getTamHeight()==720){
            y1=y+128+motor->getTamWidth()/2.f;
            x1=x-70-motor->getTamHeight()/2.f;

            x5=x1-20;
            y5=y1+70;
            y3=y+motor->getTamWidth()/4.f;
            x3=x1-10;
            y32=y3-100;
            y33=y3-200;
            x32=x3;
            x33=x3;
        }
        else{
            y1=y-100+motor->getTamWidth()/2.f;
            x1=x+20-motor->getTamHeight()/2.f;

            x5=x1-20;
            y5=y1+110;

            y3=y-100+motor->getTamWidth()/4.f;
            x3=x1-10;
            y32=y3-100;
            y33=y3-200;
            x32=x3;
            x33=x3;

        }

        y2=y-motor->getTamWidth()/4.f;
        x2=x1-20;

        x4=x2;
        y4=y2+210;

        x42=x4+20;
        y42=y4+75;
    }

    
    
   

    posicion->setPositionXY(x1, y1);
    posicion2->setPositionXY(x2, y2);
    posicion_moneda->setPositionXY(x3,y3);
    posicion_moneda2->setPositionXY(x32,y32);
    posicion_moneda3->setPositionXY(x33,y33);
    posicion_muertes->setPositionXY(x4,y4);
    posicion_calavera->setPositionXY(x42,y42);
    posicion_fondo->setPositionXY(x5, y5);

    
    if(motor->getTamHeight()==720)
        posicion3->setPositionXY(x+motor->getTamWidth()/2.f, y+motor->getTamHeight()/2.f);
    else
        posicion3->setPositionXY(x-200+motor->getTamWidth()/2.f, y-150+motor->getTamHeight()/2.f);

    //posicion4->setPositionXY(x2, y2);

    bloqueo->setPosition(motor->getCamaraCenter().x,motor->getCamaraCenter().y);
    
}

void Hud::render(float factor, bool mostrarNivel,bool cambiandoGravedad){
    //bool suelo = Player::Instance()->getEnSuelo();
    if(!cambiandoGravedad){
        float interX = (posicion->getX()-posicion->getPrevX()) * factor + posicion->getPrevX();
        float interY = (posicion->getY()-posicion->getPrevY()) * factor + posicion->getPrevY();

        float interX2 = (posicion2->getX()-posicion2->getPrevX()) * factor + posicion2->getPrevX();
        float interY2 = (posicion2->getY()-posicion2->getPrevY()) * factor + posicion2->getPrevY();

        float interX3 = (posicion3->getX()-posicion3->getPrevX()) * factor + posicion3->getPrevX();
        float interY3 = (posicion3->getY()-posicion3->getPrevY()) * factor + posicion3->getPrevY();
        
        float interX4 = (posicion_moneda->getX()-posicion_moneda->getPrevX()) * factor + posicion_moneda->getPrevX();
        float interY4 = (posicion_moneda->getY()-posicion_moneda->getPrevY()) * factor + posicion_moneda->getPrevY();

        float interX5 = (posicion_muertes->getX()-posicion_muertes->getPrevX()) * factor + posicion_muertes->getPrevX();
        float interY5 = (posicion_muertes->getY()-posicion_muertes->getPrevY()) * factor + posicion_muertes->getPrevY();

        float interX6 = (posicion_moneda2->getX()-posicion_moneda2->getPrevX()) * factor + posicion_moneda2->getPrevX();
        float interY6 = (posicion_moneda2->getY()-posicion_moneda2->getPrevY()) * factor + posicion_moneda2->getPrevY();

        float interX7 = (posicion_moneda3->getX()-posicion_moneda3->getPrevX()) * factor + posicion_moneda3->getPrevX();
        float interY7 = (posicion_moneda3->getY()-posicion_moneda3->getPrevY()) * factor + posicion_moneda3->getPrevY();

        float interX8 = (posicion_fondo->getX()-posicion_fondo->getPrevX()) * factor + posicion_fondo->getPrevX();
        float interY8 = (posicion_fondo->getY()-posicion_fondo->getPrevY()) * factor + posicion_fondo->getPrevY();

        float interX9 = (posicion_calavera->getX()-posicion_calavera->getPrevX()) * factor + posicion_calavera->getPrevX();
        float interY9 = (posicion_calavera->getY()-posicion_calavera->getPrevY()) * factor + posicion_calavera->getPrevY();

        if(fondo!=NULL){
            fondo->setPosition(interX8,interY8);
            motor->ventanaDibujaSinShader(fondo->getSprite());
        }
        if(habilidades!=NULL){
            habilidades->setPosition(interX,interY);
            motor->ventanaDibujaSinShader(habilidades->getSprite());
            if(!mostrarNivel){//si se muestra la animacion no se renderiza
                texto->setPosition(interX2,interY2);
                texto->drawText();
            }
        }
   
        if(secreto1!=NULL){
            secreto1->setPosition(interX4,interY4);
            motor->ventanaDibujaSinShader(secreto1->getSprite());
        }
        if(secreto2!=NULL){
            secreto2->setPosition(interX6,interY6);
            motor->ventanaDibujaSinShader(secreto2->getSprite());
        }
        if(secreto3!=NULL){
            secreto3->setPosition(interX7,interY7);
            motor->ventanaDibujaSinShader(secreto3->getSprite());
        }

        if(reloj!=NULL && nivel>5 && nivel<11){//falta añadir condicion de si la q esta activada
            if(Player::Instance()->getAtravesarObj()){
                reloj->setPosition(interX3,interY3);
                motor->ventanaDibujaSinShader(reloj->getSprite());
                cont_segundos->setPosition(interX3-20, interY3-20);
                cont_segundos->drawText();
            }
        }
        if(muertes != NULL){
            muertes->setPosition(interX5,interY5);
            muertes->drawText();
        }
        if(calavera!=NULL){
            calavera->setPosition(interX9,interY9);
            motor->ventanaDibujaSinShader(calavera->getSprite());
        }
    }
    else{
        if(bloqueo!=NULL)
            motor->ventanaDibujaSinShader(bloqueo->getSprite());
    }
    
}

void Hud::setRotacion(float rot){
    if(habilidades!=NULL){
        habilidades->setRotation(rot);
        texto->setRotation(rot);
        secreto1->setRotation(rot);
        secreto2->setRotation(rot);
        secreto3->setRotation(rot);
        fondo->setRotation(rot);
        muertes->setRotation(rot);
        calavera->setRotation(rot);
    }
    
}