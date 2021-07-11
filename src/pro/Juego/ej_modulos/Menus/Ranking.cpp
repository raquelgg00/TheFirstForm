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
    fondo->setTexture("Creditos","png");
    if(motor->getTamHeight()==720){
        fondo->setScale(0.67,0.67);
    }

    //Fondo del menu
    logo=new Sprite();
    logo->setTexture("Logo1","png");
    logo->setOrigin(logo->getBounds("global").width/2.f, logo->getBounds("global").height/2.f);

    logo->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10));
    if(motor->getTamHeight()==720)
        logo->setScale(0.15,0.15);
    else
        logo->setScale(0.22,0.22);
   

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
        if(motor->getTamHeight()==720){
            nombres[i]->setSize(45);

        }
        else
            nombres[i]->setSize(67);

        nombres[i]->setOrigin(nombres[i]->getWidthBounds()/2.f, nombres[i]->getHeightBounds()/2.f);
        nombres[i]->setPosition(motor->getTamWidth()/3.5, (motor->getTamHeight()/5) + i*50);
        nombres[i]->setColor(255,255,255);
    }
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
}


void Ranking::CambiarEstado(){ // Cuando seleccionamos una opcion, cambiamos a InGame.cpp
//reseteo creditos y luego cambio
    logo->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(10));

    for(int i=0;i<num_items;i++){
        nombres[i]->setPosition(motor->getTamWidth()/2, (motor->getTamHeight()/10)*(i+12));
    }
    Partida::setEstado(MenuPrincipal::Instance());
}

void Ranking::render(float tick){
    tick = 0.f;
    motor->ventanaClear(140,140,140);
    motor->ventanaDibuja(fondo->getSprite());

    motor->ventanaDibuja(logo->getSprite());
    for(int i=0;i<num_items;i++){
        nombres[i]->drawText();
    }
    motor->setView(0);
    motor->ventanaDisplay();
}

void Ranking::update(){
    //logo->setPosition(logo->getXPosition(),logo->getYPosition()-2);
    for(int i=0;i<num_items;i++){
        //nombres[i]->setPosition(nombres[i]->getXPosition(),nombres[i]->getYPosition()-2);
    }
    //if(nombres[5]->getYPosition()<-45){
        //CambiarEstado();
    //}
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
        stringstream ss;  
        ss << i+1;  
        ss >> pos_ranking;
        pos_ranking = pos_ranking + ". "+res[i][0]+"            "+res[i][3]+" niveles"+"   ----   "+res[i][2]+" secretos "+"   ----   "+res[i][1]+" muertes ";

        std::cout<<res[i][0]<<" --> "<<res[i][1]<<std::endl;
        nombres[i]->setTexto(pos_ranking);

        if(res[i][0] == Guardar::Instance()->getNombre()){
            nombres[i]->setColor(255,230,0);
        }
            
    }
}

