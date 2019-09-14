#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>

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
  State(string _state)
  {
    state = 0;
    for (int i = 0; i < _state.length(); i++)
    {
      if (_state[i] != ' ')
      {
        unsigned char num = (unsigned char)_state[i] - '0';
        state += num;
        state = state << 4;

        if (_state[i] == '0')
        {
          unsigned char should_linha; // linha que devia estar
          int n = i / 6;
          if (n < 1)
          {
            should_linha = 0x0;
          }
          else if (n < 2)
          {
            should_linha = 0x1;
          }
          else
            should_linha = 0x2;

          unsigned char should_coluna = (i / 2) % 3;
          posicao_zero = (should_linha << 4) | should_coluna;
        }
      }
    }

    state = state >> 4; // um if ali testado n vezes é mais facil fazer 4 shifts pro outro lado depois
    h = calc_h(*this);
  }
  State(unsigned long int _state, unsigned char _posicao_zero)
  {
    state = _state;
    posicao_zero = _posicao_zero;
    h = calc_h(*this);
  }
  State() {}
  long long getState() const { return state; }
  int getH() const { return h; }
  unsigned char getPosZero() const { return posicao_zero; }

  /* Função que printa o estado (fins de debug) */
  void printState() const
  {
    unsigned long long position = 0xF00000000; // tem 8 zeros pq ignora 8 numeros pra pegar o primeiro
    unsigned long long number = 0;
    int indice = 8;
    cout << "========================"
         << "\n";
    cout << "Representação do estado: "
         << "\n";
    for (int i = 0; i < PUZZLE; i++)
    {

      for (int j = 0; j < PUZZLE; j++)
      {
        number = state & position;     // a mascara pega o primeiro numero
        number = number >> 4 * indice; // e shifta ele até a posição certa
        indice -= 1;
        int should_linha;
        if (number / PUZZLE < 1)
        {
          should_linha = 0;
        }
        else if (number / PUZZLE < 2)
        {
          should_linha = 1;
        }
        else if (number / PUZZLE < 3)
        {
          should_linha = 2;
        }
        else
        {
          should_linha = 3;
        }

        int should_coluna = number % PUZZLE;
        int h = abs(should_linha - i) + abs(should_coluna - j);
        cout << number << " (h(n): " << h << ")   ";
        position = position >> 4; // move a mascara p/ pegar o próximo numero
      }
      cout << "\n";
    }
    cout << "========================"
         << "\n";
  }
};

class Node
{
  int g;
  int f;
  State *state;

public:
  int getG() const { return g; }
  int getF() const { return g + state->getH(); }
  int getH() const { return state->getH(); }
  void setG(int _g) { g = _g; }
  void setF(int _f) { f = _f; }
  State getState() const { return *state; }
  Node(State *_s)
  {
    state = _s;
  }
};

class Comparador
{
public:
  int operator()(const Node &e1, Node &e2)
  {
    int e1F = e1.getF();
    int e2F = e2.getF();
    if (e1F > e2F)
    {
      return true;
    }
    else if (e1F == e2F)
    {
      int e1H = e1.getH();
      int e2H = e2.getH();
      if (e1H > e2H)
      {
        return true;
      }
      else if (e1H == e2H)
      {
        return true;
      }
      else
      { // NÃO é LIFO (por coisa do C++, ele não garante ordem dos elementos (não segue padrão no iterador))
        return false;
      }
    }
    else
    {
      return false;
    }
  }
};

bool is_goal(State s)
{
  return s.getState() == GOAL;
}

int calc_h(State s)
{
  unsigned long long position = 0xF00000000; // mascara
  unsigned long long number = 0;
  unsigned long long state = s.getState();
  int h_ac = 0;
  int indice = 8;
  for (int i = 0; i < PUZZLE; i++)
  {
    for (int j = 0; j < PUZZLE; j++)
    {
      number = state & position;     // a mascara pega o primeiro numero
      number = number >> 4 * indice; // e shifta ele até a posição certa
      indice -= 1;
      int should_linha; // linha que devia estar
      int n = number / PUZZLE;
      if (n < 1)
      {
        should_linha = 0;
      }
      else if (n < 2)
      {
        should_linha = 1;
      }
      else if (n < 3)
      {
        should_linha = 2;
      }
      else
      {
        should_linha = 3;
      }
      int should_coluna = number % PUZZLE;
      int h = abs(should_linha - i) + abs(should_coluna - j);
      h_ac += h;
      position = position >> 4; // move a mascara p/ pegar o próximo numero
    }
  }
  return h_ac;
}


