#include "Video.h"
#include "Episodio.h"
#include "Pelicula.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>
#include <limits>

using namespace std;

vector<Video*> cargar(const string& nombreArchivo) {
    vector<Video*> videos;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t pos = 0;
            string token;
            string tipo, id, titulo, duracion_str, genero, serie, numero_str;
            int duracion = 0, numero = 0;

            auto getMenu = [&](char delimiter) {
                pos = linea.find(delimiter);
                if (pos != string::npos) {
                    token = linea.substr(0, pos);
                    linea.erase(0, pos + 1);
                } else {
                    token = linea;
                    linea.clear();
                }
                return token;
            };

            tipo = getMenu(',');
            id = getMenu(',');
            titulo = getMenu(',');
            duracion_str = getMenu(',');
            genero = getMenu(',');

            try {
                duracion = stoi(duracion_str);
            } catch (const invalid_argument& e) {
                cerr << "Error: duracion no es un numero valido: " << linea << endl;
                continue; 
            } catch (const out_of_range& e) {
                cerr << "Error: duracion fuera de rango en la linea: " << linea << endl;
                continue; 
            }

            if (tipo == "c") {
                serie = getMenu(',');
                numero_str = getMenu(',');
                try {
                    numero = stoi(numero_str);
                } catch (const invalid_argument& e) {
                    cerr << "Error: numero no es un numero valido en la linea: " << linea << endl;
                    continue; 
                } catch (const out_of_range& e) {
                    cerr << "Error: numero fuera de rango en la linea: " << linea << endl;
                    continue; 
                }
                videos.push_back(new Episodio(id, titulo, duracion, genero, serie, numero));
            } else if (tipo == "p") {
                videos.push_back(new Pelicula(id, titulo, duracion, genero));
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return videos;
}

void mostrarCatalogo(const vector<Video*>& videos) {
    cout << "Id, Nombre, Duracion, temporada ,genero, Calificacion" << endl;
    for (const auto& video : videos) {
        cout << *video << endl;
    }
}

void calificarVideo(vector<Video*>& videos) {
    string videoID;
    cout << "Ingresa el ID del video a calificar: ";
    cin >> videoID;

    for (auto& video : videos) {
        if (video->getId() == videoID) {
            int calificacion;
            cout << "Ingresa la calificación ( 1 - 5 , solo enteros): ";
            while (!(cin >> calificacion) || calificacion < 1 || calificacion > 5) {
                cout << "Calificación inválida. Ingresa un valor entero entre 1 y 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            video->calificar(calificacion);
            cout << "Calificación agregada correctamente." << endl;
            return;
        }
    }
    cout << "No se encontró un video con el ID ingresado." << endl;
}

void mostrarVideosPorCalificacion(const vector<Video*>& videos) {
    int subopcion;
    cout << "------SUBMENU------" << endl;
    cout << "1. Ver películas" << endl;
    cout << "2. Ver capítulos" << endl;
    cout << "3. Ver película y capítulos" << endl;
    cout << "Selecciona una opción: ";
    while (!(cin >> subopcion) || subopcion < 1 || subopcion > 3) {
        cout << "Opción inválida. Ingresa un valor entre 1 y 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double calificacion;
    cout << "Ingresa la calificación mínima (1-5): ";
    while (!(cin >> calificacion) || calificacion < 1 || calificacion > 5) {
        cout << "Calificación inválida. Ingresa un valor entre 1 y 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Id, Nombre, Calificación" << endl;
    for (const auto& video : videos) {
        if ((subopcion == 1 && dynamic_cast<Pelicula*>(video)) ||
            (subopcion == 2 && dynamic_cast<Episodio*>(video)) ||
            subopcion == 3) {
            if (video->getCalificacion() >= calificacion) {
                cout << video->imprimirCalificacion() << endl;
            }
        }
    }
}

void mostrarVideosPorGenero(const vector<Video*>& videos) {
    int subopcion;
    cout << "-----SUBMENU----" << endl;
    cout << "1. Ver películas" << endl;
    cout << "2. Ver capítulos" << endl;
    cout << "3. Ver películas y capítulos" << endl;
    cout << "Selecciona una opción: ";
    while (!(cin >> subopcion) || subopcion < 1 || subopcion > 3) {
        cout << "Opción inválida. Ingresa un valor entre 1 y 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string genero;
    cout << "Ingresa un género (drama, accion, misterio): ";
    while (cin >> genero && genero != "drama" && genero != "accion" && genero != "misterio") {
        cout << "Opción inválida. Ingrese un género válido (drama, accion, misterio): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Id, Nombre, Genero, Calificación" << endl;
    for (const auto& video : videos) {
        if ((subopcion == 1 && dynamic_cast<Pelicula*>(video)) ||
            (subopcion == 2 && dynamic_cast<Episodio*>(video)) ||
            subopcion == 3) {
            if (video->getGenero() == genero) {
                cout << video->imprimirGenero() << endl;
            }
        }
    }
}

void mostrarMenu(vector<Video*>& videos) {
    int opcion = 0;
    while (opcion != 9) {
        cout << "---- MENU ----" << endl;
        cout << "1. Mostrar el catálogo con calificaciones" << endl;
        cout << "2. Calificar un video" << endl;
        cout << "3. Mostrar películas o episodios con la calificación mìnima requerida por usuario" << endl;
        cout << "4. Mostrar películas o episodios de un cierto género" << endl;
        cout << "9. Salir" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarCatalogo(videos);
                break;
            case 2:
                calificarVideo(videos);
                break;
            case 3:
                mostrarVideosPorCalificacion(videos);
                break;
            case 4:
                mostrarVideosPorGenero(videos);
                break;
            case 9:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }

        cout << endl;
    }
}

int main() {
    vector<Video*> videos = cargar("archivo1.txt");
    mostrarMenu(videos);
    return 0;
}
