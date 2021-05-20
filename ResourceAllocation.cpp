#include "ResourceAllocation.h"
#include <set>

bool doResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig)
{
	while (simplificationStack->size() > 0) {
		Variable* v = simplificationStack->top();
		std::set<int> usedColors;
		int i = v->pos();
		for (Variables::iterator it = ig->variables->begin(); it != ig->variables->end(); it++) {
			int j = (*it)->pos();
			if (ig->values[i][j] == __INTERFERENCE__) {
				if ((*it)->assignment() != Regs::no_assign)
					usedColors.insert((*it)->assignment());
			}
		}

		for (int r = 1; r <= __REG_NUMBER__; r++) {
			if (usedColors.find(r) == usedColors.end()) {
				v->assignment() = (Regs)r;
				break;
			}
		}
		simplificationStack->pop();
	}
	return true;
}

bool checkResourceAllocation(InterferenceGraph* ig)
{
	std::set<int> colors;
	for (Variables::iterator it1 = ig->variables->begin(); it1 != ig->variables->end(); it1++) {
		for (Variables::iterator it2 = it1; it2 != ig->variables->end(); it2++) {
			if (*it2 == *it1) continue;
			Variable* v = *it1;
			Variable* u = *it2;
			if (ig->values[v->pos()][u->pos()] == 1 && v->assignment() == u->assignment()) return false;
			colors.insert(v->assignment());
			colors.insert(u->assignment());
		}
	}
	if (colors.size() > __REG_NUMBER__) return false;
	return true;
}

Instructions* removeMove(Instructions* instrs)
{
	for (Instructions::iterator it = instrs->begin(); it != instrs->end(); it++) {
		Instruction* instr = *it;
		// if (instr->type() != InstructionType::T_MOVE) continue;
		//if (instr->dst()->assigment() == instr->src()->assigment()) {
		//	it = instrs->erase(it);
		//	it--;
		//}
	}
	return instrs;
}
