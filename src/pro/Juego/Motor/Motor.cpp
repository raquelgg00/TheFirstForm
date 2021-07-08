#include "Motor.h"
#include <iostream>

// Singleton
Motor* Motor::pinstance = 0;
Motor* Motor::Instance(){
    if(pinstance == 0){
        pinstance = new Motor;

    }
    return pinstance;
}

// Constructor
Motor::Motor(){
    Guardar *guardar=Guardar::Instance();

    if(guardar->getResolucion()==720){
        tamWidth = 1280;
        tamHeight = 720;
    }
    else{
        tamWidth = 1920;
        tamHeight = 1080;
    }

    new_ventana(tamWidth,tamHeight,"The First Shape");

    //añadimos favicon
    favicon.loadFromFile("resources/texturas/0.png");
    ventana1->setIcon(favicon.getSize().x,favicon.getSize().y,favicon.getPixelsPtr());

    setFramerateLimit(60);
    //camara = new sf::View(sf::Vector2f(0,0), sf::Vector2f(1920,1080));

    deltaTime=0.0;

    // Esto lo pongo asi para que se vea todo el mapa, luego se quita la linea de abajo y se descomenta la de arriba ZOOM
    //camara = new sf::View(sf::Vector2f(0,0), sf::Vector2f(TAM_WIDTH*3.25,TAM_HEIGHT*3.25));
    camara=NULL;
    if(tamHeight==720)
        camara = new sf::View(sf::Vector2f(0,0), sf::Vector2f(tamWidth*1.25,tamHeight*1.25));
    else
        camara = new sf::View(sf::Vector2f(0,0), sf::Vector2f(tamWidth,tamHeight));

    camara2 = new sf::View(sf::Vector2f(0,0), sf::Vector2f(tamWidth,tamHeight));
    camara2->setCenter(tamWidth/2,tamHeight/2);

    

    musica=new Audio();
    musica->setBuffer("resources/sounds/musica.wav");
    musica->setVolume(guardar->getMusica());
    musica->SetLoop(true);


    musicaMenu=new Audio();
    musicaMenu->setBuffer("resources/sounds/menu.wav");
    musicaMenu->setVolume(guardar->getMusica());
    musicaMenu->SetLoop(true);

    musicaAnimacion = new Audio();
    musicaAnimacion->setBuffer("resources/sounds/AudioAnimacionInicial.wav");
    musicaAnimacion->setVolume(Guardar::Instance()->getMusica());
    musicaAnimacion->SetLoop(true);

    sonidoSeleccion=new Audio();
    sonidoSeleccion->setBuffer("resources/sounds/seleccion.wav");
    sonidoSeleccion->setVolume(guardar->getSonido());

    sonidoMover=new Audio();
    sonidoMover->setBuffer("resources/sounds/moverse_por_el_menu.wav");
    sonidoMover->setVolume(guardar->getSonido());

    sonidoMorision=new Audio();
    sonidoMorision->setBuffer("resources/sounds/morision.wav");
    sonidoMorision->setVolume(guardar->getSonido());

    sonidoInicio=new Audio();
    sonidoInicio->setBuffer("resources/sounds/intro.wav");
    sonidoInicio->setVolume(guardar->getMusica());
    sonidoInicio->SetLoop(true);

    sonidoEvolucion=new Audio();
    sonidoEvolucion->setBuffer("resources/sounds/evolusion.wav");
    sonidoEvolucion->setVolume(guardar->getSonido());

    sonidoNivelCompletado=new Audio();
    sonidoNivelCompletado->setBuffer("resources/sounds/completado.wav");
    sonidoNivelCompletado->setVolume(guardar->getSonido());

    playercoord.x = 0;
    playercoord.y = 0;
    if(!shaderM.loadFromFile("Motor/shaders/shadermotor.frag", sf::Shader::Fragment)){
            std::cerr << "Error al cargar el shader\n";
    }

}

