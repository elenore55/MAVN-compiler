/* Autor: Milica Popović Datum: 31.05.2021. */

#include "InterferenceGraph.h"
#include <map>

InterferenceGraph* doInterferenceGraph(Instructions* instructions)
{
	std::map<std::string, Variable*, VariableNamesComparator> var_map;
	InterferenceGraph* ig = new InterferenceGraph();
	ig->variables = new Variables();
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++)
	{
		for (Variable* v : (*it)->def())
		{
			var_map[v->name()] = v;
		}
		for (Variable* v : (*it)->use())
		{
			var_map[v->name()] = v;
		}
	}
	int i = 0;

	// initializing interference graph

	for (std::map<std::string, Variable*>::iterator it = var_map.begin(); it != var_map.end(); it++, i++)
	{
		it->second->pos() = i;
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

		// add interference between variables in def and variables in use
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

void testInterferenceGraph(std::string filePath, InterferenceGraph* ig)
{
	std::ifstream ifs;
	ifs.open(filePath);
	if (!ifs)
	{
		throw std::runtime_error("File " + filePath + " does not exist.");
	}
	int n;	// number of variables in the interference graph
	int k;

	// read correct interference graph
	ifs >> n;
	std::vector<std::vector<int>> correctResult(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ifs >> k;
			correctResult[i].push_back(k);
		}
	}
	if (correctResult != ig->values)
	{
		throw std::runtime_error("Incorrect interference graph.");
	}
}
