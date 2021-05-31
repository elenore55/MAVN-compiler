/* Autor: Milica Popović Datum: 29.05.2021. */

#pragma once

#include <stack>
#include "InterferenceGraph.h"

/*
* Implements the simplification algorithm
* 
* @return generated simplification stack
*/
std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree);

/**
* Prints simplification stack in console
*/
void printSimplificationStack(std::stack<Variable*>* stack);