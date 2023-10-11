#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "Aresta.h"
#include "No.h"
#include <vector>

using namespace std;

class No;
class Aresta;

class Grafo
{
public:
    //--- Construtor e Destrutor ---
    Grafo();
    Grafo(bool isDigrafo);
    Grafo(bool isDigrafo, bool weightArc);
    Grafo(int order, bool directed, bool weightedEdge, bool weightedNode);
    virtual ~Grafo();

    //--- Seters ---
    void incOrdem();
    void decOrdem();

    //--- Funcoes do No ---
    bool procurarNoPeloId(int idFindNo);
    No *insereNo(int idNo);
    bool removeNo(int idNo, bool isDigrafo);
    No *getNoById(int idNo);

    //--- Funcoes de Aresta ---
    bool insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool isDirected);
    bool removeAresta(int idNoOrigem, int idNoDestino, bool isDirected);

    //--- Caracteristica do Grafo ---
    int getNumAresta();
    No *getNoRaiz();
    int getOrdem();
    int getGrauEntrada();
    int getGrauSaida();
    void printGrafo();
    bool isDigrafo();
    bool getWeightedEdge();
    bool getWeightedNode();

    void gravarArquivoSaida(vector<int> v, ofstream &arquivoSaida);

    // --- Etapas trabalho ---

    void imprimirFechoTransitivoDireto(ofstream &arquivoSaida, int idNo);
    void imprimirFechoTransitivoIndireto(ofstream &arquivoSaida, int idNo);
    // void getIncomingNodes(int idNo, vector<int> &feixoTransitivo, vector<bool> &visitados);

private:
    int ordem;
    int numAresta;
    bool digrafo;
    bool weigthNo;
    bool weightArc;

    No *noRaiz;
};

#endif // GRAPH_H
