#include "Conexion.h"
#include <iostream>

using namespace std;

// Singleton
Conexion* Conexion::pinstance = 0;
Conexion* Conexion::Instance(){
    if(pinstance == 0){
        pinstance = new Conexion;

    }
    return pinstance;
}

// Constructor
Conexion::Conexion(){
   
   // Conexion BD
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "sql11.freesqldatabase.com", "sql11423929", "YJhMdyzuXx", "sql11423929", 3306, NULL, 0);
    

    if(conectar){
        std::cout<<"Conexión establecida con la BD\n"; 
    }
    else {
        std::cout<<"No se pudo conectar con la BD\n";
    }

}

// Destructor
Conexion::~Conexion(){
    if(pinstance != NULL){
        delete pinstance;
        pinstance=NULL;
    }

}


string** Conexion::select_bd(string consulta, int filas){
    const char* c = consulta.c_str();
    int q_estado;

    std::string** res;
    res = new std::string*[filas]; // reservamos para X filas (10 en el ranking)
    for(int k=0; k<filas; k++){
        res[k] = new std::string[filas_tabla_usuario]; // para cada fila, usamos 4 columnas (nombre, niveles, monedas, muertes)
    }

    if(conectar){
        q_estado = mysql_query(conectar, c);
        if(!q_estado){
            resultado = mysql_store_result(conectar);
            int i = 0;
            while((fila = mysql_fetch_row(resultado)) && i<filas){
                for(int j=0; j<filas_tabla_usuario; j++){
                    res[i][j] = std::string(fila[j]);
                }
                i++;
            }
        }
    }
    return res;
}


        
bool Conexion::insert_bd(string consulta){

    const char* c = consulta.c_str();
    int q_estado;
   
    q_estado = mysql_query(conectar, c);
    if(!q_estado){
        resultado = mysql_store_result(conectar);
        return true;
    }

    if(mysql_error(conectar)){
        cout<<"ERROR AL HACER EL INSERT: "<<mysql_error(conectar)<<"\n";
    }

    return false;
}


        
bool Conexion::update_bd(string consulta){

    const char* c = consulta.c_str();
    int q_estado;
   
    q_estado = mysql_query(conectar, c);
    if(!q_estado){
        resultado = mysql_store_result(conectar);
        return true;
    }

    if(mysql_error(conectar)){
        cout<<"ERROR AL HACER EL UPDATE/DELETE: "<<mysql_error(conectar)<<"\n";
    }

    return false;
}