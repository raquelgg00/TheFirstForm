#include "Partida.h"
#include "ej_modulos/mysql/mysql.h"

/*
para usar valgrind primero instalarlo desde terminal y colocarse en la carpeta build de juego para ejecutar el comando:
valgrind --tool=memcheck --track-origins=yes ./MiJuego
hay que fijarse solo en los valores de definitly lost que deben ser 0 y 0
*/
int main(){

  // Conexion BD
  MYSQL* conectar = mysql_init(0);
  conectar = mysql_real_connect(conectar, "localhost", "id17210918_gasparmr6", "</IPvRwRAz~(OHh2", "id17210918_bd_webhost", 21, NULL, 0);

  MYSQL_ROW fila;
  MYSQL_RES* resultado;

  if(conectar){
    string consulta = "select *";
    const char* c = consulta.c_str();
    int q_estado;

    q_estado = mysql_query(conectar, c);
    if(!q_estado){
      resultado = mysql_store_result(conectar);
      while(fila = mysql_fetch_row(resultado)){
        cout<<fila[0]<<" , "<<fila[1];
      }
    }
  }
  else {
    cout<<"No se conecto con la BD";
  }



  Partida::Instance();
  return 0;
}

