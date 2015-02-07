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

#include <stdio.h>

#include "types.h"
#include "test.h"
#include "algorithms.h"

// balancedGraph is a mock balanced graph used for testing
static int balancedGraph(EDGE** mat){
	int current, adjacent;

	mat[0][1].sign = NEGATIVE;	//0 -- 1 -
	mat[0][2].sign = POSITIVE;	//0 -- 2 +
	mat[0][3].sign = POSITIVE;	//0 -- 3 +
	mat[1][0].sign = NEGATIVE;
	mat[2][0].sign = POSITIVE;
	mat[3][0].sign = POSITIVE;
	mat[1][2].sign = NEGATIVE;	//1 -- 2 -
	mat[1][4].sign = POSITIVE;	//1 -- 4 +
	mat[2][1].sign = NEGATIVE;
	mat[4][1].sign = POSITIVE;
	mat[2][3].sign = POSITIVE;	//2 -- 3 +
	mat[3][2].sign = POSITIVE;
	mat[3][4].sign = NEGATIVE;	//3 -- 4 -
	mat[4][3].sign = NEGATIVE;

	for(current = 0; current < 5; current++){
   		for(adjacent = 0; adjacent < 5; adjacent++){
            		if(mat[current][adjacent].sign){
                		mat[current][adjacent].visited = UNVISITED;
                		mat[adjacent][current].visited = UNVISITED;
            		}
		}
    	}

    	return 0;
}

// unbalancedGraph is a mock unbalanced graph used for testing
static int unbalancedGraph(EDGE** mat){
	int current, adjacent;

	for(current = 0; current < 5; current++){
  		for(adjacent = 0; adjacent < 5; adjacent++){
    			mat[current][adjacent].sign = POSITIVE;
			if (current == adjacent){
				mat[current][adjacent].sign = 0;
			}
		}
	}
	mat[4][3].sign = NEGATIVE;
	mat[3][4].sign = NEGATIVE;
	for(current = 0; current < 5; current++){
   		for(adjacent = 0; adjacent < 5; adjacent++){
            		if(mat[current][adjacent].sign){
                		mat[current][adjacent].visited = UNVISITED;
                		mat[adjacent][current].visited = UNVISITED;
            		}
		}
    	}

    	return 1;
}

// balancedGraphFig7 is a mock balanced graph used for testing
// Its implementation comes from Figure 7 of STRUCTURAL BALANCE:
// A GENERALIZATION OF HEIDER'S THEORY by Cartwright and 
// Harary (1956)
static int balancedGraphFig7(EDGE** mat){
	int current, adjacent;

	mat[0][1].sign = POSITIVE;	//A -- B +
	mat[1][0].sign = POSITIVE;
	mat[1][2].sign = POSITIVE;	//B -- C +
	mat[2][1].sign = POSITIVE;
	mat[2][3].sign = POSITIVE;	//C -- D +
	mat[3][2].sign = POSITIVE;
	mat[3][0].sign = POSITIVE;	//D -- A +
	mat[0][3].sign = POSITIVE;
	mat[3][4].sign = NEGATIVE;	//D -- E -
	mat[4][3].sign = NEGATIVE;
	mat[4][5].sign = POSITIVE;	//E -- F +
	mat[5][4].sign = POSITIVE;
	mat[5][3].sign = NEGATIVE;	//F -- D -
	mat[3][5].sign = NEGATIVE;
	mat[1][5].sign = NEGATIVE;	//F -- B -
	mat[5][1].sign = NEGATIVE;
	mat[5][6].sign = POSITIVE;	//F -- G +
	mat[6][5].sign = POSITIVE;
	mat[6][0].sign = NEGATIVE;	//G -- A -
	mat[0][6].sign = NEGATIVE;
	mat[6][7].sign = POSITIVE;	//G -- H +
	mat[7][6].sign = POSITIVE;
	mat[7][0].sign = NEGATIVE;	//H -- A -
	mat[0][7].sign = NEGATIVE;
	mat[7][3].sign = NEGATIVE;	//H -- D -
	mat[3][7].sign = NEGATIVE;

	for(current = 0; current < 8; current++){
   		for(adjacent = 0; adjacent < 8; adjacent++){
            		if(mat[current][adjacent].sign){
                		mat[current][adjacent].visited = UNVISITED;
                		mat[adjacent][current].visited = UNVISITED;
            		}
		}
    	}

    	return 0;
}

// checkReturnCode checks if a test has passed or failed and reports back
static int checkReturnCode(int expectedBalance, int returnCode){
	if (expectedBalance == returnCode){
		printf("OK\n");
		return 0;
	} else {
		printf("TEST FAILED!\n");
		return 1;
	}
}

// testAlgorithms runs the balance checking algorithms on our mock graphs
static int testAlgorithms(int (*testFunc)(EDGE**), int nodes){
	int current, expectedBalance, testDFS, testBFS;
	EDGE **clone, **mat;

	// Create two copies of our mock graph; DFS will run on one
	// and BFS will run on the other
	mat = Allocate(EDGE*, nodes);
	clone = Allocate(EDGE*, nodes);
	for(current = 0; current < nodes; current++){
		mat[current] = Allocate(EDGE, nodes);
		clone[current] = Allocate(EDGE, nodes);
	}
	expectedBalance = (*testFunc)(mat);
	(*testFunc)(clone);
	// Testing...
	printf("Testing DFS: ");
	testDFS = checkReturnCode(expectedBalance, DFS(mat, nodes));
	printf("Testing BFS: ");
	testBFS = checkReturnCode(expectedBalance, BFS(clone, nodes));
	// Clean-up
	for(current = 0; current < nodes; current++){
		free(mat[current]);
		free(clone[current]);
	}
	free(mat);
	free(clone);
	// If at least one algorithm has failed then all the testing
	// process should be considered as failed
	if(testBFS == 1 || testDFS == 1){
		return 1;
	}
	// Tests are successful
	return 0;
}

// RunTests is the main testing function where all tests start up
int RunTests(){
	int testResult = 0;

	printf("**********TEST MODE**********\n");
	printf("*****************************\n");
	printf("Running balanced graph test...\n");
	testResult += testAlgorithms(&balancedGraph, 5);
	printf("Running unbalanced graph test...\n");
	testResult += testAlgorithms(&unbalancedGraph, 5);
	printf("Running balancedGraphFig7 graph test...\n");
	testResult += testAlgorithms(&balancedGraphFig7, 8);
	if(testResult > 0) {
		// Some test has failed
		return 1;
	}
	return 0;
}
