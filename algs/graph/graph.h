#ifndef GRAPH_H
#define GRAPH_H

#include <cstdio>
#include <cstdlib>
#include "tree.h"

/* 
 * from Google Style Guide:
 * input arguments are values or const references while output arguments are pointers
 */

/*
 * Using the adjacency list to represent a G=(V,E) in this code: 
 * An array (Adj[]) of |V| lists of vertex pointers, each list (Adj[u]) contains 
 * pointers to all vertices v, such that (u,v) is an edge in E
 */

inline void Enqueue(int *array, int &tail, int value) {
  printf("enqueue %d\n", value);
  tail++;
  array[tail]=value;
}

inline int Dequeue(int *array, int &head, int tail) {
  if(head>tail)
    return -1;

  int value = array[head];
  head++;
  printf("dequeue %d\n", value);
  return value;
}

/*   Vertices        Edges
 *      |
 *      v
 *   -------
 *   |  A  |
 *   |-----|     ---------     ----------
 *   |   --+---> | &B | -+---> | &D | 0 |
 *   |-----|     ---------     ----------
 *   |  |  |
 *   ---+---
 *      |
 *      v
 *   -------
 *   |  B  |
 *   |-----|
 *   |  0  |
 *   |-----|
 *   |  |  |
 *   ---+---
 *      |
 *      v
 *   -------
 *   |  C  |
 *   |-----|     ----------
 *   |   --+---> | &F | 0 |
 *   |-----|     ----------
 *   |  0  |
 *   -------
 */

class Edge;

/*************************************
 * Vertex is a linked list of all the
 * vertices in a graph
 *************************************/
class Vertex {
private:
  int key_;      //the data stored in this vertex
  Edge *edges_;  //pointers to adjacency vertices
  Vertex *next_; //the next vertex in the adj_list
  /* Three BFS extra fields */
  bool visited_;
  int BFS_d_;
  Vertex *BFS_p_;

public:
  Vertex(int k): 
    key_(k), edges_(NULL), next_(NULL), 
    visited_(0), BFS_d_(0x7FFFFFFF), BFS_p_(NULL)
  {}
  ~Vertex();
  inline int key() { return key_; }
  inline void set_key(int newk) { key_=newk; }
  inline Edge* edges() { return edges_; }
  inline Vertex* next() { return next_; }
  inline void set_next(Vertex* v) { next_ = v; }
  inline bool visited() { return visited_; }
  inline void set_visited(bool b) { visited_ = b; }
  inline int BFS_d() { return BFS_d_; }
  inline void set_BFS_d(int d) { BFS_d_ = d; }
  inline Vertex* BFS_p() { return BFS_p_; }
  inline void set_BFS_p(Vertex* v) { BFS_p_ = v; }
  void AddEdge(Vertex *);
};

/************************************
 * An edge is a pointer to a vertex *
 ************************************/
class Edge {
private:
  Vertex *connects_; //the vertex to which this vertex is linked by this edge
  Edge *next_;       //the next edge in a adjacency list

public:
  Edge(): connects_(NULL), next_(NULL) {}
  Edge(Vertex *v): connects_(v), next_(NULL) {}
  ~Edge() {}

  inline Vertex* connects() { return connects_; }
  inline Edge* next() { return next_; }
  inline void set_next(Edge *e) { next_ = e; }
};

/***********************************
 * Graph is is pointer to the first
 * vertex in the Vertex linked list
 ***********************************/
class Graph {
private:
  Vertex *adj_list_;
  Tree<Vertex*> *BFS_tree_;

public:
  Graph(Vertex *v): adj_list_(v), BFS_tree_(NULL) {}
  ~Graph();
  Vertex* VertexList(int i);
  void AddVertex(Vertex*);
  void Build();
  void Print();
  Tree<Vertex*>* BFS(int vindex);
};

#endif //GRAPH_H
