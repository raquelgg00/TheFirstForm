#include "Ranking.h"


// Singleton 
Ranking* Ranking::pinstance = 0;
Ranking* Ranking::Instance(){
    if(pinstance == 0){
        pinstance = new Ranking;

    }
    return pinstance;
}

// Constructor
Ranking::Ranking(){

    // Motor
    motor = Motor::Instance();
    
    //Fondo del menu
    fondo=new Sprite();
    fondo->setTexture("Ranking","png");
    fondo2=new Sprite();
    fondo2->setTexture("RankingError","png");
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
        fondo2->setScale(0.67,0.67);
    }


    //Inicializamos los textos de las opciones
    nombres[0]=new Texto("Bot");
    nombres[1]=new Texto("Bot");
    nombres[2]=new Texto("Bot");
    nombres[3]=new Texto("Bot");
    nombres[4]=new Texto("Bot");
    nombres[5]=new Texto("Bot");
    nombres[6]=new Texto("Bot");
    nombres[7]=new Texto("Bot");
    nombres[8]=new Texto("Bot");
    nombres[9]=new Texto("Bot");
    
    for(int i=0;i<num_items;i++){
        niveles[i]=new Texto("Bot");
        monedas[i]=new Texto("Bot");
        muertes[i]=new Texto("Bot");
        if(motor->getTamHeight()==720){
            nombres[i]->setSize(45);
            niveles[i]->setSize(45);
            monedas[i]->setSize(45);
            muertes[i]->setSize(45);
        }
        else{
            nombres[i]->setSize(67);
            niveles[i]->setSize(67);
            monedas[i]->setSize(67);
            muertes[i]->setSize(67);
        }

        nombres[i]->setOrigin(nombres[i]->getWidthBounds()/2.f, nombres[i]->getHeightBounds()/2.f);
        nombres[i]->setPosition(motor->getTamWidth()/6, (motor->getTamHeight()/5) + i*50);
        nombres[i]->setColor(255,255,255);

        niveles[i]->setOrigin(niveles[i]->getWidthBounds()/2.f, niveles[i]->getHeightBounds()/2.f);
        niveles[i]->setPosition((motor->getTamWidth()/6), (motor->getTamHeight()/5) + i*50);
        niveles[i]->setColor(255,255,255);

        monedas[i]->setOrigin(monedas[i]->getWidthBounds()/2.f, monedas[i]->getHeightBounds()/2.f);
        monedas[i]->setPosition((motor->getTamWidth()/6), (motor->getTamHeight()/5) + i*50);
        monedas[i]->setColor(255,255,255);

        muertes[i]->setOrigin(muertes[i]->getWidthBounds()/2.f, muertes[i]->getHeightBounds()/2.f);
        muertes[i]->setPosition((motor->getTamWidth()/6), (motor->getTamHeight()/5) + i*50);
        muertes[i]->setColor(255,255,255);

    }

    miResult=new Texto("Bot");
    if(motor->getTamHeight()==720){
            miResult->setSize(45);
        }
        else{
            miResult->setSize(67);
        }
    miResult->setOrigin(miResult->getWidthBounds()/2.f, miResult->getHeightBounds()/2.f);
    miResult->setPosition(motor->getTamWidth()/6, (motor->getTamHeight()/5)+11*40-20);
    miResult->setColor(255,230,0);


    actualiza_ranking();
}


// Destructor
Ranking::~Ranking(){
    if(pinstance!=NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(fondo!=NULL){
        delete fondo;
        fondo=NULL;
    }
    if(fondo2!=NULL){
        delete fondo2;
        fondo2=NULL;
    }
    if(miResult!=NULL){
        delete miResult;
        miResult=NULL;
    }
    for(int i=0;i<num_items;i++){
        if(nombres[i]!=NULL){
            delete nombres[i];
            nombres[i]=NULL;
        }
        if(niveles[i]!=NULL){
            delete niveles[i];
            niveles[i]=NULL;
        }
        if(monedas[i]!=NULL){
            delete monedas[i];
            monedas[i]=NULL;
        }
        if(muertes[i]!=NULL){
            delete muertes[i];
            muertes[i]=NULL;
        }
    }
}


void Ranking::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
//reseteo creditos y luego cambio

    Partida::setEstado(MenuPrincipal::Instance());
}

void Ranking::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    

    if(Conexion::Instance()->getConexion()){
        motor->ventanaDibuja(fondo->getSprite());
        for(int i=0;i<num_items;i++){
            nombres[i]->drawText();
            niveles[i]->drawText();
            monedas[i]->drawText();
            muertes[i]->drawText();
        }

        miResult->drawText();
    }
    else{
        motor->ventanaDibuja(fondo2->getSprite());

    }
    motor->setView(0);
    motor->ventanaDisplay();
}

