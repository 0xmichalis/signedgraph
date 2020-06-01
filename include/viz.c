#include <stdio.h>
#include <stdlib.h>

#include "types.h"

// vizGraph visualizes a given graph by generating its represantation
// in the DOT language and calling neato on it
void vizGraph(EDGE** mat, int nodes){
	FILE *pFile;
	int current, adjacent, fcount=0;

	pFile = fopen("graph.dot", "wb");
	if(pFile == NULL){
    		fprintf(stderr, "Error opening graph.dot\n");
    		return;
	}
	// The following is a grammar part of the DOT language. Literal characters
	// are given in single quotes. Parentheses () indicate grouping when needed.
	// Square brackets [] enclose optional items. The keywords node, edge, and
	// graph are case-independent. Note also that the allowed compass point values
	// are not keywords, so these strings can be used elsewhere as ordinary identifiers
	// and, conversely, the parser will actually accept any identifier.The language
	// supports C-style comments and in addition, a line beginning with a '#' character
	// is considered a line output from a C preprocessor.
	// More information in the following link: http://graphviz.org/content/dot-language
	fprintf(pFile, "graph G {\n\tnode [shape=circle, style=filled];\n\n\nedge [len=3];\n");
	for(current = 0; current < nodes; current++){
		for(adjacent = 0; adjacent < nodes; adjacent++){
			if(mat[current][adjacent].sign == NEGATIVE){
				fcount++;
				mat[adjacent][current].sign = 0;
				fprintf(pFile, "%d -- %d [label=\"%c\", color=\"%s\"]; ", current, adjacent, '-', "blue");
				if(fcount%3==0){
					fprintf(pFile, "\n");
				}
			} else if(mat[current][adjacent].sign == POSITIVE){
				fcount++;
				mat[adjacent][current].sign = 0;
				fprintf(pFile, "%d -- %d [label=\"%c\", color=\"%s\"]; ", current, adjacent, '+', "red");
				if(fcount%3==0){
					fprintf(pFile, "\n");
				}
			}
		}
	}
	fprintf(pFile, "\n}");
	fclose(pFile);
	// neato is a program that makes layouts of undirected graphs following the
	// filter model of DOT language.Its layout heuristic creates virtual physical
	// models and runs an iterative solver to find low energy configurations.
	// More information in the following link: http://graphviz.org/pdf/neatoguide.pdf
	system("neato -Tps graph.dot -o graph.ps");
	system("evince graph.ps");
}