#include "Texto.h"

Texto::Texto(){
    texto=NULL;
    fuente=NULL;
}

Texto::~Texto(){
    if(texto!=NULL){
        delete texto;
        texto=NULL;
    }
    if(fuente!=NULL){
        delete fuente;
        fuente=NULL;
    }
}

Texto::Texto(std::string cad){
    texto = new sf::Text;
    fuente=NULL;
    m = Motor::Instance();
    if(cad.size()>0){
        texto->setString(cad);
    }
    this->setFuente("aAnekdot.ttf");
    this->setColor(255,255,255);
    this->setSize(14);
}

void Texto::setFuente(std::string f){
    fuente = new sf::Font;
    if(!fuente->loadFromFile("resources/fonts/" + f))
        exit(1);
    texto->setFont(*fuente);
    if(f.size()>0){
        font_name = f;
    }
}

void Texto::setSize(int tam){
    texto->setCharacterSize(tam);
}

void Texto::setPosition(float x, float y){
    texto->setPosition(sf::Vector2f(x,y));
}

void Texto::setRotation(float a){
    texto->setRotation(a);
}

void Texto::setOrigin(float x, float y){
    texto->setOrigin(x,y);
}

void Texto::drawText(){
    m->ventanaDibuja(*texto);
}

void Texto::setColor(int r, int g, int b){
    texto->setColor(sf::Color(r,g,b));
}

void Texto::setColor(int r, int g, int b, int a){
    texto->setColor(sf::Color(r,g,b,a));
}

void Texto::setColor(std::string color){
    sf::Color c = sf::Color::White;
    if(strcmp(color.data(), "red")==0){
        c = sf::Color::Red;
    }else if(strcmp(color.data(), "blue")==0){
        c = sf::Color::Blue;
    }else if(strcmp(color.data(), "black")==0){
        c = sf::Color::Black;
    }else if(strcmp(color.data(), "yellow")==0){
        c = sf::Color::Yellow;
    }else if(strcmp(color.data(), "green")==0){
        c = sf::Color::Green;
    }else if(strcmp(color.data(), "cyan")==0){
        c = sf::Color::Cyan;
    }else if(strcmp(color.data(), "magenta")==0){
        c = sf::Color::Magenta;
    }else if(strcmp(color.data(), "transparent")==0){
        c = sf::Color::Transparent;
    }
    texto->setColor(c);
}

void Texto::setStyle(std::string estilo){
    if(strcmp(estilo.data(), "Underlined")==0)
        texto->setStyle(sf::Text::Underlined);
    else if(strcmp(estilo.data(), "Regular")==0)
        texto->setStyle(sf::Text::Regular);
}

std::string Texto::getTexto(){
    return texto->getString();
}

std::string Texto::getFuente(){
    if(fuente != NULL){
        return font_name;
    }else{
        return "No tiene aplicada ninguna fuente";
    }
}

float Texto::getXPosition(){
    return texto->getPosition().x;
}

float Texto::getYPosition(){
    return texto->getPosition().y;
}
float Texto::getRotation(){
    return texto->getRotation();
}

float Texto::getXOrigin(){
    return texto->getOrigin().x;
}

float Texto::getYOrigin(){
    return texto->getOrigin().y;
}

float Texto::getWidthBounds(){
    return texto->getGlobalBounds().width;
}
float Texto::getHeightBounds(){
    return texto->getGlobalBounds().height;
}
sf::FloatRect Texto::getGlobalBounds(){
    return texto->getGlobalBounds();
}

float Texto::getSize(){
    return texto->getCharacterSize();
}