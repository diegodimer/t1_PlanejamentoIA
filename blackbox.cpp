#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <tr1/functional>
#include <unordered_set>
#include "blackbox.h"
#include <ctime>

/**
 * BLACKBOX
 * O objetivo aqui foi simular as funções de blackbox como estudadas em aula.
 * O estado é representado por um long long (64 bits) onde cada célula ocupa
 * 4 bits. O teste de is_goal fica trivial: comparamos com um numero (0x12345678 
 * e 0x123456789ABCDEF). Variáveis de PUZZLE (índice da maior coluna (3 ou 4)),
 * MAX_INDEX (qual máximo índice alcançado no array para o tabuleiro (8 ou 15))
 * e GOAL são setadas quando o primeiro estado é criado (o único que é gerado a
 * partir de uma string). A função de calc_h calcula a heurística para um estado
 * passando por todas as células (usando operações de shift e and lógico) e cal-
 * cula a distância de manhattan até a posição que esse número deveria estar. 
 * A geração de sucessores é basicamente mudar a posição do zero, para otimizar
 * isso resolvemos salvar separado do estado (em 1 byte) a posição do zero: para
 * não gerar o sucessor de um estado igual o pai, compara-se a posição do zero
 * do pai com a do estado a ser gerado. Na geração de sucessores também se fez
 * a otimização de não recalcular a heurística para o estado inteiro: precisa
 * apenas remover da heuristica do estado o impacto que o número que trocou com
 * o zero tinha e somar o impacto que ele passou a ter, assim salvamos algum 
 * tempo de processamento. As funções de extract_path e print_state são auxilia-
 * res que nos ajudaram no debug dos algoritmos. Adicionou-se ao estado também 
 * uma variável de índice para funcionar como time stamp, que é o critério de
 * desempate do A*, que tem seu comparador implementado aqui também, assim como
 * o gbfs. A função de hash do open set do A* é implementada aqui também, sendo
 * apenas uma chamada a função nativa de hash com o long long que representa o
 * estado.
*/
using namespace std;
static int nodos_expandidos;
static short int PUZZLE;    //3
static long long GOAL;      //305419896
static short int MAX_INDEX; //8
clock_t start_t;
clock_t end_t;
void print_results(Node n, int h_inicial, float h_media)
{
    // nodos expandidos, comprimento da solução otima, tempo, heuristica media, heuristica inicial
    end_t = clock();
    double elapsed_secs = double(end_t - start_t) / CLOCKS_PER_SEC;
    cout << nodos_expandidos << ", " << n.getF() << ", " << elapsed_secs << ", " << h_media << ", " << h_inicial << endl;
}

State::State(string _state)
{
    start_t = clock();
    state = 0;
    std::istringstream iss(_state);
    std::string token;
    short int index = 0;
    Node::index = 0;
    nodos_expandidos = 0;
    if (_state.size() <= 18)
    {
        PUZZLE = 3;
        GOAL = 305419896;
        MAX_INDEX = 8;
    }
    else
    {
        PUZZLE = 4;
        GOAL = 0x123456789ABCDEF;
        MAX_INDEX = 15;
    }

    while (std::getline(iss, token, ' '))
    {
        unsigned char num = stoi(token);
        state += num;
        if (index < MAX_INDEX)
            state = state << 4;
        if (num == 0)
        {
            int linha = floor(index / PUZZLE);
            int coluna = floor(index % PUZZLE);
            posicao_zero = (linha << 4) | coluna;
        }
        index++;
    }
    h = calc_h(*this);
}
State::State(unsigned long long _state, unsigned char _posicao_zero)
{
    state = _state;
    posicao_zero = _posicao_zero;
    h = calc_h(*this);
}
State::State(unsigned long long _state, unsigned char _posicao_zero, int _h)
{
    state = _state;
    posicao_zero = _posicao_zero;
    h = _h;
}
State::State() {}
long long State::getState() const { return state; }
int State::getH() const { return h; }
void State::setH(int _h) { h = _h; }
unsigned char State::getPosZero() const { return posicao_zero; }

