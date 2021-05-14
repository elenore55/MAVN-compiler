#pragma once

#include <iostream>
#include "IR.h"

/**
 * This structure represent interference graph.
 */
typedef struct
{
	Variables* variables;	///< all variables from instructions
	char** values;			///< matrix value
	int size;				///< size of square matrix
} InterferenceGraph;


/**
 * Use this function to make interference graph from instructions list.
 * @param instructions pointer to instruction list
 * @return pointer to interference graph
 */
InterferenceGraph* doInterferenceGraph(Instructions* instructions);

/**
 * Use this function to free all interference graph resources.
 * @param ig pointer to InterferenceGraph structure which values are going to be free
 */
void freeInterferenceGraph(InterferenceGraph* ig);


/**
 * Use this function to print interference graph values in console.
 * @param ig pointer to interference graph structure which value will be printed in console.
 */
void printInterferenceGraph(InterferenceGraph* ig);

