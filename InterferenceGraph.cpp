#include "InterferenceGraph.h"

InterferenceGraph* doInterferenceGraph(Instructions* instructions)
{
	InterferenceGraph* ig = new InterferenceGraph();
	ig->variables = new Variables();
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++) {
		Instruction* instr = *it;
		for (Variable* v : instr->in()) ig->variables->push_back(v);
		for (Variable* v : instr->out()) ig->variables->push_back(v);
	}
	ig->variables->sort();
	ig->variables->unique();
	ig->size = ig->variables->size();

	ig->values = new char* [ig->size];
	for (int i = 0; i < ig->size; ++i)
		ig->values[i] = new char[ig->size];

	for (int i = 0; i < ig->size; i++)
		for (int j = 0; j < ig->size; j++)
			ig->values[i][j] = __EMPTY__;
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++) {
		Instruction* instr = *it;
		for (Variable* v : instr->in()) {
			for (Variable* u : instr->in()) {
				if (u != v) {
					ig->values[v->pos()][u->pos()] = __INTERFERENCE__;
				}
			}
		}
		for (Variable* v : instr->out()) {
			for (Variable* u : instr->out()) {
				if (u != v) {
					ig->values[v->pos()][u->pos()] = __INTERFERENCE__;
				}
			}
		}
	}
	return ig;
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
			std::cout << ig->values[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}
