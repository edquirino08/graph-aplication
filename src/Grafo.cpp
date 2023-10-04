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
int getNumAresta();
No *getNoRaiz();
int getOrdem();
int getGrauEntrada();
int getGrauSaida();