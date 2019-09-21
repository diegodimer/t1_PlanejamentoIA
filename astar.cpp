#include <iostream>
#include "astar.h"
#include "blackbox.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>
#include <queue>
int A_STAR(string _state)
{
  State *teste = new State(_state); // esse estado é 30674020401 em decimal
  priority_queue<Node *, vector<Node *>, Comparador> open;
  std::unordered_set<unsigned long long, State_hash, State_equal> closed;

  Node *raiz = new Node(NULL, teste, 0);
  open.push(raiz);
  int h_inicial = raiz->getH();
  int iteracoes = 0;
  while (!open.empty())
  {
    iteracoes++;
    Node *n = open.top();
    open.pop();
    unsigned long long n_state = n->getState().getState();
    if (closed.find(n_state) == closed.end()) // não ta no closed set
    {
      closed.insert(n_state);
      if (is_goal(n_state))
      {
        print_results(*n, h_inicial);
        return 0;
      }
      vector<State *> sucessores;
      succ(*n, &sucessores);
      while (!sucessores.empty())
      {
        State *estado = sucessores.back();
        int new_g = n->getG() + 1; // n->getH() + 0; // 1 é o custo da transição
        Node *n_linha = new Node(n, estado, new_g);
        sucessores.pop_back();
        open.push(n_linha);
      }
    }
    delete n;
  }
  cout<<"Goal not found!"<<endl;
}
