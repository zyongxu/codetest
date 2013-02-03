#include "graph.h"

#include <cstdio>
#include <cstdlib>
//#include <other_lib>
//#include <my_lib>

Vertex::~Vertex() {
  if(edges_) {
    Edge *cur = edges_;
    Edge *next = NULL;
    while(cur) {
      next = cur->next();
      delete cur;
      cur = next;
    }
  }
}

void Vertex::AddEdge(Vertex *dst) {
  Edge *newedge = new Edge(dst);
  if(!edges_) {
    edges_ = newedge;
    return;
  }

  Edge *tail = edges_;
  while (tail->next())
    tail = tail->next();

  tail->set_next(newedge);
}

Graph::~Graph() {
  if (adj_list_)
    delete adj_list_;
  return;
}

Vertex* Graph::VertexList(int i) {
  Vertex *temp = adj_list_;
  int count = 0;
  while(temp && count < i) {
    temp = temp->next();
    count++;
  }
  
  if (count < i)
    return NULL;
  else
    return temp;
}

void Graph::AddVertex(Vertex *new_vertex) {
  if(!new_vertex)
    return;

  Vertex *temp = adj_list_;
  while(temp->next())
    temp = temp->next();
  
  temp->set_next(new_vertex);
}

void Graph::Build() {
  if(!adj_list_)
    adj_list_ = new Vertex(0);

  for(int i=1; i<6; i++) {
    Vertex *temp = new Vertex(i);
    AddVertex(temp);
  }
  
  Vertex *cur = VertexList(0);
  cur->AddEdge(VertexList(1));
  cur->AddEdge(VertexList(2));
  cur = VertexList(1);
  cur->AddEdge(VertexList(0));
  cur = VertexList(2);
  cur->AddEdge(VertexList(0));
  cur->AddEdge(VertexList(3));
  cur->AddEdge(VertexList(4));
  cur = VertexList(3);
  cur->AddEdge(VertexList(2));
  cur->AddEdge(VertexList(4));
  cur->AddEdge(VertexList(5));
  cur = VertexList(4);
  cur->AddEdge(VertexList(2));
  cur->AddEdge(VertexList(3));
  cur->AddEdge(VertexList(5));
  cur = VertexList(5);
  cur->AddEdge(VertexList(3));
  cur->AddEdge(VertexList(4));
}

void Graph::Print() {
  Vertex *tempV =  adj_list_;
  while (tempV) {
    printf("Adj[%d] ", tempV->key());
    Edge *tempE = tempV->edges();
    while(tempE) {
      printf("-->%d", tempE->connects()->key());
      tempE = tempE->next();
    }
    tempV = tempV->next();
    printf("\n");
  }
}

Tree<Vertex*>* Graph::BFS(int vindex) {
  int queue[100]; //using an array as a queue
  int qtail=-1, qhead=0;
  int cur_index = -1;

  Vertex *adjV = NULL;
  Vertex *curV = VertexList(vindex);
  if(!curV) {
    printf("invalid root!\n");
    return NULL;
  }

  BFS_tree_ = new Tree<Vertex*>();
  /* set root */
  curV->set_BFS_d(0);
  curV->set_BFS_p(NULL);
  printf("insert %d to the tree\n", curV->key());
  BFS_tree_->Insert(NULL, curV);
  curV->set_visited(1);

  /* enqueue root */
  Enqueue(queue,qtail,vindex);

  while((cur_index = Dequeue(queue, qhead, qtail)) >= 0) {
    curV = VertexList(cur_index);

    /* go through the adj list of curV */
    Edge *tempE = curV->edges();
    while(tempE) {
      adjV = tempE->connects();
      if((adjV != NULL) && !(adjV->visited()) ) {
        adjV->set_BFS_d(curV->BFS_d());
        adjV->set_BFS_p(curV);
        printf("insert %d to the tree, as child of %d\n", adjV->key(), curV->key());
        BFS_tree_->Insert(curV, adjV);
        adjV->set_visited(1);
        Enqueue(queue, qtail, adjV->key());
      }
      tempE = tempE->next();
      adjV = NULL;
    }
  }
  return BFS_tree_;
}

