all:
	g++ blackbox.cpp blackbox.h bfs_graph.cpp bfs_graph.h astar.cpp astar.h main.cpp -o main

astar:
	g++ blackbox.cpp blackbox.h astar.cpp astar.h main.cpp -o main

bfsgraph:
	g++ blackbox.cpp blackbox.h bfs_graph.cpp bfs_graph.h main.cpp -o main 
