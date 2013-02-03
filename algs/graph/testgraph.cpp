#include <cstdio>
#include <cstdlib>

#include "graph.h"
#include "tree.h"

int main() {
  Graph *gra = new Graph(NULL);
  gra->Build();
  gra->Print();
  Tree<Vertex*> *bfst = gra->BFS(2);
  bfst->Print();
  return 0;
}
