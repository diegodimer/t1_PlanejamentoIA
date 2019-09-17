#include <iostream>
#include "astar.h"
#include "blackbox.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>	
#include <queue>

int A_STAR()
{
  State *teste = new State("0 6 1 7 4 2 3 8 5"); // esse estado é 30674020401 em decimal
  int nodos_expandidos = 0;
  int viz = 0;
  priority_queue<Node*, vector<Node*>, Comparador> open;
  std::unordered_set<State, State_hash, State_equal> closed;

  Node *raiz = new Node(NULL, teste, 0);
  open.push(raiz);
  cout<<"HEURISTICA NO ESTADO INICIAL: " << raiz->getH() << endl;
  int iteracoes = 0;
  while (!open.empty())
  {
    iteracoes++;
    Node *n = open.top();
    open.pop();
    State n_state = n->getState();
    if (closed.find(n_state) == closed.end()) // não ta no closed set
    {
      closed.insert(n_state);
      if (is_goal(n_state))
      {
        cout << "GOAL REACHED" << endl;
        n_state.printState();
        cout << "COST : " << n->getF() << " EXPANDIDOS: " << nodos_expandidos << " CLOSED SIZE: " << closed.size() << endl;
        extract_path(n);
        return 0;
      }
      vector<State *> sucessores;
      succ(*n, &sucessores);
      nodos_expandidos++;
      while (!sucessores.empty())
      {
        State *estado = sucessores.back();
        int new_g = n->getG()+1;// n->getH() + 0; // 1 é o custo da transição
        Node *n_linha = new Node(n, estado, new_g);
        sucessores.pop_back();
        open.push(n_linha);
      }
    }
  }
}
