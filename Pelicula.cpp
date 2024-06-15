#include "Pelicula.h"
#include <string>
using namespace std;

Pelicula::Pelicula():Video(){}

Pelicula::~Pelicula(){}

Pelicula::Pelicula(string id, string nombre, int duracion, string genero):Video(id, nombre, duracion, genero){}


string Pelicula::imprimir(){
    return this->id + ", " + this->nombre + ", " + to_string(this->duracion) + ", " + this->genero + ", " + calSinCalificacion();
}