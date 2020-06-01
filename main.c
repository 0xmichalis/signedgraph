#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "types.h"
#include "algorithms.h"
#ifdef VIZ
#include "viz.h"
#endif
#ifdef TEST
#include "test.h"
#endif

// traverseGraph randomly chooses an algorithm
// between BFS and DFS in order to traverse the
// graph and prints if the graph is balanced or not.
static void traverseGraph(EDGE** mat, int nodes){
	int returnCode = 0;

    	if(rand() % 2){
    		printf("Graph traversed using DFS...\n");
    		returnCode = DFS(mat, nodes);
	} else {
		printf("Graph traversed using BFS...\n");
    		returnCode = BFS(mat, nodes);
	}
    	if(returnCode == 1){
		printf("The graph is unbalanced.\n");
	} else if(returnCode == 0){
		printf("The graph is balanced.\n");
	}
}

// usage prints the way this program has to be used
static void usage(){
	printf("usage: signedgraph <# of nodes>\n");
	printf("\t# of nodes: [3-18000]\n");
}

int main(int argc, char **argv){
	#ifndef TEST
	// Minimum number of nodes required to create a graph is three:
	//
	//		    A
	//		  /   \
	//		 B --- C
	//
	// and maximum is set to 18000 (about 1.5 GB of RAM allocated).
	// Theoretically our graph algorithms can work with up to as many
	// nodes we want, but we have restricted the present program to 
	// generate graphs up to 18k nodes due to memory limitations some 
	// computers may have.
	const unsigned int minimum = 3, maximum = 18000;
	unsigned int current, nodes, digits;
	EDGE** mat;

	srand(time(NULL));

	if(argc == 1){
		fprintf(stderr, "No number of nodes passed\n");
		usage();
		return 1;
	}
	digits = strlen(argv[1]);
	for(current = 0; current < digits; current++){
		if (!isdigit(argv[1][current])){
			fprintf(stderr, "%s is not a valid number\n", argv[1]);
			usage();
			return 1;
		}
	}
	nodes = strtol(argv[1], NULL, 10);
	if((nodes < minimum) || (nodes > maximum)){
		fprintf(stderr, "%d is not between the allowed limits\n", nodes);
		usage();
		return 1;
	}
	mat = Allocate(EDGE*, nodes);
	for(current = 0; current < nodes; current++){
		mat[current] = Allocate(EDGE, nodes);
	}
	// Create a random singed graph
	createGraph(mat, nodes);
	// and traverse it to check for its balance
	traverseGraph(mat, nodes);
	// Optionally run Graphviz but in any case don't run it while testing
	#ifdef VIZ
	vizGraph(mat, nodes);
	#endif

	for(current = 0; current < nodes; current++){
		free(mat[current]);
	}
	free(mat);
	return 0;
	#endif

	// Cannot be here

	#ifdef TEST
	return RunTests();
	#endif
}
