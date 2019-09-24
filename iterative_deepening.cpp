#include <iostream>
#include "blackbox.h"

int expandido = 0;
int heuristica_ac4;
int heuristica_ind4;


Node* depth_limited_search(Node *n, int depth_limit)
{
    
  if (is_goal(n->getState().getState())){
      return n;
  }
  
  
  if(depth_limit > 0){
      
    vector<State*> successors;
    succ(*n, &successors);
      
    expandido++;
    
    while(!successors.empty()){
        
        State* s_linha = successors.back();
        successors.pop_back();
        
        int new_g = n->getG() + 1;
        Node* n_linha = new Node(n, s_linha,new_g);
        heuristica_ind4++;
        heuristica_ac4+=n_linha->getH();
        Node* solution = depth_limited_search(n_linha,depth_limit-1);
        
        if(solution != NULL){
          return solution;
        }
        
        delete n_linha;
        
        
    }
  }
  return NULL;
}

int iterative_deepening(string _state){
    
  //State *teste = new State("0 6 1 7 4 2 3 8 5");
  //State *teste = new State("5 0 2 6 4 8 1 7 3");  
  //State *teste = new State("2 4 7 0 3 6 8 1 5");  

  State *teste = new State(_state);
  Node *raiz = new Node(NULL, teste, 0);
  int h_inicial = raiz->getH();
  heuristica_ind4=1;
  heuristica_ac4=h_inicial;
  
  int iteration = 0;
  Node* solution;
    
  int found = 0;
    
  while(found==0){  
      
    solution = depth_limited_search(raiz,iteration);
    if(solution != NULL){
        found++;
    }
    iteration++;
  }
  if(found==0)
      return -1;
  else{
      print_results(*solution, h_inicial, (float)heuristica_ac4/heuristica_ind4);
      return 0;
  }
    
}
  