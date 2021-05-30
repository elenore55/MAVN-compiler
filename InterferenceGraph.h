#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "IR.h"

/**
 * This structure represent interference graph.
 */
typedef struct
{
	Variables* variables;	///< all variables from instructions
	std::vector<std::vector<int>> values;			///< matrix value
	int size;				///< size of square matrix
} InterferenceGraph;

struct VariableNamesComparator
{
	bool operator()(const std::string& left, const std::string& right) const
	{
		return std::stoi(left.substr(1)) < std::stoi(right.substr(1));
	}
};

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

void testInterferenceGraph(std::string filePath, InterferenceGraph* ig);