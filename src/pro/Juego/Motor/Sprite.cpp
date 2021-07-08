#include "Sprite.h"

// Constructor
Sprite::Sprite(){
    texture_applied=false;
    textura = new sf::Texture;
    sprite = new sf::Sprite;
}

// Destructor
Sprite::~Sprite(){
    if(textura != NULL){
        delete textura;
        textura=NULL;
    }
    if(sprite != NULL){
        delete sprite;
        sprite=NULL;
    }
}

//Establecemos la textura del sprite, devuelve true si la aplica y false si no. Le pasamos el nombre del archivo y la extensión, de esta manera, "nombre", "png".
bool Sprite::setTexture(std::string filename, std::string extension){
    
    std::string path = "resources/texturas/";

    if(!textura->loadFromFile(path + filename + "." + extension))
    {
        exit(0);
        return false;
    }else{
        if(sprite != NULL){
            sprite->setTexture(*textura);
            texture_applied=true;
            return true;
        }
        else {
            return false;
        }
    }
}

//Seleccionamos que sprite de la textura queremos, introduciendo la posición en 'x', 'y' y el tamaño del sprite para x e y
bool Sprite::setFrameSprite(int x, int y, int tamx, int tamy){  
    if(texture_applied == true){
        sprite->setTextureRect(sf::IntRect(x, y, tamx, tamy));
        return true;
    }else{
        return false;
    }
}

void Sprite::setAnimation(int i, int x, int y, int tam_x, int tam_y){
    x=0;
    y=0;
    int current_coin_frame = 0;
    sf::Clock clock;   

    if(clock.getElapsedTime().asSeconds() > 0.1f){
        if(current_coin_frame==i){
          current_coin_frame = 0;
        }else{
          current_coin_frame++;
        }
        this->getSprite().setTextureRect(sf::IntRect( current_coin_frame * tam_x, y, tam_x, tam_y));
        clock.restart();
    }
}

//Establecemos la posicion del sprite, pasándole el posición en x y en y (Ambos en formato <float>)
void Sprite::setPosition(float x, float y){
    sprite->setPosition(x,y);
}

//Establecemos la escale del sprite, pasandole la x y la y (AMbos en formato <float>)
void Sprite::setScale(float x, float y){
    sprite->setScale(x, y);
}

//EStablecemos la rotación del sprite, le pasamos el ángulo
void Sprite::setRotation(float angle){
    sprite->setRotation(angle);
}

//Devuelve las colisiones del objeto, le pasamos un string donde indicamos si queremos las locales o las Globales.
sf::FloatRect Sprite::getBounds(const char type[]){
    if(strcmp( type, "local" ) == 0){
        return sprite->getLocalBounds();
    }else if(strcmp( type, "global" ) == 0){
        return sprite->getGlobalBounds();
    }
    return sprite->getGlobalBounds();
}

//Devuelve la posición en x del sprite
float Sprite::getXPosition(){
    return sprite->getPosition().x;
}

//Devuelve la posicion en y del sprite
float Sprite::getYPosition(){
    return sprite->getPosition().y;
}

float Sprite::getXOrigin(){
    return sprite->getOrigin().x;
}

//Devuelve la posicion en y del sprite
float Sprite::getYOrigin(){
    return sprite->getOrigin().y;
}

//Devuelve la rotación del sprite
float Sprite::getRotation(){
    return sprite->getRotation();
}

//Devuelve la escala del objeto
const sf::Vector2f Sprite::getScale(){
    return sprite->getScale();
}

//Mueve al personaje incrementando la posicion en x y en y con los valores pasados por parámetro.
void Sprite::move(float x, float y){
    float pos_x = Sprite::getXPosition();
    float pos_y = Sprite::getYPosition();
    sprite->setPosition(pos_x + x, pos_y + y);
}

sf::Sprite Sprite::getSprite(){
    return *sprite;
}

// Pinta del color RGB que le pasemos
void Sprite::setColor(float f1, float f2, float f3){
    sprite->setColor(sf::Color(f1,f2,f3));
}

void Sprite::setColor(float f1, float f2, float f3, float f4){
    sprite->setColor(sf::Color(f1,f2,f3,f4));
}

/* Pinta de color el sprite. Se le pasa una cadena:
    "blue"      --> para pintarlo azul
    "red"       --> para pintarlo rojo
    "green"     --> para pintarlo verde
    "yellow"     --> para pintarlo amarillo
    cualquier otra  para pintarlo negro
*/
void Sprite::setColor(const std::string s){
    if(s == "blue"){
        sprite->setColor(sf::Color::Blue);
    }
    else if(s == "red"){
        sprite->setColor(sf::Color::Red);
    }
    else if(s == "green") {
        sprite->setColor(sf::Color::Green);
    }
    else if(s == "yellow") {
        sprite->setColor(sf::Color::Yellow);
    }
    else
        sprite->setColor(sf::Color::Black);
    
}

void Sprite::setOrigin(float n1, float n2){
    sprite->setOrigin(n1, n2);
}

sf::Transform Sprite::getInverseTransform(){
    return sprite->getInverseTransform();
}
