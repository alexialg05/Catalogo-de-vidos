#include "Video.h"
#include <string>
using namespace std;

Video::Video() {
    id = "";
    nombre = "";
    duracion = 0;
    genero = "";
    sumacalificacion = 0;
    numcalificacion = 0;
    calificacion = 0;
}

Video::Video(string id, string nombre, int duracion, string genero) {
    this->id = id;
    this->nombre = nombre;
    this->duracion = duracion;
    this->genero = genero;
    sumacalificacion = 0;
    numcalificacion = 0;
    calificacion = 0;
}

Video::~Video() {
    // Destructor
}

void Video::calificar(int calificacion) {
    sumacalificacion += calificacion;
    numcalificacion++;
    calcularCalificacion();
}

void Video::calcularCalificacion() {
    if (numcalificacion != 0) {
        calificacion = static_cast<double>(sumacalificacion) / numcalificacion;
    }
}

string Video::getId() {
    return id;
}

double Video::getCalificacion() {
    return calificacion;
}

string Video::getGenero() {
    return genero;
}

string Video::calSinCalificacion() {
    if (sumacalificacion != 0) {
        return to_string(calificacion);
    } else {
        return "SinCalificacion";
    }
}

string Video::imprimirCalificacion() {
    return id + ", " + nombre + ", " + calSinCalificacion();
}

string Video::imprimirGenero() {
    return id + ", " + nombre + ", " + genero + ", " + calSinCalificacion();
}
