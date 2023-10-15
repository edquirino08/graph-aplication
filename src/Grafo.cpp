#include "../include/Grafo.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>
#include <set>
#include <cfloat>

using namespace std;

Grafo::Grafo()
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = 0;
    this->weigthNo = 0;
    this->weightArc = 0;
}


Grafo::Grafo(bool isDigrafo)
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = isDigrafo;
    this->weigthNo = 0;
    this->weightArc = 0;
}

Grafo::Grafo(bool isDigrafo,bool weightArc)
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = isDigrafo;
    this->weigthNo = 0;
    this->weightArc = weightArc;
}

Grafo::~Grafo()
{
    No *currentNode = noRaiz;
    while (currentNode != nullptr)
    {
        Aresta *currentEdge = currentNode->getPrimeiraAresta();
        while (currentEdge != nullptr)
        {
            Aresta *tempEdge = currentEdge;
            currentEdge = currentEdge->getProxAresta();
            delete tempEdge;
        }
        No *tempNode = currentNode;
        currentNode = currentNode->getProxNo();
        delete tempNode;
    }
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

    while (noAux != nullptr)
    {
        if (noAux->getIdNo() == idFindNo)
        {
            return true;
        }

        if (noAux->getIdNo() == 0)
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
        return nullptr;
    }

    No *newNo = new No(idNo);

    if (noRaiz == nullptr)
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
    No *noToRemove = getNoById(idNo);

    if (noToRemove == nullptr)
    {
        return false;
    }

    Aresta *currentEdge = noToRemove->getPrimeiraAresta();
    while (currentEdge != nullptr)
    {
        Aresta *tempEdge = currentEdge;
        currentEdge = currentEdge->getProxAresta();
        removeAresta(idNo, tempEdge->getIdNoDestino(), isDigrafo);
    }

    No *currentNode = noRaiz;
    No *previousNode = nullptr;

    while (currentNode != nullptr)
    {
        if (currentNode == noToRemove)
        {
            if (previousNode == nullptr)
            {
                noRaiz = currentNode->getProxNo();
            }
            else
            {
                previousNode->setProxNo(currentNode->getProxNo());
            }

            delete currentNode;
            this->decOrdem();
            return true;
        }

        previousNode = currentNode;
        currentNode = currentNode->getProxNo();
    }

    return false;
}


//--- Funcoes de Aresta ---
bool Grafo::insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool isDirected)
{
    No *noOrigem = getNoById(idNoOrigem);
    No *noDestino = getNoById(idNoDestino);

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

    Aresta *novaAresta = new Aresta(idNoDestino, pesoAresta);

    if (noOrigem->getPrimeiraAresta() == nullptr)
    {
        noOrigem->setPrimeiraAresta(novaAresta);
        noOrigem->setUltimaAresta(novaAresta);
    }
    else
    {
        noOrigem->getUltimaAresta()->setProxAresta(novaAresta);
        noOrigem->setUltimaAresta(novaAresta);
    }

    if (!isDirected)
    {
        Aresta *novaArestaInversa = new Aresta(idNoOrigem, pesoAresta);

        if (noDestino->getPrimeiraAresta() == nullptr)
        {
            noDestino->setPrimeiraAresta(novaArestaInversa);
            noDestino->setUltimaAresta(novaArestaInversa);
        }
        else
        {
            noDestino->getUltimaAresta()->setProxAresta(novaArestaInversa);
            noDestino->setUltimaAresta(novaArestaInversa);
        }
    }
    else
    {
        noOrigem->setGrauSaida(noOrigem->getGrauSaida() + 1);
        noDestino->setGrauEntrada(noDestino->getGrauEntrada() + 1);
    }

    this->numAresta++;

    return true;
}

bool Grafo::removeAresta(int idNoOrigem, int idNoDestino, bool isDirected)
{
    No *noOrigem = getNoById(idNoOrigem);
    No *noDestino = getNoById(idNoDestino);

    if (noOrigem == nullptr)
    {
        return false;
    }

    Aresta *aresta = noOrigem->getPrimeiraAresta();
    Aresta *arestaAnterior = nullptr;

    while (aresta != nullptr)
    {
        if (aresta->getIdNoDestino() == idNoDestino)
        {
            if (arestaAnterior == nullptr)
            {
                noOrigem->setPrimeiraAresta(aresta->getProxAresta());
            }
            else
            {
                arestaAnterior->setProxAresta(aresta->getProxAresta());
            }

            delete aresta;

            if (isDirected)
            {
                noOrigem->setGrauSaida(noOrigem->getGrauSaida() - 1);
                noDestino->setGrauEntrada(noDestino->getGrauEntrada() - 1);
            }
            else
            {
                Aresta *arestaOposta = noDestino->getPrimeiraAresta();
                Aresta *arestaOpostaAnterior = nullptr;

                while (arestaOposta != nullptr)
                {
                    if (arestaOposta->getIdNoDestino() == idNoOrigem)
                    {
                        if (arestaOpostaAnterior == nullptr)
                        {
                            noDestino->setPrimeiraAresta(arestaOposta->getProxAresta());
                        }
                        else
                        {
                            arestaOpostaAnterior->setProxAresta(arestaOposta->getProxAresta());
                        }

                        delete arestaOposta;
                        break;
                    }

                    arestaOpostaAnterior = arestaOposta;
                    arestaOposta = arestaOposta->getProxAresta();
                }
            }

            this->numAresta--;
            return true;
        }

        arestaAnterior = aresta;
        aresta = aresta->getProxAresta();
    }

    return false;
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
    while (noAux != nullptr)
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
    while (noAux != nullptr)
    {
        if (noAux->getGrauSaida() > outputDegree)
        {
            outputDegree = noAux->getGrauSaida();
        }
        noAux = noAux->getProxNo();
    }
    return outputDegree;
}

