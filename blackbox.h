#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>

#define PUZZLE 3
#define GOAL 305419896
using namespace std;
/* 

  0     1    2    3    4    5    6    7    8
0000 0001 0010 0011 0100 0101 0110 0111 1000= 36 bits para armazenar o estado (305419896 em decimal é o goal)

   0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 = 64 bits para armazenar o estado (81985529216486895 em decimal é o goal)

*/

class State;      // classe que representa o estado
class Node;       // classe que representa um nodo (nodo tem um estado parte dele)
class Comparador; // classe que implementa o comparador usado no open set

int calc_h(State);
bool is_goal(State);
void succ(Node, vector<Node>);

class State
{

  unsigned long long state; // estado representado com 64-bit
  int h;
  unsigned char posicao_zero; // os 4 primeiros bits são a linha, os 4 seguintes a coluna

public:
  State(string _state);
  State(unsigned long long _state, unsigned char _posicao_zero);
  State();
  long long getState() const;
  int getH() const ;
  void setH(int _h);
  unsigned char getPosZero() const;

  /* Função que printa o estado (fins de debug) */
  void printState() const
  ;
};

class Node
{
  int g;
  State *state;
  // pode tirar \/
  Node *whereFrom;

public:
  static unsigned int index;
  unsigned int my_index;
  int getG() const ;
  int getF() const ;
  int getH() const ;
  void setG(int _g) ;
  void setH(int _h);
  unsigned int getindex() const;
  State getState() const;
  Node(State *_s);
  Node(State *_s, int _g);
  Node(Node *_pai, State *_s, int _g);
  Node* getWhereFrom();
};


class Comparador
{
public:
  int operator()(const Node *e1, Node *e2);
};
class Comparador_gbfs
{
  public:
    int operator()(const Node *n1, const Node *n2);
};

struct State_hash {
public:
	size_t operator()(const State & e1) const;
};

struct State_equal {
public:
	bool operator()(const State &e1, const State &e2) const;
};

bool is_goal(State s);

int calc_h(State s);

State *swap_board(unsigned long long state_original, short int zero_linha, short int zero_coluna, short int new_zero_linha, short int new_zero_coluna, short int pos_zero_state);

void succ(Node n, vector<State *> *suc);

void extract_path(Node* n);


#endif
