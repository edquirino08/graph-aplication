#include <iostream>
#include "../include/Grafo.h"

#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

Grafo *leitura(ifstream &input_file, bool directed, bool weightedEdge, bool weightedNode)
{

  // Variáveis para auxiliar na criação dos nós no Grafo
  int idNodeSource;
  int idNodeTarget;
  int order;

  // Pegando a ordem do grafo
  input_file >> order;

  // Criando objeto grafo
  Grafo *graph = new Grafo(0, directed, weightedEdge, weightedNode);

  // Leitura de arquivo

  if (!graph->getWeightedEdge() && !graph->getWeightedNode())
  {

    while (input_file >> idNodeSource >> idNodeTarget)
    {

      graph->insertAresta(idNodeSource, idNodeTarget, 0, directed);
    }
  }
  else if (graph->getWeightedEdge() && !graph->getWeightedNode())
  {

    float edgeWeight;

    while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
    {

      graph->insertAresta(idNodeSource, idNodeTarget, edgeWeight, directed);
    }
  }
  else if (graph->getWeightedNode() && !graph->getWeightedEdge())
  {

    float nodeSourceWeight, nodeTargetWeight;

    while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
    {

      graph->insertAresta(idNodeSource, idNodeTarget, 0, graph->isDigrafo());
      graph->getNoById(idNodeSource)->setPesoNo(nodeSourceWeight);
      graph->getNoById(idNodeTarget)->setPesoNo(nodeTargetWeight);
    }
  }
  else if (graph->getWeightedNode() && graph->getWeightedEdge())
  {

    float nodeSourceWeight, nodeTargetWeight, edgeWeight;

    while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
    {

      graph->insertAresta(idNodeSource, idNodeTarget, edgeWeight, graph->isDigrafo());
      graph->getNoById(idNodeSource)->setPesoNo(nodeSourceWeight);
      graph->getNoById(idNodeTarget)->setPesoNo(nodeTargetWeight);
    }
  }

  return graph;
}

Grafo *leituraInstancia(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

  // Variáveis para auxiliar na criação dos nós no Grafo
  int idNodeSource;
  int idNodeTarget;
  int order;
  int numEdges;

  // Pegando a ordem do grafo
  input_file >> order;

  // Criando objeto grafo
  Grafo *graph = new Grafo(order, directed, weightedEdge, weightedNode);

  // Leitura de arquivo
  while (input_file >> idNodeSource >> idNodeTarget)
  {

    graph->insertAresta(idNodeSource, idNodeTarget, 0, directed);
  }

  return graph;
}

int menu()
{
  int selecao;
  cout << "\n==================== MENU ====================\n";
  cout << "[1] Fecho transitivo direto de um vertice\n";
  cout << "[2] Fecho transitivo indireto de um vertice\n";
  cout << "[3] Coeficiente de agrupamento local de um vertice\n";
  cout << "[4] Coeficiente de agrupamento medio do grafo\n";
  cout << "[5] Caminho Minimo entre dois vertices - Dijkstra\n";
  cout << "[6] Caminho Minimo entre dois vertices - Floyd\n";
  cout << "[7] Arvore Geradora Minima - Prim\n";
  cout << "[8] Arvore Geradora Minima - Kruskal\n";
  cout << "[9] Caminhamento em profundidade\n";
  cout << "[0] Sair\n";
  cout << "==============================================\n";

  cin >> selecao;

  return selecao;
}

void selecionar(int selecao, Grafo *graph, ofstream &output_file)
{

  switch (selecao)
  {

  // Fecho transitivo direto de um vértice ;
  case 1:
  {
    int id;
    cout << "Digite o ID do vertice para seu fecho transitivo direto: ";
    cin >> id;
    graph->imprimirFechoTransitivoDireto(output_file, id);
    break;
  }
    // Fecho transitivo indireto de um vértice;
  case 2:
  {
    int id;
    cout << "Digite o ID do vertice para seu fecho transitivo indireto: ";
    cin >> id;
    // graph->imprimirFechoTransitivoIndireto(output_file, id);
    break;
  }

    // Coeficiente de agrupamento local de um vértice;
  case 3:
  {
    int id;
    cout << "Digite o ID do vertice: ";
    cin >> id;
    // cout << "Coeficiente do nó " << id << ": " << graph->localClusteringCoefficient(id) << endl;
    break;
  }
    // Coeficiente de agrupamento médio do grafo;
  case 4:
  {
    cout << "Coeficiente Medio de agrupamento do grafo";
    // cout << " = " << graph->averageClusteringCoefficient() << endl;
    break;
  }
    // Djkstra
    // Caminho Mínimo entre dois vértices - Dijkstra ;
  case 5:
  {
    int id1, id2;
    cout << "Digite o vértcie de inicio: ";
    cin >> id1;
    cout << "Digite o vértcie final: ";
    cin >> id2;
    // float distancia = graph->dijkstra(id1, id2);
    cout << "A distancia entre " << id1 << " e " << id2 << " é de: "
         << "distancia" << endl;
    break;
  }

  case 6:
  {
    int id_one, id_two;
    cout << "Digite o id do vertice de origem: ";
    cin >> id_one;
    cout << "Digite o id do vertice de destino: ";
    cin >> id_two;
    // graph->minimalPathByFloyd(id_one, id_two);
    break;
  }
    // Árvore Geradora Mínima - Prim;
  case 7:
  {
    cout << "Árvore Geradora Mínima - Prim" << endl;
    // graph->minimalSpanningTreeByPrimAlgorithm(graph->getVerticeInduzido());
    break;
  }
    // Árvore Geradora Mínima - Kruskal;
  case 8:
  {
    // graph->agmByKruskal(output_file, graph->getVerticeInduzido());
    break;
  }
    // Caminhamento em profundidade
  case 9:
  {
    // output_file.close();
    int id;
    cout << "Digite o vértice de inicio: ";
    cin >> id;
    // graph->depthFirstSearch(output_file, id);
  }
  default:
  {
    cout << "Exit!!!" << endl;
  }
  }
}

int mainMenu(ofstream &output_file, Grafo *graph)
{

  int selecao;

  do
  {
    selecao = menu();

    if (output_file.is_open())
      selecionar(selecao, graph, output_file);
    else
      cout << "Unable to open the output_file" << endl;

    output_file << endl;
  } while (selecao != 0);

  return 0;
}

int main(int argc, const char *argv[])
{
  if (argc != 6)
  {
    cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
    return 1;
  }

  string program_name(argv[0]);
  string input_file_name(argv[1]);

  string instance;
  if (input_file_name.find("v") != string::npos)
  {
    instance = input_file_name.substr(input_file_name.find("v"));
    cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
  }

  // Abrindo arquivo de entrada
  ifstream input_file;
  ofstream output_file;
  input_file.open(argv[1], ios::in);
  output_file.open(argv[2], ios::out | ios::trunc);

  Grafo *graph;
  if (input_file.is_open())
  {
    auto start = chrono::steady_clock::now();
    graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    auto end = chrono::steady_clock::now();
    cout << "Demorou  "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms para ler o arquivo de entrada." << endl;
  }
  else
  {
    cout << "Unable to open " << argv[1] << endl;
    return 1;
  }

  mainMenu(output_file, graph);

  return 0;
}