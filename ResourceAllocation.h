#pragma once

#include <stack>
#include "IR.h"
#include "InterferenceGraph.h"

class ResourceAllocation 
{
public:
	ResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig);
	bool Do();
	bool check();

private:
	std::stack<Variable*>* m_simplificationStack;
	InterferenceGraph* m_interferenceGraph;
};
