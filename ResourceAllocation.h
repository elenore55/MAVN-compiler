#pragma once

#include <stack>
#include "IR.h"
#include "InterferenceGraph.h"

/**
 * Use this function to do resource allocation algorithm.
 * @param simplificationStack pointer to simplification stack
 * @param ig pointer to interference graph
 * @return true if no spill is detected during resource allocation algorithm, false actual spill detected
 */
bool doResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig);


/**
 * Use this function remove unnecessary move instruction from graph flow.
 * @param instrs list of instructions
 * @return list of instructions without unnecessary move instructions
 */
Instructions* removeMove(Instructions* instrs);