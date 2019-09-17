#include <iostream>
#include "blackbox.h"

int bfs_graph()
{ 
  int expandido = 0;
  
  State *teste = new State("0 6 1 7 4 2 3 8 5");
  Node *raiz = new Node(NULL, teste, 0);
  
  queue<Node*> open;
  open.push(raiz);
  
  unordered_set <unsigned long long> closed;
  closed.insert(teste->getState());
  
  while(!open.empty()){
    Node* n = open.front();
    open.pop();
    
    State steste = n->getState();
    
    vector<State*> successors;
    succ(*n,&successors);
    
    expandido++;
    
    while(!successors.empty()){
        State *s_linha = successors.back();      
        Node *n_linha;
        
        if(closed.find(s_linha->getState())== closed.end()){
          closed.insert(s_linha->getState());
          int new_g = n->getG() + 1;
          n_linha = new Node(n, s_linha, new_g);
          open.push(n_linha);
        }
      
        if(is_goal(*s_linha)){
          cout << "goal reached! Nodos expandidos: " << expandido << " custo: " << n_linha->getG()
               << "\n";
          s_linha->printState();
          extract_path(n_linha);
          return 0;
        }
        
        successors.pop_back();
    }   
  }
  return -1;
}