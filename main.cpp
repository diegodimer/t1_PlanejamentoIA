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

/* 
 f(n) = h(s) + g(n)
*/
class State{
  unsigned long long state; // estado representado com 64-bit
  public:
    State(string _state){
      state = 0;
      for(int i=0; i<_state.length(); i++){
        if (_state[i] != ' '){
          unsigned char num = (unsigned char) _state[i] - '0';
          state += num;
          state = state << 4;
        }
      }
      
      state = state >> 4; // um if ali testado n vezes é mais facil fazer 4 shifts pro outro lado depois
    
    }
    
    long long getState() const { return state;}

    void printState() const { 
      unsigned long long position = 0xF00000000; // tem 8 zeros pq ignora 8 numeros pra pegar o primeiro
      unsigned long long number = 0;
      int indice = 8;
      cout << "========================"<<"\n";
      cout << "Representação do estado: " << "\n";
      for(int i=0; i<3; i++){
        cout<<"\t\t";
        for(int j=0; j<3;j++){
          number = state & position; // a mascara pega o primeiro numero
          number = number >> 4*indice; // e shifta ele até a posição certa
          indice -=1;
          int should_linha;
          if(number/3 < 1){
            should_linha = 0;
          } else if(number/3 < 2){
            should_linha = 1;
          } else
            should_linha = 2;
           
          int should_coluna = number % 3;
          int h = abs(should_linha-i) + abs(should_coluna-j);
          cout << number << " (h(n): " << h <<")   " ;
          position = position >> 4; // move a mascara p/ pegar o próximo numero
        }
        cout << "\n";
      }
      cout << "========================"<<"\n";
     }

    int h() const {
      unsigned long long position = 0xF00000000; // mascara
      unsigned long long number = 0;
      int h_ac = 0;
      int indice = 8;
      for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
          number = state & position; // a mascara pega o primeiro numero
          number = number >> 4*indice; // e shifta ele até a posição certa
          indice -=1;
          int should_linha; // linha que devia estar
          int n = number/3;
          if(n < 1){
            should_linha = 0;
          } else if(n/3 < 2){
            should_linha = 1;
          } else
            should_linha = 2;
           
          int should_coluna = number % 3;
          int h = abs(should_linha-i) + abs(should_coluna-j);
          h_ac += h;
          position = position >> 4; // move a mascara p/ pegar o próximo numero
        }
      }
      return h_ac;
     }
      
    bool is_goal() const {return state == 305419896;} // só vale pro 8-puzzle
};



int main() {
  State teste= State("7 2 4 5 0 6 8 3 1"); // esse estado é 30674020401 em decimal
  
  State teste_dois = State("0 1 2 3 4 5 6 7 8");
  //cout << teste.is_goal() << " " << teste_dois.is_goal();
  teste_dois.printState();
  cout << teste_dois.h();
}