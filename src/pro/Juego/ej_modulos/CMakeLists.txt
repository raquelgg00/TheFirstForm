#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Partida.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/CampoGravedad.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ObjetoMundo2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Ayuda.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AnimacionInicial.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/InGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Nivel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FlotanteInterpolado.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mysql/mysql.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/MenuMundo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/MenuPrincipal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/Opciones.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/Creditos.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/Controles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/Pausa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/InicioJuego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menus/CambioResolucion.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos/Bolita.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos/Canion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos/Molino.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos/PinchoPared.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos/Bala.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Plataforma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Arista.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Cubo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Sensor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Pared.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Entidades/Puerta.cpp"
   
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

