#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Audio.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Sprite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Texto.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Guardar.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Collision.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Conexion.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

