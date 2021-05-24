#include "InterferenceGraph.h"
#include <map>

InterferenceGraph* doInterferenceGraph(Instructions* instructions)
{
	std::map<std::string, Variable*> var_map;
	InterferenceGraph* ig = new InterferenceGraph();
	ig->variables = new Variables();
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++)
	{
		for (Variable* v : (*it)->def())
		{
			var_map[v->name()] = v;
		}
	}

	for (std::map<std::string, Variable*>::iterator it = var_map.begin(); it != var_map.end(); it++)
	{
		ig->variables->push_back(it->second);
	}
	int size = ig->variables->size();
	ig->size = size;
	ig->values.resize(size);
	for (int i = 0; i < size; i++)
	{
		ig->values[i].resize(size);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ig->values[i][j] = __EMPTY__;
		}
	}

	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++) 
	{
		Instruction* instr = *it;
		Variables def = instr->def();
		Variables out = instr->out();
		for (Variable* v : def) 
		{
			for (Variable* u : out)
			{
				if (u != v) 
				{
					ig->values[v->pos()][u->pos()] = __INTERFERENCE__;
					ig->values[u->pos()][v->pos()] = __INTERFERENCE__;
				}
			}
		}
	}
	return ig;
}

void freeInterferenceGraph(InterferenceGraph* ig)
{
	delete ig;
}

void printInterferenceGraph(InterferenceGraph* ig)
{
	for (Variable* v : *(ig->variables))
	{
		std::cout << v->name() << "  ";
	}
	std::cout << std::endl;
	int n = ig->variables->size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << ig->values[i][j] << "   ";
		}
		std::cout << std::endl;
	}
}
