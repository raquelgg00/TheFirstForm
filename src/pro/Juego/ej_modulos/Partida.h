#ifndef PARTIDA_H
#define PARTIDA_H
#pragma once
#include <iostream>
#include "JuegoState.h"
#include "Motor.h"
#include "Menus/InicioJuego.h"


class Partida {
  private:
    static Partida* pinstance;
    static JuegoState* state_;
    Motor *motor = NULL;
    sf::Clock relojInterpo;
    sf::Clock relojUpdate;
    sf::Time tiempoInterpo;
    float tickTime;

  public:
    static Partida* Instance();
    ~Partida();
    static void setEstado(JuegoState *state);
    void gameLoop();
    void render(), update(), input();
    float getTickTime(){return tickTime;};

  protected:
    Partida();
    Partida(const Partida & );
    Partida &operator= (const Partida & );
};

#endif