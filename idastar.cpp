#include <iostream>
#include "blackbox.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>
#include <queue>
#include <vector>

static int h_inicial;
static int stop;
int heuristica_ac3;
int heuristica_ind3;
vector<Node *> passados;
int recursive_function(Node *n, int *f_limit)
{
    heuristica_ind3++;
    heuristica_ac3+=n->getH();
    if (n->getF() > (*f_limit))
    {
        int ret = n->getF();
        n = NULL;
        return ret;
    }
    if (is_goal(n->getState().getState()))
    {
        print_results(*n, h_inicial, (float)heuristica_ac3/heuristica_ind3);
        stop=1;
        return 0;
    }
    int next_limit;
    vector<State *> sucessores;
    if (!stop)
    {
        succ(*n, &sucessores);
        while (!sucessores.empty())
        {
            State *estado = sucessores.back();
            int new_g = n->getG() + 1;
            Node *n_linha = new Node(n, estado, new_g);
            passados.push_back(n_linha);
            sucessores.pop_back();
            next_limit = recursive_function(n_linha, f_limit);
        }
    }
    return next_limit;
}

int IDASTAR(string _state)
{
    State *estado = new State(_state); 
    Node *n_zero = new Node(NULL, estado, 0);
    h_inicial = n_zero->getH();
    int rec_limit = n_zero->getF();
    stop = 0;
    heuristica_ac3 = h_inicial;
    heuristica_ind3 = 1;
    while (!stop)
    {
        rec_limit = recursive_function(n_zero, &rec_limit);

    }
    delete n_zero;
    while(!passados.empty()){
        Node *n = passados.back();
        passados.pop_back();
        delete n;
    }
}
