#ifndef CONEXION_H
#define CONEXION_H

#include <string>
#include <sstream>
#include <mysql/mysql.h>

class Conexion{

    public:
        static Conexion* Instance();
        bool insert_bd(std::string);
        bool update_bd(std::string);
        void delete_bd(std::string);
        std::string** select_bd(std::string, int);
        bool getConexion(){
			mysql_close(conectar);
			conectar = mysql_init(0);
			conectar = mysql_real_connect(conectar, "sql11.freesqldatabase.com", "sql11425998", "gXcpSTHTYv", "sql11425998", 3306, NULL, 0);
			if(conectar)
				return true;
			else
				return false;
        }

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
        int filas_tabla_usuario = 5;
       
};

#endif

