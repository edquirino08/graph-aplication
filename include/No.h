#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;
class Aresta;

class No
{
public:
    No(int idNo);
    No(int idNo, int weight);
    virtual ~No();

    int getIdNo();
    void setIdNo(int idNo);

    int getPesoNo();
    void setPesoNo(int peso);

    int getGrauEntrada();
    void setGrauEntrada(int grau);

    int getGrauSaida();
    void setGrauSaida(int grau);

    No *getProxNo();
    void setProxNo(No *prox);

    Aresta *getPrimeiraAresta();
    void setPrimeiraAresta(Aresta *aresta);

    Aresta *getUltimaAresta();
    void setUltimaAresta(Aresta *aresta);

private:
    int idNo;
    int pesoNo;
    int grauEntrada;
    int grauSaida;
    No *proxNo;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
};

#endif // NO_H
