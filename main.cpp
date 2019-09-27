#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>

#include "blackbox.h"
#include "bfs_graph.h"
#include "astar.h"
#include "idastar.h"
#include "iterative_deepening.h"
#include "greedy_bfs.h"


using namespace std;
/* 

  0     1    2    3    4    5    6    7    8
0000 0001 0010 0011 0100 0101 0110 0111 1000= 36 bits para armazenar o estado (305419896 em decimal é o goal)

   0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 = 64 bits para armazenar o estado (81985529216486895 em decimal é o goal)

*/

typedef int (*FnPtr)(string);

int main(int argc, char *argv[])
{
  //int main(int argc, char *argv[]){
  //  priority_queue<Node*, vector<Node*>, Comparador> open;
  //  State *s1 = new State("0 6 1 7 4 2 3 8 5");
  //  State *s2 = new State("0 6 1 7 4 2 3 8 5");
  //  Node *n2 = new Node(NULL, s2, 1);
  //  Node *n3 = new Node(NULL, s1, 2);
  //  Node *n4 = new Node(NULL, s1, 3);
  //  Node *n5 = new Node(NULL, s1, 3);
  //  Node *n6 = new Node(NULL, s1, 0);
  //  n2->setH(9);
  //  open.push( n2 );
  //  open.push( n3 );
  //  open.push( n4 );
  //  open.push( n5 );
  //  open.push( n6 );
  // while( !open.empty()){
  //   Node *top = open.top();
  //   cout << " topo: " << "index: " << top->getindex() << " F: " << top->getF() << " H:" << top->getH()  << endl;
  //   open.pop();
  // }
  //A_STAR();
  //bfs_graph();

  std::map<std::string, FnPtr> myMap;
  myMap["-astar"] = A_STAR;
  myMap["-bfs"] = bfs_graph;
  myMap["-idastar"] = IDASTAR;
  myMap["-idfs"] = iterative_deepening;
  myMap["-gbfs"] = greedy_bfs;
  string algorithm = string(argv[1]);
  string command;
  for (int i = 2; i < argc; i++)
  {
    command += argv[i];
    if (command[command.length()-1] != ',')
      command += " ";
  }
  std::istringstream iss(command);
  std::string token;
  while (std::getline(iss, token, ','))
  {
    myMap[algorithm](token);
  }

  /*
  greedy_bfs();
  State *teste = new State("2 4 7 0 3 6 8 1 5"); 
  cout << calc_h(*teste) << "\n";
   */
  return 0;
}
