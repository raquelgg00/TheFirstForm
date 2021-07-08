#include "Partida.h"


/*
para usar valgrind primero instalarlo desde terminal y colocarse en la carpeta build de juego para ejecutar el comando:
valgrind --tool=memcheck --track-origins=yes ./MiJuego
hay que fijarse solo en los valores de definitly lost que deben ser 0 y 0
*/
int main(){
  Partida::Instance();
  return 0;
}

