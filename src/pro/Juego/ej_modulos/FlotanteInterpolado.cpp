#include "FlotanteInterpolado.h"

// Constructor por defecto
FlotanteInterpolado::FlotanteInterpolado(){
    x = 0;
    y = 0;
    prevX = 0;
    prevY = 0;
}

FlotanteInterpolado::FlotanteInterpolado(float xini, float yini){
    x=xini;
    y=yini;
    prevX=0;
    prevY=0;
}

void FlotanteInterpolado::setPositionXY(float nx, float ny){
    prevX=x;
    prevY=y;
    x=nx;
    y=ny;
}
void FlotanteInterpolado::setPositionX(float nx){
    prevX=x;
    x=nx;
}
void FlotanteInterpolado::setPositionY(float ny){
    prevY=y;
    y=ny;
}
void FlotanteInterpolado::restaurarPosiciones(){
    x=prevX;
    y=prevY;
    prevX=-1;
    prevY=-1;
}

float FlotanteInterpolado::getX(){
    return x;
}

float FlotanteInterpolado::getY(){
    return y;
}

float FlotanteInterpolado::getPrevX(){
    return prevX;
}

float FlotanteInterpolado::getPrevY(){
    return prevY;
}

void FlotanteInterpolado::reset(){
    prevX=0;
    prevY=0;
}