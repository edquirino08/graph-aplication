#include <iostream>
#include "../include/Grafo.h"

#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

void criaGrafoListaAdj(Grafo *grafo, ifstream &entrada)
{
  if (!entrada.is_open())
  {
    cout << "Erro ao abrir o arquivo de entrada." << endl;
    return;
  }

  // Lê o número de vértices do arquivo
  int numVertices;
  entrada >> numVertices;

  // Cria os nós no grafo
  for (int i = 1; i <= numVertices; i++)
  {
    grafo->insereNo(i);
  }

  int idNoOrigem, idNoDestino;
  while (entrada >> idNoOrigem >> idNoDestino)
  {
    // Adiciona as arestas no grafo
    grafo->insertAresta(idNoOrigem, idNoDestino, 0, grafo->isDigrafo());
  }
}

int main(int argc, const char *argv[])
{

  // Criando arquivos de entrada e saida
  ifstream entrada;
  ofstream saida;
  entrada.open(argv[1], ios::in);
  saida.open(argv[2], ios::out | ios::trunc);

  // Obtendo a informacao se o grafo eh direcionado ou nao
  bool ehDirecionado;
  cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
  cin >> ehDirecionado;
  cout << "Eh direcionado: " << ehDirecionado;
  cout << '\n'
       << endl;

  // Obtendo a informacao se o grafo eh ponderado ou nao
  bool ehPonderado;
  cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
  cin >> ehPonderado;
  cout << "Eh ponderado: " << ehPonderado;
  cout << '\n'
       << endl;

  Grafo *g = new Grafo(ehDirecionado, ehPonderado);

  // Criando grafo a partir de uma lista de adjacencia
  cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;
  criaGrafoListaAdj(g, entrada);

  g->printGrafo();

  return 0;
}