void Grafo::printGrafo()
{
    cout << "Ordem do Grafo: " << ordem << endl;
    cout << "Numero de Arestas: " << this->numAresta << endl;
    cout << "Tipo do Grafo: " << (digrafo ? "Direcionado" : "Nao Direcionado") << endl;
    cout << "Peso nos nos: " << (weigthNo ? "Sim" : "Nao") << endl;
    cout << "Peso nas arestas: " << (weightArc ? "Sim" : "Nao") << endl;

    cout << "\nNos do Grafo:" << endl;
    No *currentNode = noRaiz;
    while (currentNode != nullptr)
    {
        cout << "  ID do no: " << currentNode->getIdNo() << endl;
        cout << "  Peso do no: " << currentNode->getPesoNo() << endl;
        cout << "  Grau de entrada: " << currentNode->getGrauEntrada() << endl;
        cout << "  Grau de saida: " << currentNode->getGrauSaida() << endl;

        Aresta *currentEdge = currentNode->getPrimeiraAresta();
        cout << "  Arestas deste no:" << endl;
        while (currentEdge != nullptr)
        {
            cout << "    Destino: " << currentEdge->getIdNoDestino() << endl;
            cout << "    Peso da aresta: " << currentEdge->getPesoAresta() << endl;
            currentEdge = currentEdge->getProxAresta();
        }

        currentNode = currentNode->getProxNo();
        cout << endl;
    }
}

bool Grafo::isDigrafo(){
    return this->digrafo;
}

bool Grafo::getWeightedEdge()
{
    return this->weightArc;
}
bool Grafo::getWeightedNode()
{
    return this->weigthNo;
}

void Grafo::gravarArquivoSaida(vector<int> v, ofstream &arquivoSaida)
{
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return;
    }
    for (int i = 0; i < v.size(); i++)
    {
        arquivoSaida << v[i];
        if (i < v.size() - 1)
        {
            arquivoSaida << ",";
        }
    }
    arquivoSaida << std::endl;

    arquivoSaida.close();
}

//------funções primeira etapa-----//

void Grafo::imprimirFechoTransitivoDireto(ofstream &arquivoSaida, int idNo)
{
    vector<int> feixoTransitivo;
    feixoTransitivo.push_back(idNo);
    vector<bool> visitados(this->ordem, false);

    No *node = getNoById(idNo);

    if (node == nullptr)
    {
        cout << "Erro! No nao encontrado." << endl;
        return;
    }

    Aresta *aresta = node->getPrimeiraAresta();
    while (aresta != nullptr)
    {
        if (visitados[aresta->getIdNoDestino()] == false)
        {
            visitados[aresta->getIdNoDestino()] = true;
            feixoTransitivo.push_back(aresta->getIdNoDestino());
        }

        aresta = aresta->getProxAresta();
    }

    gravarArquivoSaida(feixoTransitivo, arquivoSaida);
}

void Grafo::imprimirFechoTransitivoIndireto(ofstream &arquivoSaida, int idNo)
{
    vector<int> fechoTransitivo;
    vector<bool> visitados(this->ordem, false);

    stack<int> pilha;
    pilha.push(idNo);

    while (!pilha.empty())
    {
        int currentNode = pilha.top();
        pilha.pop();

        if (!visitados[currentNode])
        {
            visitados[currentNode] = true;
            fechoTransitivo.push_back(currentNode);
        }

        No *noOrigem = this->getNoRaiz();
        while (noOrigem != nullptr)
        {
            Aresta *aresta = noOrigem->getPrimeiraAresta();
            while (aresta != nullptr)
            {
                if (aresta->getIdNoDestino() == currentNode && !visitados[noOrigem->getIdNo()])
                {
                    pilha.push(noOrigem->getIdNo());
                }
                aresta = aresta->getProxAresta();
            }
            noOrigem = noOrigem->getProxNo();
        }
    }

    gravarArquivoSaida(fechoTransitivo, arquivoSaida);
}

