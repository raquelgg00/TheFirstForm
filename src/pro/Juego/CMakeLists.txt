cmake_minimum_required(VERSION 3.1)
project(TheFirstShape)

#Añadir tantos subdirectorios como se necesiten
#En cada subdirectorio debe haber un fichero CMakeLists.txt
#Habitualmente cada subdirectorio determinará una libreria 
add_library(libModulos STATIC)
add_subdirectory(ej_modulos)
add_subdirectory(Motor)

#Opciones a pasar al compilador de C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall ")

#Se desea generar un ejecutable, se especifica donde está el main
#y ficheros que aporten código que no sean librerias o subcarpetas 
add_executable(TheFirstShape main.cpp favicon.rc)

#Añadir todos los objetos (ficheros o) que requiera el ejecutable. 
#Habitualmente todas las librerias definidas mediante subcarpetas
#aportaran código
target_link_libraries(TheFirstShape libModulos)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#Para usar SFML
set(SFML_ROOT "C:/SFML/lib")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories("C:/SFML/include")
    target_link_libraries(TheFirstShape ${SFML_LIBRARIES})
endif()

include_directories("C:/Program Files/MySQL/Connector C++ 1.1/include")
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/MySQL/Connector C++ 1.1/lib/opt")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")
target_link_libraries(TheFirstShape "C:/Program Files/MySQL/Connector C++ 1.1/lib/opt/mysqlcppconn.lib")
target_link_libraries(TheFirstShape "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")


# Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
	file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()