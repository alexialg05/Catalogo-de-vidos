#ifndef VIDEO_H
#define VIDEO_H
#include <string>
#include <iostream>
using namespace std;

class Video{
    protected:
        string id;
        int duracion;
        string genero;
        string nombre;

        int sumacalificacion;;
        int numcalificacion;
        double calificacion;

    public:

        void calificar(int);
        void calcularCalificacion();
        virtual string imprimir()=0;
        string imprimirCalificacion();
        string imprimirGenero();
        string calSinCalificacion();

        string getId();
        double getCalificacion();
        string getGenero();

        Video();
        Video(string, string, int, string);
        ~Video();

    friend ostream& operator<< (ostream& os, Video& vid){
        os << vid.imprimir() ;
        return os;
        }

};
#endif