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
    
    motor=Motor::Instance();

    habilidades=new Sprite();
    habilidades->setTexture("HudHab","png");
    habilidades->setFrameSprite(0,0,320,64);
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
    habilidades->setPosition(x,y);
    posicion->setPositionXY(x, y);
    
    texto=new Texto("Nivel");
    texto->setSize(67);
    texto->setColor(0,0,0);
    texto->setPosition(x-motor->getTamWidth()/4.f,y-20);
    posicion2->setPositionXY(x-motor->getTamWidth()/4.f, y-20);
    textoFondo=new Texto("Nivel");
    textoFondo->setSize(70);
    textoFondo->setColor(255,255,255);
    textoFondo->setPosition(x-motor->getTamWidth()/4.f,y-20);

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
    if(reloj!=NULL){
        delete reloj;
        reloj=NULL;
    }
    if(bloqueo!=NULL){
        delete bloqueo;
        bloqueo=NULL;
    }

    if(posicion!=NULL){
        delete posicion;
        posicion=NULL;
    }

    if(posicion2!=NULL){
        delete posicion2;
        posicion2=NULL;
    }
    if(posicion3!=NULL){
        delete posicion3;
        posicion3=NULL;
    }
    if(texto!=NULL){
        delete texto;
        texto=NULL;
    }
    if(textoFondo!=NULL){
        delete textoFondo;
        textoFondo=NULL;
    }
    if(cont_segundos!=NULL){
        delete cont_segundos;
        cont_segundos=NULL;
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
    textoFondo->setTexto("Mundo "+mon+" - Nivel "+text);

    int tiempo = Player::Instance()->getTiempo_q_activa();
    std::stringstream sstream2;
    sstream2 << tiempo;
    std::string text2 = sstream2.str();
    cont_segundos->setTexto(text2);


    //Sprite
    int hab=Guardar::Instance()->getHabilidades();
    habilidades->setFrameSprite(0,hab*64,320,64);

    x=motor->getCamaraCenter().x;
    y=motor->getCamaraCenter().y;

    float x1=0.f;
    float x2=0.f;
    float y1=0.f;
    float y2=0.f;
    
    if(gravedad==0){
        
        if(motor->getTamHeight()==720){
            x1=x-128-motor->getTamWidth()/2.f;
            y1=y-51-motor->getTamHeight()/2.f;
        }
        else{
            x1=x+100-motor->getTamWidth()/2.f;
            y1=y+20-motor->getTamHeight()/2.f;
        }
        
        x2=x+motor->getTamWidth()/4.f;
        y2=y1-20;
        
    }
    else if(gravedad==1){
        if(motor->getTamHeight()==720){
            y1=y-128-motor->getTamWidth()/2.f;
            x1=x+51+motor->getTamHeight()/2.f;
        }
        else{
            y1=y+100-motor->getTamWidth()/2.f;
            x1=x-20+motor->getTamHeight()/2.f;
        }

        y2=y+motor->getTamWidth()/4.f;
        x2=x1+20;
    }
    else if(gravedad==2){
        if(motor->getTamHeight()==720){
            x1=x+128+motor->getTamWidth()/2.f;
            y1=y+51+motor->getTamHeight()/2.f;
        }
        else{
            x1=x-100+motor->getTamWidth()/2.f;
            y1=y-20+motor->getTamHeight()/2.f;
        }

        x2=x-motor->getTamWidth()/4.f;
        y2=y1+20;
    }
    else if(gravedad==3){
        if(motor->getTamHeight()==720){
            y1=y+128+motor->getTamWidth()/2.f;
            x1=x-51-motor->getTamHeight()/2.f;
        }
        else{
            y1=y-100+motor->getTamWidth()/2.f;
            x1=x+20-motor->getTamHeight()/2.f;
        }

        y2=y-motor->getTamWidth()/4.f;
        x2=x1-20;
    }

    posicion->setPositionXY(x1, y1);
    posicion2->setPositionXY(x2, y2);
    
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
        
        
        if(habilidades!=NULL){
            habilidades->setPosition(interX,interY);
            motor->ventanaDibujaSinShader(habilidades->getSprite());
            if(!mostrarNivel){//si se muestra la animacion no se renderiza
                textoFondo->setPosition(interX2-7,interY2-5);
                textoFondo->drawText();
                texto->setPosition(interX2,interY2);
                texto->drawText();
                
            }
        }
        if(reloj!=NULL && nivel>5 && nivel<11){//falta añadir condicion de si la q esta activada
            if(Player::Instance()->getAtravesarObj()){
                reloj->setPosition(interX3,interY3);
                motor->ventanaDibujaSinShader(reloj->getSprite());
                cont_segundos->setPosition(interX3-20, interY3-20);
                cont_segundos->drawText();
            }
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
        textoFondo->setRotation(rot);
    }
    
}