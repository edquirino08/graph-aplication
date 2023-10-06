#include <iostream>
#include "../include/Grafo.h"

int main()
{

  std::cout << "Hello, World!" << std::endl;

  Grafo *grafo = new Grafo(false);
  grafo->insereNo(1);
  grafo->insereNo(4);
  grafo->insereNo(5);
  grafo->insereNo(6);

  grafo->insereNo(7);

  cout << grafo->getNoById(7)->getIdNo() << endl;

  return 0;
}
