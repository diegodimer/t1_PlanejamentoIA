#include <iostream>
#include "blackbox.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>
#include <queue>

static int h_inicial;
static int stop;

int recursive_function(Node *n, int *f_limit)
{
    if (n->getF() > (*f_limit))
    {
        int ret = n->getF();
        delete n;
        n = NULL;
        return ret;
    }
    if (is_goal(n->getState().getState()))
    {
        print_results(*n, h_inicial);
        stop=1;
        return INT_MAX;
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
            sucessores.pop_back();
            next_limit = recursive_function(n_linha, f_limit);
        }
    }
    return next_limit;
}

int IDASTAR(string _state)
{
    State *estado = new State(_state); 
    cout << "Starting IDA*" << endl;
    Node *n_zero = new Node(NULL, estado, 0);
    h_inicial = n_zero->getH();
    int rec_limit = n_zero->getF();
    while (!stop)
    {
        cout<<"Calling with " << rec_limit << endl;
        rec_limit = recursive_function(n_zero, &rec_limit);

    }
}
