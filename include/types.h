#ifndef types_h
#define	types_h

#include <stdlib.h>
#include <stdint.h>

// Data structures and macros

#define POSITIVE 2	// positive sign
#define NEGATIVE 1 	// negative sign
#define VISITED 2
#define UNVISITED 1
#define Allocate(type, count)				(type *)calloc((count), sizeof(type))

// stack is a type used to represent a stack.
typedef uint16_t stack;

// EDGE is a type used to represent an edge in a graph
typedef struct {
	uint8_t sign;
	uint8_t nodeSign; // row field (mat[row][column]) indicates the node number
	uint8_t visited;
}EDGE;

#endif