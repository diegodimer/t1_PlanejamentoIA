#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;
/* 

  0     1    2    3    4    5    6    7    8
0000 0001 0010 0011 0100 0101 0110 0111 1000= 36 bits para armazenar o estado (305419896 em decimal é o goal)

   0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 = 64 bits para armazenar o estado (81985529216486895 em decimal é o goal)

*/

class State; // classe que representa o estado
class Node; // classe que representa um nodo (nodo tem um estado parte dele)
class Comparador; // classe que implementa o comparador usado no open set

// mapa com todos os estados (funciona parecido com um hash set)
unordered_map<int, State *> estados;


class State
{

  unsigned long long state; // estado representado com 64-bit
  int h;

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
      }
    }

    state = state >> 4; // um if ali testado n vezes é mais facil fazer 4 shifts pro outro lado depois
    h = calc_h();
  }

  long long getState() const { return state; }
  int getH() const { return h; }

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
    for (int i = 0; i < 3; i++)
    {

      for (int j = 0; j < 3; j++)
      {
        number = state & position;     // a mascara pega o primeiro numero
        number = number >> 4 * indice; // e shifta ele até a posição certa
        indice -= 1;
        int should_linha;
        if (number / 3 < 1)
        {
          should_linha = 0;
        }
        else if (number / 3 < 2)
        {
          should_linha = 1;
        }
        else
          should_linha = 2;

        int should_coluna = number % 3;
        int h = abs(should_linha - i) + abs(should_coluna - j);
        cout << number << " (h(n): " << h << ")   ";
        position = position >> 4; // move a mascara p/ pegar o próximo numero
      }
      cout << "\n";
    }
    cout << "========================"
         << "\n";
  }

  bool is_goal() const { return state == 305419896; } // só vale pro 8-puzzle

  /* Função que gera os sucessores do estado s. Retorna no vetor passado como parâmetro */
  void succ(vector<State> sucessores) const
  {

  }

private:
  /* Função que calcula o valor h(S) */
  int calc_h() const
  {
    unsigned long long position = 0xF00000000; // mascara
    unsigned long long number = 0;
    int h_ac = 0;
    int indice = 8;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        number = state & position;     // a mascara pega o primeiro numero
        number = number >> 4 * indice; // e shifta ele até a posição certa
        indice -= 1;
        int should_linha; // linha que devia estar
        int n = number / 3;
        if (n < 1)
        {
          should_linha = 0;
        }
        else if (n < 2)
        {
          should_linha = 1;
        }
        else
          should_linha = 2;

        int should_coluna = number % 3;
        int h = abs(should_linha - i) + abs(should_coluna - j);
        h_ac += h;
        position = position >> 4; // move a mascara p/ pegar o próximo numero
      }
    }
    return h_ac;
  }
};

class Node
{
  int g;
  int f;
  State state;

public:
  int getG() const { return g; }
  int getF() const { return f; }
  int getH() const { return state.getH(); }
  State getState() const { return state; }
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

int main()
{
  //State teste = State("7 2 4 5 0 6 8 3 1"); // esse estado é 30674020401 em decimal

  //State teste_dois = State("0 1 2 3 4 5 6 7 8");

  // cout << teste.is_goal() << " " << teste_dois.is_goal() << "\n";
  // teste_dois.printState();
  // cout << teste_dois.getH() << "\n";

  // if (mapa.end() == mapa.find(e)){
  //   cout <<"a";
  // }

  priority_queue<Node, vector<Node>, Comparador> pq;
}
