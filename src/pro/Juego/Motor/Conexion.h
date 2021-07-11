#ifndef CONEXION_H
#define CONEXION_H
#include <SFML/Graphics.hpp>
#include "mysql/mysql.h"
#include <string>
#include <sstream>

class Conexion{

    public:
        static Conexion* Instance();
        bool insert_bd(std::string);
        bool update_bd(std::string);
        void delete_bd(std::string);
        std::string** select_bd(std::string, int);


    protected:
        Conexion();
        ~Conexion();
        Conexion(const Conexion & );
        Conexion &operator= (const Conexion & );

    private:
        static Conexion* pinstance;
        MYSQL* conectar;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        int filas_tabla_usuario = 4;
       
};

#endif
