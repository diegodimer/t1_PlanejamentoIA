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
    
  int teste_h=0; // bug na media h
  int teste_hacc=0; // bug na media h
  
  teste_hacc += raiz->getH();// bug na media h
  teste_h++;// bug na media h
    
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
          
        cout << "\n VALOR INDEX: " << teste_h << " VALOR ACC: " << teste_hacc << " MEDIA: " << (float)teste_hacc/teste_h << "\n";  // bug na media h, IMPRIME O VALOR CERTO
          
        return 0;
      }
      vector<State *> sucessores;
      succ(*n, &sucessores);
      while (!sucessores.empty())
      {
        State *estado = sucessores.back();
        int new_g = n->getG() + 1; // n->getH() + 0; // 1 é o custo da transição
        Node *n_linha = new Node(n, estado, new_g);
          
        teste_hacc += n_linha->getH();// bug na media h
        teste_h++;  // bug na media h
          
        sucessores.pop_back();
        open.push(n_linha);
      }
    }
    //delete n; // esse delete aqui faz o teste_hacc/teste_h  ter um valor errado, ele por algum motivo ta deletando nodos dentro da priority queue
  }
  cout<<"Goal not found!"<<endl;
}
