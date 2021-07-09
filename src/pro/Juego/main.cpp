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
  conectar = mysql_real_connect(conectar, "sql11.freesqldatabase.com", "sql11423929", "YJhMdyzuXx", "sql11423929", 3306, NULL, 0);

  MYSQL_ROW fila;
  MYSQL_RES* resultado;

  if(conectar){
    cout<<"Conexión establecida con la BD\n";
    string consulta = "select * from usuario";
    const char* c = consulta.c_str();
    int q_estado;

    q_estado = mysql_query(conectar, c);
    if(!q_estado){

      resultado = mysql_store_result(conectar);
      while(fila = mysql_fetch_row(resultado)){
        cout<<fila[0]<<" --> "<<fila[1]<<std::endl;
      }
    }
  }
  else {
    cout<<"No se pudo conectar con la BD\n";
  }


  Partida::Instance();
  return 0;
}