float Grafo::dijkstra(int origem, int destino)
{
    std::vector<float> dist(ordem, std::numeric_limits<float>::max());
    std::set<std::pair<float, int>> filaPrioridade;

    dist[origem] = 0.0f;
    filaPrioridade.insert({0.0f, origem});

    while (!filaPrioridade.empty())
    {
        int u = filaPrioridade.begin()->second;
        filaPrioridade.erase(filaPrioridade.begin());

        for (Aresta *aresta = getNoById(u)->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            int v = aresta->getIdNoDestino();
            float pesoAresta = static_cast<float>(aresta->getPesoAresta());
            if (dist[u] + pesoAresta < dist[v])
            {
                filaPrioridade.erase({dist[v], v});
                dist[v] = dist[u] + pesoAresta;
                filaPrioridade.insert({dist[v], v});
            }
        }
    }

    if (dist[destino] == std::numeric_limits<float>::max())
    {
        std::cout << "Nao ha caminho entre os nos " << origem << " e " << destino << std::endl;
        return 0.0f;
    }

    return dist[destino];
}

void Grafo::minimalPathByFloyd(int id_one, int id_two)
{
    int numVertices = this->getOrdem();
    vector<vector<float>> dist(numVertices, vector<float>(numVertices, FLT_MAX));

    for (int i = 0; i < numVertices; i++)
    {
        dist[i][i] = 0;
        No *node = getNoById(i + 1);
        Aresta *edge = node->getPrimeiraAresta();

        while (edge != nullptr)
        {
            dist[i][edge->getIdNoDestino() - 1] = edge->getPesoAresta();
            edge = edge->getProxAresta();
        }
    }

    for (int k = 0; k < numVertices; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (dist[i][k] != FLT_MAX && dist[k][j] != FLT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int node_id_one = id_one - 1;
    int node_id_two = id_two - 1;

    if (dist[node_id_one][node_id_two] != FLT_MAX)
    {
        cout << "O caminho minimo entre os nas " << id_one << " e " << id_two << " é: " << dist[node_id_one][node_id_two] << endl;
    }
    else
    {
        cout << "Nao ha caminho entre os nos " << id_one << " e " << id_two << endl;
    }
}

void Grafo::minimalSpanningTreeByPrimAlgorithm()
{
    // Verifique se o grafo é ponderado e não direcionado
    if (!weightArc || digrafo)
    {
        std::cerr << "O grafo deve ser ponderado e nao direcionado para usar o algoritmo de Prim." << std::endl;
        return;
    }

    int V = ordem;                                              // Número de vértices no grafo
    std::vector<Aresta *> mst;                                  // Árvore Geradora Mínima
    std::vector<int> chave(V, std::numeric_limits<int>::max()); // Chaves de custo mínimo para cada vértice
    std::vector<int> parent(V, -1);                             // Vértices pai na Árvore Geradora Mínima
    std::vector<bool> inMST(V, false);                          // Vértices incluídos na Árvore Geradora Mínima

    // A raiz da Árvore Geradora Mínima pode ser escolhida arbitrariamente
    int raiz = 0;
    chave[raiz] = 0;

    for (int count = 1; count < V; count++)
    {
        // Escolha o vértice com a chave mínima que ainda não está na Árvore Geradora Mínima
        int u = minKey(chave, inMST);

        // Marque o vértice escolhido como incluído na Árvore Geradora Mínima
        inMST[u] = true;

        // Para cada vértice adjacente a u, se a aresta tiver um peso menor do que a chave atual,
        // atualize a chave do vértice
        for (Aresta *a = getNoById(u + 1)->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
        {
            int v = a->getIdNoDestino();
            int peso = a->getPesoAresta();
            if (!inMST[v] && peso < chave[v])
            {
                parent[v] = u + 1;
                chave[v] = peso;
            }
        }
    }

    for (int i = 1; i < V; i++)
{
    // Aqui, acessamos o nó de origem diretamente do vetor parent
    int destino = i;
    int peso = chave[i];

    // Adicione a aresta à Árvore Geradora Mínima
    Aresta *aresta = new Aresta(destino, peso);  // Supondo que você tenha uma classe Aresta para representar arestas
    mst.push_back(aresta);
}

    // Imprima a Árvore Geradora Mínima
    for (Aresta *aresta : mst)
    {
        int origem = parent[aresta->getIdNoDestino()]; // Obtenha o nó de origem da aresta
        int destino = aresta->getIdNoDestino();
        int peso = aresta->getPesoAresta();

        // Imprima as informações da aresta
        std::cout << "Aresta: " << origem << " - " << destino << " Peso: " << peso << std::endl;
    }

    // Lembre-se de liberar a memória das Arestas que você criou
    for (Aresta *aresta : mst)
    {
        delete aresta;
    }
}
int Grafo::minKey(const std::vector<int> &chave, const std::vector<bool> &inMST)
{
    int V = chave.size();
    int min = std::numeric_limits<int>::max();
    int min_index;

    for (int v = 0; v < V; v++)
    {
        if (!inMST[v] && chave[v] < min)
        {
            min = chave[v];
            min_index = v;
        }
    }

    return min_index;
}