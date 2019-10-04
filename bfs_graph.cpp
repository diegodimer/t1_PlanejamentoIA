#include <iostream>
#include "blackbox.h"
int heuristica_ac1;
int heuristica_ind1;


int bfs_graph(string _state)
{ 
  State *teste = new State(_state);
  Node *raiz = new Node(NULL, teste, 0);
  int h_inicial = raiz->getH();
  heuristica_ac1 = h_inicial;
  heuristica_ind1 = 1;
  queue<Node*> open;
  open.push(raiz);
  
  unordered_set <unsigned long long> closed;
  closed.insert(teste->getState());
  
  while(!open.empty()){
    Node* n = open.front();
    open.pop();
    
    //State steste = n->getState();
    
    vector<State*> successors;
    succ(*n,&successors);
    
    while(!successors.empty()){
        State *s_linha = successors.back();      
        Node *n_linha;
        
        if(closed.find(s_linha->getState())== closed.end()){
          closed.insert(s_linha->getState());
          int new_g = n->getG() + 1;
          n_linha = new Node(n, s_linha, new_g);
          heuristica_ac1+=n_linha->getH();
          heuristica_ind1++;
          open.push(n_linha);
        }
      
        if(is_goal((*s_linha).getState())){
          //print_results(*n_linha, h_inicial, (float)heuristica_ac1/heuristica_ind1);
          print_results(*n_linha, h_inicial, 0);//sem heuristica nesse algortimo
          return 0;
        }
        
        successors.pop_back();
    }   
  }
  return -1;
}