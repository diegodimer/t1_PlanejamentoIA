#include <iostream>
#include "blackbox.h"

int expandido = 0;

Node* depth_limited_search(Node *n, int depth_limit)
{
    
  if (is_goal(n->getState())){
      return n;
  }
  
  
  if(depth_limit > 0){
      
    vector<State*> successors;
    succ(*n, &successors);
      
    expandido++;
    
    while(!successors.empty()){
        
        State* s_linha = successors.back();
        
        
        int new_g = n->getG() + 1;
        Node* n_linha = new Node(n, s_linha,new_g);
        
        Node* solution = depth_limited_search(n_linha,depth_limit-1);
        
        if(solution != NULL){
            return solution;
        }
        
        delete n_linha;
        
        successors.pop_back();
    }
  }
  return NULL;
}
// matematicamente impossivel esse algoritmo retornar 20k expansoes para um caminho com 16 passos
// para o iterative deepening chegar em 16 ele primeiro foi executado com 15 passos (sem sucesso)
// isso quer dizer que uma sequencia de 1 + 2¹ + 2² ... + exp(2,14) nodos foram expandidos, no minimo
// a soma dessa sequencia da exp(2,15) - 1 = 32767
// ou seja, mais que 20k
// entao ou o algoritmo do enunciado tem alguma otimizaçao ou o resultado esperado pro iterative deepening foi escrito errado
int iterative_deepening(){
    
  State *teste = new State("0 6 1 7 4 2 3 8 5");
  //State *teste = new State("5 0 2 6 4 8 1 7 3");  
    
  Node *raiz = new Node(NULL, teste, 0);
  
  int iteration = 0;
  Node* solution;
    
  int found = 0;
    
  while(found==0 && iteration < 50000){  
      
    solution = depth_limited_search(raiz,iteration);
    if(solution != NULL){
        found++;
    }
    cout << "terminado dls com profundidade " << iteration << " custo: " << expandido
         << "\n";
    iteration++;
  }
  if(found==0)
      return -1;
  else{
      cout << "goal reached! Nodos expandidos: " << expandido << " custo: " << solution->getG()
           << "\n";
      solution->getState().printState();
      extract_path(solution);
      return 0;
  }
    
}
  