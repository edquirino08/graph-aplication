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
    this->numAresta = 0;
}

Grafo::Grafo(bool isDigrafo)
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = isDigrafo;
    this->weigthNo = 0;
    this->weightArc = 0;
    this->numAresta = 0;
}

Grafo::Grafo(bool isDigrafo, bool weightArco)
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = isDigrafo;
    this->weightArc = weightArco;
    this->weigthNo = 0;
    this->numAresta = 0;
}

Grafo::Grafo(int order, bool directed, bool weightedEdge, bool weightedNode)
{
    this->ordem = order;
    this->noRaiz = nullptr;
    this->digrafo = directed;
    this->weigthNo = weightedNode;
    this->weightArc = weightedEdge;
    this->numAresta = 0;
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

bool Grafo::isDigrafo()
{
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

    for (std::vector<int>::size_type i = 0; i < v.size(); i++)
    {
        arquivoSaida << v[i];
        if (i < v.size() - 1)
        {
            arquivoSaida << ",";
        }
    }

    arquivoSaida << std::endl;
}

//------funções primeira etapa-----//
void Grafo::imprimirFechoTransitivoDireto(ofstream &arquivoSaida, int idNo)
{
    vector<int> feixoTransitivo;
    feixoTransitivo.push_back(idNo);

    // Certifique-se de que visitados seja acessível
    vector<bool> visitados(this->ordem, false);

    No *node = getNoById(idNo);

    if (node == nullptr)
    {
        cout << "Erro! No nao encontrado." << endl;
        return;
    }

    Aresta *aresta = node->getPrimeiraAresta();
    int visitadosCount = 0;

    while (aresta != nullptr)
    {
        if (visitadosCount < this->ordem && !visitados[aresta->getIdNoDestino()])
        {
            visitados[aresta->getIdNoDestino()] = true;
            visitadosCount++;
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

void Grafo::dijkstra(int origem, int destino)
{
    if (!this->getWeightedEdge())
    {
        cerr << "O algoritmo de Dijkstra requer um grafo com arestas ponderadas." << endl;
        return;
    }

    vector<float> dist(this->getOrdem(), numeric_limits<float>::max());
    vector<int> pai(this->getOrdem(), -1);
    vector<bool> visitado(this->getOrdem(), false);

    dist[origem - 1] = 0;

    for (int count = 0; count < this->getOrdem() - 1; count++)
    {
        int u = -1;

        for (int i = 0; i < this->getOrdem(); i++)
        {
            if (!visitado[i] && (u == -1 || dist[i] < dist[u]))
            {
                u = i;
            }
        }

        if (u == -1 || dist[u] == numeric_limits<float>::max())
        {
            cerr << "Grafo desconexo ou inalcancavel a partir da origem." << endl;
            return;
        }

        visitado[u] = true;

        for (Aresta *aresta = this->getNoById(u + 1)->getPrimeiraAresta(); aresta; aresta = aresta->getProxAresta())
        {
            int v = aresta->getIdNoDestino() - 1;
            float peso = aresta->getPesoAresta();

            if (!visitado[v] && dist[u] + peso < dist[v])
            {
                dist[v] = dist[u] + peso;
                pai[v] = u;
            }
        }
    }

    cout << "Caminho mais curto de " << origem << " para " << destino << ": " << dist[destino - 1] << endl;
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
        cout << "O caminho minimo entre os nos " << id_one << " e " << id_two << " eh: " << dist[node_id_one][node_id_two] << endl;
    }
    else
    {
        cout << "Nao ha caminho entre os nos " << id_one << " e " << id_two << endl;
    }
}

bool Grafo::existeAresta(int idNoOrigem, int idNoDestino)
{
    No *noOrigem = getNoById(idNoOrigem);
    if (noOrigem)
    {
        for (Aresta *a = noOrigem->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
        {
            if (a->getIdNoDestino() == idNoDestino)
            {
                return true;
            }
        }
    }
    return false;
}

Grafo *Grafo::getVerticeInduzido()
{
    Grafo *subgrafo = new Grafo(false, true);

    for (int i = 1; i <= ordem; i++)
    {
        subgrafo->insereNo(i);
    }

    for (int i = 1; i <= ordem; i++)
    {
        for (Aresta *a = getNoById(i)->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
        {
            int destino = a->getIdNoDestino();

            if (!subgrafo->existeAresta(i, destino))
            {
                subgrafo->insertAresta(i, destino, a->getPesoAresta(), this->isDigrafo());
            }
        }
    }

    return subgrafo;
}

void Grafo::minimalSpanningTreeByPrimAlgorithm(Grafo *g)
{
    if (!g->getWeightedEdge())
    {
        cout << "O algoritmo de Prim só pode ser aplicado a grafos ponderados." << endl;
        return;
    }

    int ordem = g->getOrdem();

    bool *inclusoNaAGM = new bool[ordem];

    float *custoMinimo = new float[ordem];

    int *pai = new int[ordem];

    for (int i = 0; i < ordem; i++)
    {
        custoMinimo[i] = FLT_MAX;
        pai[i] = -1;
        inclusoNaAGM[i] = false;
    }

    int noInicial = rand() % ordem;
    custoMinimo[noInicial] = 0;

    for (int i = 0; i < ordem - 1; i++)
    {
        int u = -1;
        for (int j = 0; j < ordem; j++)
        {
            if (!inclusoNaAGM[j] && (u == -1 || custoMinimo[j] < custoMinimo[u]))
            {
                u = j;
            }
        }

        inclusoNaAGM[u] = true;

        for (int v = 0; v < ordem; v++)
        {
            if (!inclusoNaAGM[v] && g->existeAresta(u, v))
            {
                float pesoAresta = g->getWeightedEdge();
                if (pesoAresta < custoMinimo[v])
                {
                    custoMinimo[v] = pesoAresta;
                    pai[v] = u;
                }
            }
        }
    }

    for (int i = 0; i < ordem; i++)
    {
        if (pai[i] != -1)
        {
            cout << "Aresta: " << pai[i] << " - " << i << " | Peso: " << custoMinimo[i] << endl;
        }
    }

    delete[] inclusoNaAGM;
    delete[] custoMinimo;
    delete[] pai;
}

void Grafo::agmByKruskal(Grafo *grafo)
{
    int numVertices = grafo->getOrdem();
    vector<int> subarvores(numVertices + 1, -1);

    vector<pair<int, int>> listaArestas;
    for (int i = 1; i <= numVertices; i++)
    {
        No *no = grafo->getNoById(i);
        Aresta *aresta = no->getPrimeiraAresta();
        int indiceAresta = 1;
        while (aresta != nullptr)
        {
            listaArestas.push_back(make_pair(indiceAresta, aresta->getPesoAresta()));
            aresta = aresta->getProxAresta();
            indiceAresta++;
        }
    }

    auto compareArestas = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second < b.second;
    };

    sort(listaArestas.begin(), listaArestas.end(), compareArestas);

    int contador = 0;

    for (const auto &aresta : listaArestas)
    {
        int indiceAresta = aresta.first;
        int pesoAresta = aresta.second;

        Aresta *arestaAtual = grafo->getNoById(indiceAresta)->getPrimeiraAresta();
        int u = grafo->getNoById(indiceAresta)->getIdNo();
        int v = arestaAtual->getIdNoDestino();

        int raizU = u;
        int raizV = v;

        while (subarvores[raizU] != -1)
        {
            raizU = subarvores[raizU];
        }

        while (subarvores[raizV] != -1)
        {
            raizV = subarvores[raizV];
        }

        if (raizU != raizV)
        {
            cout << "Aresta: " << u << " - " << v << " Peso: " << pesoAresta << endl;
            contador++;

            subarvores[raizU] = raizV;
        }

        if (contador >= numVertices - 1)
        {
            break;
        }
    }
}

void Grafo::depthFirstSearch(ofstream &outputFile, int id)
{
    // Verifica se o nó com o ID especificado existe no grafo
    if (!procurarNoPeloId(id))
    {
        cout << "No com ID " << id << " nao encontrado no grafo." << endl;
        return;
    }

    // Vetor para controlar os nós visitados
    vector<bool> visitado(getOrdem() + 1, false);

    stack<int> pilha;

    // Empilha o nó inicial
    pilha.push(id);

    while (!pilha.empty())
    {
        int n = pilha.top();
        pilha.pop();

        // Marca o nó como visitado
        visitado[n] = true;

        No *no = getNoById(n);

        // Processa o nó
        cout << "Visitando no " << n << endl;

        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int destino = aresta->getIdNoDestino();

            if (!visitado[destino])
            {
                // Aresta de avanço
                cout << "Aresta de avanco: " << n << " -> " << destino << endl;
                pilha.push(destino);
            }
            else if (destino != no->getIdNo() && visitado[destino])
            {
                // Aresta de retorno
                cout << "Aresta de retorno: " << n << " -> " << destino << endl;
            }

            aresta = aresta->getProxAresta();
        }
    }
}

void Grafo::calculaMedidasDoGrafo(Grafo *g)
{
    // Verifica se o grafo é ponderado nas arestas
    if (!g->getWeightedEdge())
    {
        cout << "O grafo não é ponderado nas arestas." << endl;
        return;
    }

    int ordem = g->getOrdem();
    int raio = INT_MAX;
    int diametro = 0;
    vector<int> centro;
    vector<int> periferia;

    // Primeiro, calculamos o raio, o diâmetro, o centro e a periferia do grafo
    for (int idNo = 1; idNo <= ordem; idNo++) {
        vector<int> distancia(ordem, INT_MAX);
        No *origem = g->getNoById(idNo);
        distancia[origem->getIdNo() - 1] = 0;

        queue<No *> fila; // Fila para a busca em largura
        fila.push(origem);

        while (!fila.empty()) {
            No *no = fila.front();
            fila.pop();
            Aresta *aresta = no->getPrimeiraAresta();

            while (aresta != nullptr) {
                No *vizinho = g->getNoById(aresta->getIdNoDestino());

                if (distancia[vizinho->getIdNo() - 1] == INT_MAX) {
                    distancia[vizinho->getIdNo() - 1] = distancia[no->getIdNo() - 1] + 1;
                    fila.push(vizinho);
                }
                aresta = aresta->getProxAresta();
            }
        }

        // Atualizamos o raio e o diâmetro com base nas distâncias encontradas
        for (int d : distancia) {
            if (d != INT_MAX) {
                raio = min(raio, d);
                diametro = max(diametro, d);
            }
        }
    }

    // Agora, calculamos os nós do centro e da periferia com base no raio
    for (int idNo = 1; idNo <= ordem; idNo++) {
        vector<int> distancia(ordem, INT_MAX);
        No *origem = g->getNoById(idNo);
        distancia[origem->getIdNo() - 1] = 0;

        queue<No *> fila;
        fila.push(origem);

        while (!fila.empty()) {
            No *no = fila.front();
            fila.pop();
            Aresta *aresta = no->getPrimeiraAresta();

            while (aresta != nullptr) {
                No *vizinho = g->getNoById(aresta->getIdNoDestino());

                if (distancia[vizinho->getIdNo() - 1] == INT_MAX) {
                    distancia[vizinho->getIdNo() - 1] = distancia[no->getIdNo() - 1] + 1;
                    fila.push(vizinho);
                }
                aresta = aresta->getProxAresta();
            }
        }

        int maxDistancia = 0;
        for (int d : distancia) {
            if (d != INT_MAX) {
                maxDistancia = max(maxDistancia, d);
            }
        }

        // Adicionamos o nó ao centro se a distância máxima for igual ao raio
        // Adicionamos o nó à periferia se a distância máxima for igual ao diâmetro
        if (maxDistancia == raio) {
            centro.push_back(origem->getIdNo());
        } else if (maxDistancia == diametro) {
            periferia.push_back(origem->getIdNo());
        }
    }

    // Imprimimos as medidas calculadas
    cout << "Raio: " << raio << endl;
    cout << "Diâmetro: " << diametro << endl;
    cout << "Centro: ";
    for (int c : centro) {
        cout << c << " ";
    }
    cout << endl;
    cout << "Periferia: ";
    for (int p : periferia) {
        cout << p << " ";
    }
    cout << endl;
}
