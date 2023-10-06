#include "../include/Grafo.h"

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
bool Grafo::procurarNoPeloId(int idFindNo)
{
    No *noAux = this->noRaiz;

    while (noAux != NULL)
    {
        if (noAux->getIdNo() == idFindNo)
        {
            return true;
        }

        if (noAux->getIdNo() == NULL)
        {
            return false;
        }

        noAux = noAux->getProxNo();
    }
    return false;
}

No *Grafo::getNoById(int idNo)
{

    No *noAux = this->noRaiz;
    while (noAux != nullptr)
    {

        if (noAux->getIdNo() == idNo)
        {
            return noAux;
        }

        noAux = noAux->getProxNo();
    }
    return nullptr;
}

No *Grafo::insereNo(int idNo)
{
    if (procurarNoPeloId(idNo))
    {
        return NULL;
    }

    No *newNo = new No(idNo);

    if (noRaiz == NULL)
    {
        noRaiz = newNo;
    }
    else
    {
        newNo->setProxNo(noRaiz);
        noRaiz = newNo;
    }

    this->incOrdem();
    return newNo;
}

bool Grafo::removeNo(int idNo, bool isDigrafo)
{
}

//--- Funcoes de Aresta ---
bool Grafo::insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected)
{
    No *noOrigem = this->getNoById(idNoOrigem);
    No *noDestino = this->getNoById(idNoDestino);

    if (noOrigem == nullptr)
    {
        this->insereNo(idNoOrigem);
        noOrigem = this->getNoById(idNoOrigem);
    }

    if (noDestino == nullptr)
    {
        this->insereNo(idNoDestino);
        noDestino = this->getNoById(idNoDestino);
    }

    if (isDirected)
    {
    }
    else
    {
        if (noOrigem->getPrimeiraAresta() == nullptr)
        {
            Aresta *aresta = new Aresta(idNoDestino, pesoAresta);
            noOrigem->setPrimeiraAresta(aresta);
            noOrigem->setUltimaAresta(aresta);
        }
        else
        {
        }
    }
}
bool Grafo::removeAresta(int idNoOrigem, int idNoDestino, bool isDirected)
{
}

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