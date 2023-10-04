
#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta
{
public:
    Aresta(int noDestino);
    Aresta(int noDestino, int pesoAresta);

    int getPesoAresta();
    void setPesoAresta(int pesoAresta);

    int getIdNoDestino();
    void setIdNoDestino(int idNoDestino);

    Aresta *getProxAresta();
    void setProxAresta(Aresta *proxAresta);

private:
    int pesoAresta;
    int idNoDestino;
    Aresta *proxAresta;
};

#endif // ARESTA_H
