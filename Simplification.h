#pragma once

#include <stack>
#include "InterferenceGraph.h"

std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree);

void printSimplificationStack(std::stack<Variable*>* stack);