#include "../include/Grafo.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

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

Grafo::Grafo(bool isDigrafo, bool weightArc)
{
    this->ordem = 0;
    this->noRaiz = nullptr;
    this->digrafo = isDigrafo;
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

void Grafo::gravarArquivoSaida(vector<int> v, ofstream &arquivoSaida)
{
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i)
    {
        arquivoSaida << v[i];
        if (i < v.size() - 1)
        {
            arquivoSaida << ", ";
        }
    }

    arquivoSaida.close();
}