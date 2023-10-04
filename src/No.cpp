#include "../include/No.h"

using namespace std;

No::No(int idNo)
{
    this->idNo = idNo;
    this->pesoNo = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
}
No::No(int idNo, int weight)
{
    this->idNo = idNo;
    this->pesoNo = weight;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
}
No::~No()
{
}

// Getters
int No::getIdNo()
{
    return idNo;
}

int No::getPesoNo()
{
    return pesoNo;
}

int No::getGrauEntrada()
{
    return grauEntrada;
}

int No::getGrauSaida()
{
    return grauSaida;
}

No *No::getProxNo()
{
    return proxNo;
}

Aresta *No::getPrimeiraAresta()
{
    return primeiraAresta;
}

Aresta *No::getUltimaAresta()
{
    return ultimaAresta;
}

// Setters
void No::setIdNo(int id)
{
    idNo = id;
}

void No::setPesoNo(int peso)
{
    pesoNo = peso;
}

void No::setGrauEntrada(int grau)
{
    grauEntrada = grau;
}

void No::setGrauSaida(int grau)
{
    grauSaida = grau;
}

void No::setProxNo(No *prox)
{
    proxNo = prox;
}

void No::setPrimeiraAresta(Aresta *aresta)
{
    primeiraAresta = aresta;
}

void No::setUltimaAresta(Aresta *aresta)
{
    ultimaAresta = aresta;
}