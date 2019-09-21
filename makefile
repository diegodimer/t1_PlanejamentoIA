all:
	g++ -std=c++11 blackbox.cpp blackbox.h bfs_graph.cpp bfs_graph.h astar.cpp astar.h idastar.cpp idastar.h main.cpp -o main

astar:
	g++ -std=c++11 blackbox.cpp blackbox.h astar.cpp astar.h main.cpp -o main

bfsgraph:
	g++ -std=c++11 blackbox.cpp blackbox.h bfs_graph.cpp bfs_graph.h main.cpp -o main 

idastar:
	g++ -std=c++11 blackbox.cpp blackbox.h idastar.cpp idastar.h main.cpp -o main 

