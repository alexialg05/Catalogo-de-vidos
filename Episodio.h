#ifndef CAPITULO_H
#define CAPITULO_H
#include <string>
#include "Video.h"
using namespace std;

class Episodio:public Video{
    private:
        int episodio;
        string serie;
    public:
        Episodio();
        Episodio(string, string, int, string, string, int);
        ~Episodio();

        string imprimir();

};
#endif