// Destructor
Motor::~Motor(){
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }
    if(ventana1 != NULL){
        delete ventana1;
        ventana1=NULL;
    }
    if(camara != NULL){
        delete camara;
        camara = NULL;
    }
    if(camara2 != NULL){
        delete camara2;
        camara2 = NULL;
    }
    if(musica != NULL){
        delete musica;
        musica = NULL;
    }
    if(musicaMenu != NULL){
        delete musicaMenu;
        musicaMenu = NULL;
    }
    if(musicaAnimacion != NULL){
        delete musicaAnimacion;
        musicaAnimacion = NULL;
    }
    if(sonidoMover != NULL){
        delete sonidoMover;
        sonidoMover = NULL;
    }
    if(sonidoSeleccion != NULL){
        delete sonidoSeleccion;
        sonidoSeleccion = NULL;
    }
    if(sonidoInicio != NULL){
        delete sonidoInicio;
        sonidoInicio = NULL;
    }
    if(sonidoMorision != NULL){
        delete sonidoMorision;
        sonidoMorision = NULL;
    }
    if(sonidoEvolucion != NULL){
        delete sonidoEvolucion;
        sonidoEvolucion = NULL;
    }
    if(sonidoNivelCompletado != NULL){
        delete sonidoNivelCompletado;
        sonidoNivelCompletado = NULL;
    }
    if(event!=NULL){
        delete event;
        event=NULL;
    }
}

// Crea una ventana
void Motor::new_ventana(int n1, int n2, sf::String s){
    ventana1 = new sf::RenderWindow(sf::VideoMode(n1, n2), s, sf::Style::Close);
}

void Motor::setSizeVentana(int width,int height){
    tamWidth=width;
    tamHeight=height;
    ventana1->setSize(sf::Vector2u(tamWidth, tamHeight));
}
// Crea y devuelve un color
sf::Color Motor::new_color(int n1, int n2, int n3){
    return sf::Color(n1,n2,n3);
}

// Establece maximo de fps. Así un PC muy rápido no ejecutará más veces por segundo el render
void Motor::setFramerateLimit(int fps){
    ventana1->setFramerateLimit(fps);
}

// Devuelve true si la ventana está abierta
bool Motor::ventanaIsOpen(){
    return ventana1->isOpen();
}

// Borra la ventana (fondo negro)
void Motor::ventanaClear(){
    ventana1->clear();
}

// Borra la ventana (fondo del color RGB que le pasemos)
void Motor::ventanaClear(int n1, int n2, int n3){
    ventana1->clear(sf::Color(n1,n2,n3));
}

// Cierra la ventana
void Motor::ventanaClose(){
    ventana1->close();
    exit(0);
}

// Dibuja un Sprite en la ventana
void Motor::ventanaDibuja(sf::Sprite sprite){
    if (!useShader)
        ventana1->draw(sprite);
    else{
        sf::Vector2f viewport_coords = static_cast<sf::Vector2f>(ventana1->mapCoordsToPixel(playercoord));
        shaderM.setParameter("userCoor", viewport_coords);
        shaderM.setParameter("texture", sf::Shader::CurrentTexture);
        shaderM.setParameter("radius", radio);
        ventana1->draw(sprite, &shaderM);
    }
}

// Dibuja un Sprite en la ventana
void Motor::ventanaDibujaSinShader(sf::Sprite sprite){
    ventana1->draw(sprite);
}

// Dibuja un Texto en la ventana
void Motor::ventanaDibuja(sf::Text text){
        ventana1->draw(text);
}

// Dibuja un RectangleShape en la ventana
void Motor::ventanaDibuja(sf::RectangleShape shape){
    if (!useShader)
        ventana1->draw(shape);
    else{
        sf::Vector2f viewport_coords = static_cast<sf::Vector2f>(ventana1->mapCoordsToPixel(playercoord));
        shaderM.setParameter("userCoor", viewport_coords);
        shaderM.setParameter("texture", sf::Shader::CurrentTexture);
        shaderM.setParameter("radius", radio);
        ventana1->draw(shape, &shaderM);
    }
}

void Motor::ventanaDibuja(sf::CircleShape shape){
    if (!useShader)
        ventana1->draw(shape);
    else{
        sf::Vector2f viewport_coords = static_cast<sf::Vector2f>(ventana1->mapCoordsToPixel(playercoord));
        shaderM.setParameter("userCoor", viewport_coords);
        shaderM.setParameter("texture", sf::Shader::CurrentTexture);
        shaderM.setParameter("radius", radio);
        ventana1->draw(shape, &shaderM);
    }
}

