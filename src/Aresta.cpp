#include "../include/Aresta.h"

using namespace std;

Aresta::Aresta(int noDestino)
{
    this->idNoDestino = noDestino;
}

Aresta::Aresta(int noDestino, int pesoAresta)
{
    this->idNoDestino = noDestino;
    this->pesoAresta = pesoAresta;
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
