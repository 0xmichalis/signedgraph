/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include <stdlib.h>
#include <stdio.h>

#include "algorithms.h"
#include "types.h"

// TODO: I don't like globals.
int ip = 0, rp = 0, flag;

// queuePush is the push operation of the queue used by BFS
static void queuePush(int* queue, int elem){
	int node;
	flag = 0;
	// If the node that is to be inserted in the queue
	// is already there then toggle flag.
	for(node = 0; node < ip; node++){
		if(queue[node] == elem){
			flag = 1;
		}
	}
	if(flag == 0){
		queue[ip++] = elem;
	}
}

// queuePop is the pop operation of the queue used by BFS
static int queuePop(int* queue){
	if (ip == rp){
		return -1;
	}
	return queue[rp++];
}

// stackPush is the push operation of the stacks used by DFS.
// By convention, the first element of the stack is going to 
// represent the head of the stack.
static void stackPush(stack *stack, int elem){
	stack[stack[0]++] = elem;
}

// stackPop is the pop operation of the stacks used by DFS.
// By convention, the first element of the stack is going to 
// represent the head of the stack.
static int stackPop(stack *stack){
	if (stack[0] == 0){
		return -1;
	}
	return stack[--stack[0]];
}

// createGraph creates a random signed graph given a fixed number
// of nodes
void createGraph(EDGE** mat, int nodes){
	int limit, current, adjacent;

	// TODO: This algorithm could need more polishing.
	for(current = 0; current < nodes; current++){
		// limit is a random number of initial connections assigned
		// to current node. Minimum number of edges that will get 
		// randomly assigned to a node is 2 and maximum is 6.
		if(nodes == 3){
			limit = 2;
		} else if(nodes == 4){
			limit = rand() % 2 + 2;
		} else {
			limit = rand() % (nodes % 5 + 1) + 2;
		}

		while(limit){
        		adjacent = rand() % nodes;
			// An edge has to have different endpoints so essentially
			// current and adjacent have to be unequal. If not or 
        		// already an edge with the current (current,adjacent)
        		// endpoints exists then no new edge should be added.
			if((adjacent == current) || (mat[current][adjacent].visited == UNVISITED)){
				continue;
        		}
	        	// The edge sign will be either 1 (NEGATIVE) or 2 (POSITIVE)
			mat[current][adjacent].sign = rand() % 2 + 1;
			mat[adjacent][current].sign = mat[current][adjacent].sign;
			// At start all the edges are unvisited
			mat[current][adjacent].visited = UNVISITED;
			limit--;
		}
	}
	for(current = 0; current < nodes; current++){
		if(mat[current][adjacent].visited == UNVISITED){
			mat[adjacent][current].visited = UNVISITED;
		}
	}

	return;
}

// BFS traverses a signed graph using the homonym graph traversal
// technique and checks for the graph balance
int BFS(EDGE** mat, int nodes){
	int current, adjacent, product, count = 1, adjcount = 0, tmp, nodeSign, *queue, returnCode = 0;

	current = rand() % nodes;
	queue = Allocate(int, nodes);
	// Algorithm starts traversing here, crossing every possible
	// adjacent node of the current node.
	for(adjacent = 0; adjacent < nodes; adjacent++){
		if(mat[current][adjacent].visited == UNVISITED){
			adjcount ++;
			// Random sign on the first node
			if((count == 1) && (adjcount == 1)){
				mat[current][adjacent].nodeSign = rand() % 2 + 1;
				nodeSign = mat[current][adjacent].nodeSign;
				for(tmp = 0; tmp < nodes; tmp++){
					if(mat[current][tmp].sign){
						mat[current][tmp].nodeSign = nodeSign;
					}
				}
			}
			queuePush(queue, adjacent);
			// If flag is 1 then (current,adjacent) will be a cycle-closing edge. 
			// If the product between the sign of current node and the sign of 
			// edge (current,adjacent) is different from the sign of adjacent node
			// then the subgraph that (current,adjacent) is closing, is not balanced 
			// and the algorithm breaks.
			if(flag == 1){
				product = mat[current][adjacent].nodeSign * mat[current][adjacent].sign;
				// NEGATIVE * NEGATIVE (1 * 1) == positive (1) and 
				// POSITIVE * POSITIVE (2 * 2) == positive (4)
				// The only case the product is going to be negative is
				// when NEGATIVE * POSITIVE (1 * 2) == negative (2)
				if(product == 2){
					product = NEGATIVE;
				} else {
					product = POSITIVE;
				}
				if(product != mat[adjacent][current].nodeSign){
					returnCode = 1;
					break;
				}
			}
			// If the product of the signs of current node and edge (current,adjacent)
			// is 2, a multiplication between a negative (1) and a positive sign
			// (2) has to be preceded (1*2 = 2). So the sign of adjacent node will
			// be negative.
			product = mat[current][adjacent].nodeSign * mat[current][adjacent].sign;
			if(product == 2){
				for(tmp = 0; tmp < nodes; tmp++){
					if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
						mat[adjacent][tmp].nodeSign = NEGATIVE;
					}
				}
			} else {
				for(tmp = 0; tmp < nodes; tmp++){
					if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
						mat[adjacent][tmp].nodeSign = POSITIVE;
					}
				}
			}
			mat[current][adjacent].visited = VISITED;
			mat[adjacent][current].visited = VISITED;
		}
		if(adjacent == nodes - 1){
			count ++;
			current = queuePop(queue);
			if(current == -1){
				break;
			}
			adjacent = -1;
			adjcount = 0;
		}
	}
	free(queue);
	ip = 0;
	rp = 0;

	return returnCode;
}

