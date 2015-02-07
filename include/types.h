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