/* Função que printa o estado (fins de debug) */
void State::printState() const
{
    unsigned long long position = 0xF; // mascara
    position = position << (MAX_INDEX * 4);
    unsigned long long number = 0;
    int indice = MAX_INDEX;
    cout << "========================"
         << "\n";
    for (int i = 0; i < PUZZLE; i++)
    {

        for (int j = 0; j < PUZZLE; j++)
        {
            number = state & position;     // a mascara pega o primeiro numero
            number = number >> 4 * indice; // e shifta ele até a posição certa
            indice -= 1;
            int should_linha = floor(number / PUZZLE);
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

int Node::getG() const { return g; }
int Node::getF() const { return g + state->getH(); }
int Node::getH() const { return state->getH(); }
void Node::setG(int _g) { g = _g; }
void Node::setH(int _h) { state->setH(_h); }
Node::Node() {}
unsigned int Node::getindex() const { return my_index; }
State Node::getState() const { return *state; }
State *Node::getStatePointer() const { return state; }
Node::Node(State *_s)
{
    state = _s;
}
Node::Node(State *_s, int _g)
{
    state = _s;
    g = _g;
}

Node::Node(Node *_pai, State *_s, int _g)
{
    whereFrom = _pai;
    state = _s;
    g = _g;
    my_index = ++index;
}
Node *Node::getWhereFrom() { return whereFrom; }

unsigned int Node::index = 0;

int Comparador_gbfs::operator()(const Node *n1, Node *n2)
{

    if (n1->getH() > n2->getH())
    {
        return true;
    }
    else if (n1->getH() == n2->getH())
    {
        if (n1->getG() > n2->getG())
            return false;
        else if (n1->getG() == n2->getG())
            return n1->getindex() < n2->getindex();
        else
            return true;
    }
    else
    {
        return false;
    }
}

int Comparador::operator()(const Node *e1, Node *e2)
{
    int e1F = e1->getF();
    int e2F = e2->getF();
    if (e1F > e2F)
    {
        return true;
    }
    else if (e1F == e2F)
    {
        int e1H = e1->getH();
        int e2H = e2->getH();
        if (e1H > e2H)
        {
            return true;
        }
        else if (e1H == e2H)
        {
            return e1->getindex() < e2->getindex();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

size_t State_hash::operator()(Node const *e1) const
{
    return tr1::hash<unsigned long long>()(e1->getState().getState());
}

bool State_equal::operator()(Node const *e1, Node const *e2) const
{
    return e1->getState().getState() == e2->getState().getState();
}

bool is_goal(unsigned long long s)
{
    return s == GOAL;
}

int calc_h(State s)
{
    unsigned long long position = 0xF; // mascara
    //position = position << (MAX_INDEX * 4);
    unsigned long long number = 0;
    unsigned long long state = s.getState();
    int h_ac = 0;
    int indice = 0;
    for (int i = PUZZLE-1; i >= 0; i--)
    {
        for (int j = PUZZLE-1; j >= 0; j--)
        {
            number = state & position;       // a mascara pega o primeiro numero
            number = number >> (4 * indice); // e shifta ele até a posição certa
            indice += 1;
            if (number != 0)
            {
                int should_linha = floor(number / PUZZLE); // linha que devia estar
                int should_coluna = number % PUZZLE;
                int h = abs(should_linha - i) + abs(should_coluna - j);
                h_ac += h;
            }
            position = position << 4; // move a mascara p/ pegar o próximo numero
        }
    }
    return h_ac;
}

State *swap_board(unsigned long long state_original, short int zero_linha, short int zero_coluna, short int new_zero_linha, short int new_zero_coluna, short int pos_zero_state, int h_pai)
{
    unsigned long long mask = 0xF;
    short int pos_array_original = PUZZLE * new_zero_linha + new_zero_coluna;    // posição no array do state onde está o numero q vai trocar com o 0
    unsigned long long mask_dois = mask << 4 * (MAX_INDEX - pos_array_original); // mask_dois é do tipo 0000F000 e F é onde está o número que vai trocar com o 0
    mask_dois = mask_dois & state_original;                                      // mask_dois tem o número que  vai trocar com o zero
    short int number = mask_dois  >> 4 * (MAX_INDEX - pos_array_original); // numero de fato que troca com o zero
    unsigned long long new_state = state_original & (~mask_dois);                // faz o AND com a negação da mascara para zerar onde está o número que ia trocar com o zero
    // shifto o mask_dois até onde estava o zero antes e faço or com new_state
    short int offset = (pos_array_original - pos_zero_state) * 4; // nao existe shift negativo
    if (offset < 0)
    {
        mask_dois = mask_dois >> (short int)abs(offset);
    }
    else
    {
        mask_dois = mask_dois << offset;
    }
    new_state = mask_dois | new_state; // coloca o numero no lugar do zero antigo

    unsigned char new_zero_pos = (new_zero_linha << 4) + new_zero_coluna;
    int should_linha = floor(number / PUZZLE); // linha que devia estar
    int should_coluna = number % PUZZLE;
    // zero_linha e zero_coluna = onde o numero está no sucessor
    // new_zero_linha new_zero_coluna = onde ta o numero no original
    int heurstic_change = h_pai - (abs(new_zero_linha - should_linha) + abs(new_zero_coluna - should_coluna)) + (abs(zero_linha - should_linha) + abs(zero_coluna - should_coluna));
    State *novo_estado = new State(new_state, new_zero_pos, heurstic_change);

    return novo_estado;
}

// gera os sucessores de um nodo n
void succ(Node n, vector<State *> *suc)
{
    // linhas de codigo usadas para testar se um filho gerado e igual ao pai de n
    Node *nodo_pai = n.getWhereFrom();
    unsigned long long pai = 0;
    unsigned char pos_zero_pai = ~(0x00);
    if (nodo_pai != NULL){
        pai = nodo_pai->getState().getState();
        pos_zero_pai = nodo_pai->getState().getPosZero();
    }
    State *filho;

    nodos_expandidos++;
    State state = n.getState();
    unsigned long long state_original = state.getState();
    unsigned char zero_posicao = state.getPosZero();
    short int zero_linha = (short int)(zero_posicao >> 4);   // empurra 4 bits pra pegar os 4 mais significativos (linha)
    short int zero_coluna = (short int)(0xF & zero_posicao); // mascara 1111 pra pegar os ultimos 4 bits (coluna)
    short int pos_zero_state = PUZZLE * zero_linha + zero_coluna;
    int h_pai = state.getH();

        
    if (zero_linha != (PUZZLE - 1))
    {
        // não ta na última linha, troca com o de baixo
        if( (((zero_linha+1) << 4) + zero_coluna) != pos_zero_pai){
            filho = swap_board(state_original, zero_linha, zero_coluna, zero_linha + 1, zero_coluna, pos_zero_state, h_pai);
            suc->push_back(filho);
        }
    }

    if (zero_coluna != (PUZZLE - 1))
    { // não ta na primeira linha, troca com o da direita
        if( ((zero_linha << 4) + (zero_coluna+1)) != pos_zero_pai){
        filho = swap_board(state_original, zero_linha, zero_coluna, zero_linha, zero_coluna + 1, pos_zero_state, h_pai);
        suc->push_back(filho);
        }
    }

    if (zero_coluna != 0)
    { // não ta na primeira linha, troca com o da esquerda
        if( (((zero_linha) << 4) + (zero_coluna-1)) != pos_zero_pai){
            filho = swap_board(state_original, zero_linha, zero_coluna, zero_linha, zero_coluna - 1, pos_zero_state, h_pai);
            suc->push_back(filho);
        }
    }

    if (zero_linha != 0)
    { // não ta na primeira linha, troca com o de cima
        if( (((zero_linha-1) << 4) + zero_coluna) != pos_zero_pai){
            filho = swap_board(state_original, zero_linha, zero_coluna, zero_linha - 1, zero_coluna, pos_zero_state, h_pai);
            suc->push_back(filho);
        }
    }
};

void extract_path(Node *n)
{
    Node *nlinha = n;
    while (nlinha->getWhereFrom() != NULL)
    {
        Node *pai = nlinha->getWhereFrom();
        pai->getState().printState();
        nlinha = nlinha->getWhereFrom();
    }
}
