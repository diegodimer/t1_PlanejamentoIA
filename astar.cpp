#include <iostream>
#include "astar.h"
#include "blackbox.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>
#include <queue>

/**
 * ASTAR
 * a idéia é igual o pseudo algoritmo: enquanto o openset (implementado como uma priority 
 * queue com um comparador que a torna uma min heap) tiver elementos o algoritmo continua
 * expandindo e gerando os sucessores daquele nodo, tendo o cuidado para não expandir 
 * estados que já estão no closed set (implementados como um unordered_set (escolhido por
 * ser mais rápido que o ordered_set). Quando chega no estado objetivo, desalocamos os 
 * ponteiros que estão no open e no closed set.
 * 
 */
int A_STAR(string _state)
{
  State teste = State(_state); // esse estado é 30674020401 em decimal
  priority_queue<Node *, vector<Node *>, Comparador> open;
    
  std::unordered_set<Node*, State_hash, State_equal> closed;

  Node *raiz = new Node(NULL, &teste, 0);
  Node *n_linha;
  open.push(raiz);
  int h_inicial = raiz->getH();
  int iteracoes = 0;
  int heuristica_ac5=h_inicial;
  int heuristica_ind5=1;
  while (!open.empty())
  {
    iteracoes++;
    Node *n = open.top();
    open.pop();
    State *n_state = n->getStatePointer();
    if (closed.find(n) == closed.end()) // não ta no closed set
    {
      closed.insert(n);
      if (is_goal(n->getState().getState()))
      {
        print_results(*n, h_inicial, (float)heuristica_ac5/heuristica_ind5);
        while(!open.empty()){
          Node *n_del = open.top();
          open.pop();
          delete n_del;
        }
          
        for (auto& it: closed) {
          delete it;
        }
        
        return 0;
      }
      vector<State *> sucessores;
      succ(*n, &sucessores);
      while (!sucessores.empty())
      {
        State *estado = sucessores.back();
        int new_g = n->getG() + 1; // n->getH() + 0; // 1 é o custo da transição
        n_linha = new Node(n, estado, new_g);
        heuristica_ind5++;
        heuristica_ac5+=n_linha->getH();
        sucessores.pop_back();
        open.push(n_linha);
      }
    }
    
  }
  cout<<"GOAL NOT REACHED"<<endl;
  return -1;
}
