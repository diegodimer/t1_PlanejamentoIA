#include <iostream>
#include "blackbox.h"

int greedy_bfs(){

  State *teste = new State("0 6 1 7 4 2 3 8 5");
  //State *teste = new State("5 0 2 6 4 8 1 7 3");  
    
  Node *raiz = new Node(NULL, teste, 0);
  
  int expandido = 0;
    
  priority_queue<Node*,vector<Node*>,Comparador_gbfs> open;  
  open.push(raiz);
    
  unordered_set<unsigned long long> closed;
  
  while(!open.empty()){
    
      Node* n = open.top();
      open.pop();
      
      
      if(closed.find(n->getState().getState())==closed.end()){
        
        closed.insert(n->getState().getState());
          
        if(is_goal(n->getState())){
          cout << "goal reached! Nodos expandidos: " << expandido << " custo: " << n->getG()
               << "\n";
          extract_path(n);
          return 0;
        }
          
        vector<State*> successors;
        succ(n,&successors);
        
        while(!successors.empty()){
            State* s_linha = successors.back();
            successors.pop_back();
            
            int new_g = n->getG() + 1;
            Node* n_linha = new Node(n, s_linha, new_g);
            
            open.insert(n_linha);
        } 
      }
  }
  return -1;    
}
    
