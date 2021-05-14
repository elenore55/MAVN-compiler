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

		for (int r = 0; r < __REG_NUMBER__; r++) {
			if (usedColors.find(r) == usedColors.end()) {
				v->assignment() = (Regs)r;
				break;
			}
		}
		simplificationStack->pop();
	}
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
