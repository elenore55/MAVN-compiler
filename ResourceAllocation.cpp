#include "ResourceAllocation.h"
#include <set>

ResourceAllocation::ResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig) 
	: m_simplificationStack(simplificationStack), m_interferenceGraph(ig) {}

bool ResourceAllocation::Do()
{
	while (m_simplificationStack->size() > 0) 
	{
		Variable* v = m_simplificationStack->top();
		std::set<int> usedColors;
		int i = v->pos();
		for (Variables::iterator it = m_interferenceGraph->variables->begin(); it != m_interferenceGraph->variables->end(); it++) 
		{
			int j = (*it)->pos();
			if (m_interferenceGraph->values[i][j] == __INTERFERENCE__) 
			{
				if ((*it)->assignment() != Regs::no_assign)
					usedColors.insert((*it)->assignment());
			}
		}

		for (int r = 1; r <= __REG_NUMBER__; r++) 
		{
			if (usedColors.find(r) == usedColors.end()) 
			{
				v->assignment() = (Regs)r;
				break;
			}
		}
		m_simplificationStack->pop();
	}
	return true;
}

bool ResourceAllocation::check()
{
	std::set<int> colors;
	for (Variables::iterator it1 = m_interferenceGraph->variables->begin(); it1 != m_interferenceGraph->variables->end(); it1++) 
	{
		for (Variables::iterator it2 = it1; it2 != m_interferenceGraph->variables->end(); it2++) 
		{
			if (*it2 == *it1) continue;
			Variable* v = *it1;
			Variable* u = *it2;
			if (m_interferenceGraph->values[v->pos()][u->pos()] == 1 && v->assignment() == u->assignment()) 
				return false;
			colors.insert(v->assignment());
			colors.insert(u->assignment());
		}
	}
	if (colors.size() > __REG_NUMBER__) return false;
	return true;
}
