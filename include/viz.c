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