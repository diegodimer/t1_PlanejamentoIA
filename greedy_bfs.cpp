#include <iostream>
#include "blackbox.h"

int heuristica_ac2;
int heuristica_ind2;


int greedy_bfs(string _state){

  //State *teste = new State("0 6 1 7 4 2 3 8 5");
  State *teste = new State(_state);
  //State *teste = new State("2 4 7 0 3 6 8 1 5");  
    
  Node *raiz = new Node(NULL, teste, 0);
  priority_queue<Node*,vector<Node*>,Comparador_gbfs> open;
  std::unordered_set<Node*, State_hash, State_equal> closed; 
  
    
  int h_inicial = raiz->getH();
  heuristica_ac2 = h_inicial;
  heuristica_ind2 = 1;
  open.push(raiz);
    
  while(!(open.empty())){
      
      Node* n = open.top();
      open.pop();
      
      
    if (closed.find(n) == closed.end()) // não ta no closed set
    {
        
        closed.insert(n);
          
        if(is_goal(n->getState().getState())){
          print_results(*n, h_inicial, (float)heuristica_ac2/heuristica_ind2);
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
          
        vector<State*> successors;
        succ(*n,&successors);
          
        while(!successors.empty()){
            State* s_linha = successors.back();
            int new_g = n->getG() + 1;
            Node* n_linha = new Node(n, s_linha, new_g);
            heuristica_ind2++;
            heuristica_ac2+=n_linha->getH();
            successors.pop_back();
            open.push(n_linha);
            
        } 
    }
      
  }
  return -1;    
}
    
