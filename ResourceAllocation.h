/* Autor: Milica Popović Datum: 31.05.2021. */

#pragma once

#include <stack>
#include "IR.h"
#include "InterferenceGraph.h"

class ResourceAllocation 
{
public:
	ResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig);

	/**
	* Conducts resource allocation
	*/
	void Do();

	/**
	* Checks correctness of resource allocation
	*/
	void check();

private:
	std::stack<Variable*>* m_simplificationStack;
	InterferenceGraph* m_interferenceGraph;
};
