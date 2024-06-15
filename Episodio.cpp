#include "Episodio.h"
#include <string>
using namespace std;

Episodio::Episodio():Video(){
    episodio = 0;
    serie = "";
}

Episodio::Episodio(string id, string nombre, int duracion, string genero, string serie, int episodio):Video(id, nombre, duracion, genero){
    this->episodio = episodio;
    this->serie = serie;
}

Episodio::~Episodio(){}

string Episodio::imprimir(){
    return  this->id + ", " + this->nombre + ", " + to_string(this->duracion) + ", " + this->genero + ", " + this->serie + ", " + to_string(this->episodio) + ", " + calSinCalificacion();
}
