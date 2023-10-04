#include "Grafo.h"

using namespace std;

Grafo::Grafo(bool isDigrafo)
{
    this->ordem = 0;
    this->noRaiz = NULL;
    this->digrafo = isDigrafo;
    this->weigthNo = 0;
    this->weightArc = 0;
}
Grafo::~Grafo()
{
}

//--- Seters ---
void Grafo::incOrdem()
{
    this->ordem++;
}
void Grafo::decOrdem()
{
    this->ordem--;
}

//--- Funcoes do No ---
bool procurarNoPeloId(int idFindNo);
No *insereNo(int idNo, int pesoNo);
bool removeNo(int idNo, bool isDigrafo);

//--- Funcoes de Aresta ---
bool insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected);
bool removeAresta(int idNoOrigem, int idNoDestino, bool isDirected);

//--- Caracteristica do Grafo ---
int Grafo::getNumAresta()
{
    return this->numAresta;
}
No *Grafo::getNoRaiz()
{
    return this->noRaiz;
}
int Grafo::getOrdem()
{
    return this->ordem;
}
int Grafo::getGrauEntrada()
{
    int inputDegree = 0;

    No *noAux = noRaiz;
    while (noAux != NULL)
    {
        if (noAux->getGrauEntrada() > inputDegree)
        {
            inputDegree = noAux->getGrauEntrada();
        }
        noAux = noAux->getProxNo();
    }
    return inputDegree;
}
int Grafo::getGrauSaida()
{
    int outputDegree = 0;

    No *noAux = noRaiz;
    while (noAux != NULL)
    {
        if (noAux->getGrauSaida() > outputDegree)
        {
            outputDegree = noAux->getGrauSaida();
        }
        noAux = noAux->getProxNo();
    }
    return outputDegree;
}