void Motor::ventanaDibuja(sf::ConvexShape shape){
    if (!useShader)
        ventana1->draw(shape);
    else{;
        sf::Vector2f viewport_coords = static_cast<sf::Vector2f>(ventana1->mapCoordsToPixel(playercoord));
        shaderM.setParameter("userCoor", viewport_coords);
        shaderM.setParameter("texture", sf::Shader::CurrentTexture);
        shaderM.setParameter("radius", radio);
        ventana1->draw(shape, &shaderM);
    }
}

// Muestra la ventana
void Motor::ventanaDisplay(){
    ventana1->display();
}

// Recoger eventos
bool Motor::ventanaPollEvent(){
    event = new sf::Event();
    return ventana1->pollEvent(*event);
}

// Evento de cuando se cierra la ventana
bool Motor::eventTypeClosed(){
    return event->type == sf::Event::Closed;
}

// Crea y devuelve un RectangleShape
sf::RectangleShape Motor::crearRectangleShape(float f1, float f2){
    return sf::RectangleShape(sf::Vector2f(f1,f2));
}

// Usamos la camara
void Motor::setView(int cam){
    if(cam==1)
        ventana1->setView(*camara);
    else
        ventana1->setView(*camara2);
}

// Centramos la camara para que el centro esté en el X,Y que le pasemos
void Motor::setCameraCenter(float x, float y){
    camara->setCenter(x, y);
}

void Motor::setCamaraRotation(float n){
    camara->setRotation(n);
}

bool Motor::colisionAbajo(int x, int y, int width, int height, int xPlayer, int yPlayer, int widthPlayer, int heightPlayer, bool cambia_margen){

    float margen=25.f;
    if(cambia_margen) margen=10.f;
    // Usamos dx para comparar toda la arista del personaje por abajo 
    // Si algun punto de los de esta arista colisiona con la plataforma devolvemos true
    int x_izq_player = xPlayer - widthPlayer/2.f;

    if(yPlayer+heightPlayer/2.f>y&&yPlayer<y+height){
        for(int dx=x_izq_player+margen; dx<x_izq_player+widthPlayer-margen; dx+=5){
            if(dx>x && dx<x+width){
                return true;
            }
        }
    }
    return false;
}

bool Motor::colisionArriba(int x, int y, int width, int height, int xPlayer, int yPlayer, int widthPlayer, int heightPlayer, bool es_pincho, bool cambia_margen){
    float margen=25.f;
    if(cambia_margen) margen=10.f;
    // Usamos dx para comparar toda la arista del personaje por abajo 
    // Si algun punto de los de esta arista colisiona con la plataforma devolvemos true
    int x_izq_player = xPlayer - widthPlayer/2.f;

    if(yPlayer-heightPlayer/2.f>y&&yPlayer-heightPlayer/2.f<y+height){ 
    for(int dx=x_izq_player+margen; dx<x_izq_player+widthPlayer-margen; dx+=5){
        if(dx>x && dx<x+width){
                if(es_pincho){
                    if(dx>x+10 && dx<x+width-10){//pincho
                        return true;
                    }
                } 
                return true;
            }
        }
    }
    return false;
}


bool Motor::colisionIzq(int x, int y, int width, int height, int xPlayer, int yPlayer, int widthPlayer, int heightPlayer, bool cambia_margen){
    
    float margen=10.f;
    if(cambia_margen) margen=25.f;

    int y_arriba_player = yPlayer - heightPlayer/2.f;

    if(xPlayer-widthPlayer/2.f>x && xPlayer-widthPlayer/2.f<x+width){
        for(int dy=y_arriba_player+margen; dy<y_arriba_player+heightPlayer-margen; dy+=5){
            if(dy>y && dy<y+height){
                return true;
            }
        }
    }
    return false;
}


bool Motor::colisionDerecha(int x, int y, int width, int height, int xPlayer, int yPlayer, int widthPlayer, int heightPlayer, bool cambia_margen){

    float margen=10.f;
    if(cambia_margen) margen=25.f;

    int y_arriba_player = yPlayer - heightPlayer/2.f;
      
    if(xPlayer+widthPlayer/2.f>x && xPlayer+widthPlayer/2.f<x+width){ 
        for(int dy=y_arriba_player+margen; dy<y_arriba_player+heightPlayer-margen; dy+=5){
            if(dy>y && dy<y+height){
                return true;
            }
        }
    } 
    return false;
}