#ifndef algorithms_h
#define	algorithms_h

#include "types.h"

void createGraph(EDGE** mat, int vertices);
int BFS(EDGE** mat, int vertices);
int DFS(EDGE** mat, int vertices);

#endif
