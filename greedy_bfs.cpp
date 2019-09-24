#include <iostream>
#include "blackbox.h"

int heuristica_ac2;
int heuristica_ind2;


int greedy_bfs(){

  //State *teste = new State("0 6 1 7 4 2 3 8 5");
  State *teste = new State("5 0 2 6 4 8 1 7 3");
  //State *teste = new State("2 4 7 0 3 6 8 1 5");  
    
  Node *raiz = new Node(NULL, teste, 0);
  priority_queue<Node*,vector<Node*>,Comparador_gbfs> open;
  unordered_set<unsigned long long> closed;  
  
    
  int h_inicial = raiz->getH();
  heuristica_ac2 = h_inicial;
  heuristica_ind2 = 1;
  open.push(raiz);
    
  while(!(open.empty())){
      
      Node* n = open.top();
      open.pop();
      
      
     if(closed.find(n->getState().getState())==closed.end()){
        
        closed.insert(n->getState().getState());
          
        if(is_goal(n->getState().getState())){
          print_results(*n, h_inicial, (float)heuristica_ac2/heuristica_ind2);
          //extract_path(n);
          return 0;
        }
          
        vector<State*> successors;
        succ(*n,&successors);
          
        while(!successors.empty()){
            State* s_linha = successors.back();
            successors.pop_back();

            int new_g = n->getG() + 1;
            Node* n_linha = new Node(n, s_linha, new_g);
            heuristica_ind2++;
            heuristica_ac2+=n_linha->getH();
            open.push(n_linha);
            
            
        } 
      }
      
  }
  return -1;    
}
    
