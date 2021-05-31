/* Autor: Milica Popović Datum: 31.05.2021. */

#include "ResourceAllocation.h"
#include <set>

ResourceAllocation::ResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig) 
	: m_simplificationStack(simplificationStack), m_interferenceGraph(ig) {}

void ResourceAllocation::Do()
{
	while (m_simplificationStack->size() > 0) 
	{
		Variable* v = m_simplificationStack->top();
		std::set<int> usedColors;
		int i = v->pos();

		// fill set of assignments used by variables interfering with current variable
		for (Variables::iterator it = m_interferenceGraph->variables->begin(); it != m_interferenceGraph->variables->end(); it++) 
		{
			int j = (*it)->pos();
			if (m_interferenceGraph->values[i][j] == __INTERFERENCE__) 
			{
				if ((*it)->assignment() != Regs::no_assign)
				{
					usedColors.insert((*it)->assignment());
				}
			}
		}

		for (int r = 1; r <= __REG_NUMBER__; r++) 
		{
			// assign first resource not used used by interfering variables
			if (usedColors.find(r) == usedColors.end()) 
			{
				v->assignment() = (Regs)r;	
				break;
			}
		}
		m_simplificationStack->pop();
	}
}

void ResourceAllocation::check()
{
	bool correct = true;
	std::set<int> colors;	// set of used assignments
	for (Variables::iterator it1 = m_interferenceGraph->variables->begin(); it1 != m_interferenceGraph->variables->end(); it1++) 
	{
		for (Variables::iterator it2 = it1; it2 != m_interferenceGraph->variables->end(); it2++) 
		{
			if (*it2 == *it1) continue;
			Variable* v = *it1;
			Variable* u = *it2;

			// check if two interfering variables share the same assingment
			if (m_interferenceGraph->values[v->pos()][u->pos()] == 1 && v->assignment() == u->assignment())
			{
				correct = false;
				break;
			}
			colors.insert(v->assignment());
			colors.insert(u->assignment());
		}
	}

	// check if more assignments were used than it is allowed
	if (colors.size() > __REG_NUMBER__) 
		correct =  false;

	if (!correct)
		throw std::runtime_error("Resource Allocation failed!");
}
