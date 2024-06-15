#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream archivo;
    archivo.open("archivo1.txt");

    if (archivo.is_open()) {
        archivo << "p,peliculas-1,Pocahontas,120,drama" << endl;
        archivo << "p,peliculas-2,Avengers,180,accion" << endl;
        archivo << "p,pelicula-3,Inferno,100,misterio" << endl;
        archivo << "c,episodio-1,Stranger Things,50,misterio,temporada-1,1" << endl;
        archivo << "c,episodio-2,Suits,45,drama,temporada-2,2" << endl;
        archivo << "c,episodio-3,Arrow,42,accion,temporada-3,3" << endl;
    } else {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }

    archivo.close();
    return 0;
}
