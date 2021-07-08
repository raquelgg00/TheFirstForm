#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>

class Audio{
    public:
        Audio();
        ~Audio();
        void setBuffer(std::string);
        void setVolume(int);
        int getVolume(){return volumen;};
        void Play();
        void SetLoop(bool);
        void pause();

    private:
        sf::Sound sonido;
        sf::SoundBuffer buffer;
        int volumen;
};

#endif