// DFS traverses a signed graph using the homonym graph traversal
// technique and checks for the graph balance
int DFS(EDGE** mat, int nodes){
	int *visited, current, adjacent, tmp, product, returnCode = 0;
	stack *stackA, *stackB;

	stackA = Allocate(stack, nodes + 1);
	stackB = Allocate(stack, nodes + 1);
	visited = Allocate(int, nodes);
	current = rand() % nodes;
	visited[current] = VISITED;
	for(adjacent = 0; adjacent < nodes; adjacent++){
		if(current == adjacent){
			continue;
		}
		visited[adjacent] = UNVISITED;
	}
	// Random sign on the first node
	tmp = rand() % 2 + 1;
	for(adjacent = 0; adjacent < nodes; adjacent++){
		if(mat[current][adjacent].sign){
			mat[current][adjacent].nodeSign = tmp;
		}
	}
	// Algorithm starts traversing here
	while(1){
		for(adjacent = 0; adjacent < nodes; adjacent++){
			if((mat[current][adjacent].visited == UNVISITED) && (mat[current][adjacent].sign == POSITIVE)){
			// Checking every possible adjacent node that is reached through a positive edge
				if(visited[adjacent] == UNVISITED){
					visited[adjacent] = VISITED;
					product = mat[current][adjacent].nodeSign * mat[current][adjacent].sign;
					if(product == 2){
						for(tmp = 0; tmp < nodes; tmp++){
							if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
								mat[adjacent][tmp].nodeSign = NEGATIVE;
							}
						}
					} else {
						for(tmp = 0; tmp < nodes; tmp++){
							if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
								mat[adjacent][tmp].nodeSign = POSITIVE;
							}
						}
					}
					stackPush(stackA, adjacent);
				} else if((visited[adjacent] == VISITED) && (mat[current][adjacent].nodeSign != mat[adjacent][current].nodeSign)){
				// Checking if an adjacent node has a different sign from the 
				// current because we are on a positive edge.
					returnCode = 1;
					// toggle returnCode - graph is unbalanced
					break;
				}
			} else if((mat[current][adjacent].visited == UNVISITED) && (mat[current][adjacent].sign == NEGATIVE)){
			// Checking every possible adjacent node that is reached through a negative edge
				if(visited[adjacent] == UNVISITED){
					visited[adjacent] = VISITED;
					product = mat[current][adjacent].nodeSign * mat[current][adjacent].sign;
					if(product == 2){
						for(tmp = 0; tmp < nodes; tmp++){
							if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
								mat[adjacent][tmp].nodeSign = NEGATIVE;
							}
						}
					} else {
						for(tmp = 0; tmp < nodes; tmp++){
							if(mat[adjacent][tmp].sign && (mat[adjacent][tmp].nodeSign == 0)){
								mat[adjacent][tmp].nodeSign = POSITIVE;
							}
						}
					}
					stackPush(stackB, adjacent);
				} else if((visited[adjacent] == VISITED) && (mat[current][adjacent].nodeSign == mat[adjacent][current].nodeSign)){
				// Checking if an adjacent node has the same sign as the
				// current because we are on a negative edge
					returnCode = 1;
					//toggle returnCode - graph is unbalanced
					break;
				}
			}
		}
		if(returnCode == 1){
			break;
		}
		adjacent = stackPop(stackA);
		if(adjacent == -1){
			adjacent = stackPop(stackB);
		}
		if(adjacent == -1){
			// graph is balanced
			break;
		}
		mat[current][adjacent].visited = VISITED;
		mat[adjacent][current].visited = VISITED;
		current = adjacent;
	}
	free(stackA);
	free(stackB);
	free(visited);
	ip = 0;
	rp = 0;

	return returnCode;
}