State swap_board(unsigned long long state_original, short int zero_linha, short int zero_coluna, short int new_zero_linha, short int new_zero_coluna, short int pos_zero_state)
{
  unsigned long long mask = 0xF;
  short int pos_array_original = 3 * new_zero_linha + new_zero_coluna;                   // posição no array do state onde está o numero q vai trocar com o 0
  unsigned long long mask_dois = mask << 4 * (PUZZLE * PUZZLE - 1 - pos_array_original); // mask_dois é do tipo 0000F000 e F é onde está o número que vai trocar com o 0
  mask_dois = mask_dois & state_original;                                                // mask_dois tem o número que  vai trocar com o zero
  unsigned long long new_state = state_original & (~mask_dois);                          // faz o AND com a negação da mascara para zerar onde está o número que ia trocar com o zero
  // shifto o mask_dois até onde estava o zero antes e faço or com new_state
  short int offset = pos_array_original - pos_zero_state; // nao existe shift negativo
  if (offset < 0)
  {
    mask_dois = mask_dois >> abs(offset) * 4;
  }
  else
  {
    mask_dois = mask_dois << offset * 4;
  }
  new_state = mask_dois | new_state; // coloca o numero no lugar do zero antigo

  unsigned char new_zero_pos = (new_zero_linha << 4) + new_zero_coluna;
  State novo_estado = State(new_state, new_zero_pos);

  // novo_estado.printState();
  return novo_estado;
}

// gera os sucessores de um nodo n
void succ(Node n, vector<State> *suc)
{
  State state = n.getState();
  unsigned long long state_original = state.getState();
  unsigned char zero_posicao = state.getPosZero();
  short int zero_linha = (short int)(zero_posicao >> 4);   // empurra 4 bits pra pegar os 4 mais significativos (linha)
  short int zero_coluna = (short int)(0xF & zero_posicao); // mascara 1111 pra pegar os ultimos 4 bits (coluna)
  short int pos_zero_state = 3 * zero_linha + zero_coluna;

  if (zero_linha != PUZZLE)
  {
    // não ta na última linha, troca com o de baixo
    suc->push_back(swap_board(state_original, zero_linha, zero_coluna, zero_linha + 1, zero_coluna, pos_zero_state));
  }

  if (zero_linha != 0)
  { // não ta na primeira linha, troca com o de cima
    suc->push_back(swap_board(state_original, zero_linha, zero_coluna, zero_linha - 1, zero_coluna, pos_zero_state));
  }

  if (zero_coluna != 0)
  { // não ta na primeira linha, troca com o de cima
    suc->push_back(swap_board(state_original, zero_linha, zero_coluna, zero_linha, zero_coluna - 1, pos_zero_state));
  }

  if (zero_coluna != PUZZLE)
  { // não ta na primeira linha, troca com o de cima
    suc->push_back(swap_board(state_original, zero_linha, zero_coluna, zero_linha, zero_coluna + 1, pos_zero_state));
  }
};

int main()
{
  State teste = State("7 2 4 5 0 6 8 3 1"); // esse estado é 30674020401 em decimal
  State teste_dois = State("0 1 2 3 4 5 6 7 8");
  // State teste_tres = State("1 0 2 3 4 5 6 7 8");
  // State teste_quatro = State("1 2 0 3 4 5 6 7 8");
  // State teste_cinco = State("1 2 3 0 4 5 6 7 8");
   //cout << " " << calc_h(teste) << " teste_dois: " << calc_h(teste_dois) << endl;

  // cout << teste.is_goal() << " " << teste_dois.is_goal() << "\n";
  // teste_dois.printState();
  // cout << teste_dois.getH() << "\n";

  // if (mapa.end() == mapa.find(e)){
  //   cout <<"a";
  // }
  // priority_queue<Node, vector<Node>, Comparador> open;
  // unordered_map<unsigned long long, State> closed;

  cout << "\nEstado inicial:: " << endl;
  teste.printState();

  vector<State> sucessores;
  Node nodo = Node(&teste);
  succ(nodo, &sucessores);

  cout << "Sucessores::: " << endl;
  while (!sucessores.empty())
  {
    State estado;
    estado = sucessores.back();
    estado.printState();
    sucessores.pop_back();
    
  }

  // Node nodo2 = Node(&teste_dois);
  // succ(nodo2, sucessores);

  // Node nodo3 = Node(&teste_tres);
  // succ(nodo3, sucessores);

  // Node nodo4 = Node(&teste_quatro);
  // succ(nodo4, sucessores);

  // Node nodo5 = Node(&teste_cinco);
  // succ(nodo5, sucessores);
}