void Ranking::update(){
}

void Ranking::input(){
  
      while(motor->ventanaPollEvent()) {
        if(motor->eventTypeClosed()){
            motor->ventanaClose();
        } 
       
        if (motor->getEvent()->type == sf::Event::TextEntered){
            Partida::setEstado(MenuPrincipal::Instance());
        }
    }    
}

void Ranking::actualiza_ranking(){

    std::string consult = "select * from usuario order by niveles desc, monedas desc, muertes limit 10";
    std::string** res = Conexion::Instance()->select_bd(consult, 10); 

    for(int i=0; i<10; i++){
        
        string pos_ranking;
        string pos_nivel;
        string pos_secretos;
        string pos_muertes;
        stringstream ss;  
        ss << i+1;  
        ss >> pos_ranking;
        //pos_ranking = pos_ranking + ". "+res[i][0]+"            "+res[i][3]+" niveles"+"   ----   "+res[i][2]+" secretos "+"   ----   "+res[i][1]+" muertes ";
        
        pos_ranking = pos_ranking + ". "+res[i][0];
        /*while(pos_ranking.length()<20){
            pos_ranking = pos_ranking + " ";
        }
        pos_ranking += res[i][3]+" niveles"+"   ----   "+res[i][2]+" secretos "+"   ----   "+res[i][1]+" muertes ";
*/      
        pos_nivel=res[i][3]+" niveles";
        pos_secretos=res[i][2]+" secretos";
        pos_muertes=res[i][1]+" muertes";

        std::cout<<res[i][0]<<" --> "<<res[i][1]<<std::endl;
        nombres[i]->setTexto(pos_ranking);
        niveles[i]->setTexto(pos_nivel);
        monedas[i]->setTexto(pos_secretos);
        muertes[i]->setTexto(pos_muertes);

        if(Guardar::Instance()->getResolucion()==720){
            nombres[i]->setPosition(40+(motor->getTamWidth()/6), (motor->getTamHeight()/5) + i*40-20);
            niveles[i]->setPosition(80+(motor->getTamWidth()/6)*2, (motor->getTamHeight()/5) + i*40-20);
            monedas[i]->setPosition(80+(motor->getTamWidth()/6)*3, (motor->getTamHeight()/5) + i*40-20);
            muertes[i]->setPosition(80+(motor->getTamWidth()/6)*4, (motor->getTamHeight()/5) + i*40-20);
        }
        else{
            nombres[i]->setPosition(60+(motor->getTamWidth()/6), (motor->getTamHeight()/5) + i*50);
            niveles[i]->setPosition(100+(motor->getTamWidth()/6)*2, (motor->getTamHeight()/5) + i*50);
            monedas[i]->setPosition(100+(motor->getTamWidth()/6)*3, (motor->getTamHeight()/5) + i*50);
            muertes[i]->setPosition(100+(motor->getTamWidth()/6)*4, (motor->getTamHeight()/5) + i*50);
        }

        if(res[i][0] == Guardar::Instance()->getNombre()){
            nombres[i]->setColor(255,230,0);
            niveles[i]->setColor(255,230,0);
            monedas[i]->setColor(255,230,0);
            muertes[i]->setColor(255,230,0);
        }
        else {
            nombres[i]->setColor(255,255,255);
            niveles[i]->setColor(255,255,255);
            monedas[i]->setColor(255,255,255);
            muertes[i]->setColor(255,255,255);
        }
            
    }
    
    std::string consult2 = "select niveles as nivelesMio, monedas as monedasMio, muertes as muertesMio, (select count(*) from usuario where (nombre != '"+Guardar::Instance()->getNombre()+"') AND ( (niveles>=nivelesMio) OR (niveles=nivelesMio AND monedas>=monedasMio) OR (niveles=nivelesMio AND monedas=monedasMio AND muertes<=muertesMio))) as position from usuario where nombre='"+Guardar::Instance()->getNombre()+"' order by niveles desc, monedas desc, muertes";

    std::string** res2 = Conexion::Instance()->select_bd(consult2, 1);
    string pos_mio=res2[0][3]+". "+Guardar::Instance()->getNombre()+"          "+res2[0][0]+" niveles         "+res2[0][1]+" monedas         "+res2[0][1]+" muertes";
    miResult->setTexto(pos_mio);
    miResult->setPosition(40+(motor->getTamWidth()/6), (motor->getTamHeight()/5)+10*40);
    if(Guardar::Instance()->getResolucion()==720){
        miResult->setPosition(40+(motor->getTamWidth()/6), (motor->getTamHeight()/5)+10*40);
    }
    else{
        miResult->setPosition(60+(motor->getTamWidth()/6), (motor->getTamHeight()/5)+10*50+100);
    }
}

