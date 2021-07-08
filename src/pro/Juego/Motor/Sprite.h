#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> 

class Sprite{

    public:
        Sprite();
        ~Sprite();

        //Color, textures and frame functions
        bool setTexture(std::string, std::string);
        bool setFrameSprite(int,int,int,int);
        void setColor(float, float, float, float);
        void setColor(float, float, float);
        void setColor(const std::string);
        void setAnimation(int, int, int, int, int);

        //Common Sprite set functions like position, scale and rotation
        void setPosition(float, float);
        void setScale(float, float);
        void setRotation(float);
        void setOrigin(float, float);

        void setimage();

        sf::Sprite getSprite();


        //Collision and position Sprite functions
        sf::FloatRect getBounds(const char[]);
        float getXPosition();
        float getYPosition();
        float getRotation();
        float getXOrigin();
        float getYOrigin();
        const sf::Vector2f getScale();
        void move(float, float);
        sf::Transform getInverseTransform();

        

    private:
        sf::Sprite *sprite = NULL;
        sf::Texture *textura = NULL;
        bool texture_applied;
};
#endif