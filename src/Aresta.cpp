#include "../include/Aresta.h"

using namespace std;

Aresta::Aresta()
{
    this->idNoDestino = 0;
    this->pesoAresta = 0;
    this->proxAresta = nullptr;
}

Aresta::Aresta(int noDestino)
{
    this->idNoDestino = noDestino;
    this->pesoAresta = 0;
    this->proxAresta = nullptr;
}

Aresta::Aresta(int noDestino, int pesoAresta)
{
    this->idNoDestino = noDestino;
    this->pesoAresta = pesoAresta;
    this->proxAresta = nullptr;
}

int Aresta::getPesoAresta()
{
    return this->pesoAresta;
}

void Aresta::setPesoAresta(int pesoAresta)
{
    this->pesoAresta = pesoAresta;
}

int Aresta::getIdNoDestino()
{
    return this->idNoDestino;
}
void Aresta::setIdNoDestino(int idNoDestino)
{
    this->idNoDestino = idNoDestino;
}

Aresta *Aresta::getProxAresta()
{
    return this->proxAresta;
}
void Aresta::setProxAresta(Aresta *proxAresta)
{
    this->proxAresta = proxAresta;
}
