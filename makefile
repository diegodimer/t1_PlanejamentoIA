all:
	g++ -std=c++11 blackbox.cpp blackbox.h bfs_graph.cpp iterative_deepening.cpp iterative_deepening.h greedy_bfs.cpp greedy_bfs.h bfs_graph.h astar.cpp astar.h main.cpp -o main

astar:
	g++ -std=c++11 blackbox.cpp blackbox.h astar.cpp astar.h main.cpp -o main

bfsgraph:
	g++ -std=c++11 blackbox.cpp blackbox.h bfs_graph.cpp bfs_graph.h main.cpp -o main 

iterative_deepening:
	g++ -stad=c++11 blackbox.cpp blackbox.h iterative_deepening.cpp iterative_deepening.h main.cpp -o main
