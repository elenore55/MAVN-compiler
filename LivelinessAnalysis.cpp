#include "LivelinessAnalysis.h"
#include <vector>

bool done(Instructions* instructions, const std::vector<Variables>& in_prims, const std::vector<Variables>& out_prims) {
	int i = 0;
	for (Instruction* instr : *instructions) {
		if (instr->in() != in_prims[i] || instr->out() != out_prims[i]) return false;
		i++;
	}
	return true;
}

void livenessAnalysis(Instructions* instructions)
{
	for (Instructions::reverse_iterator it = instructions->rbegin(); it != instructions->rend(); it++) {
		Instruction* instr = *it;
		instr->in().clear();
		instr->out().clear();
		Variables defRegs;
		Variables useRegs;
		for (Variable* v : instr->def())
			if (v->type() == Variable::REG_VAR)
				defRegs.push_back(v);
		for (Variable* v : instr->use())
			if (v->type() == Variable::REG_VAR)
				useRegs.push_back(v);
		instr->use() = useRegs;
		instr->def() = defRegs;
		instr->src() = useRegs;
		instr->dst() = defRegs;
	}

	while (true) {
		std::vector<Variables> in_prims(instructions->size());
		std::vector<Variables> out_prims(instructions->size());
		int i = instructions->size() - 1;
		for (Instructions::reverse_iterator it = instructions->rbegin(); it != instructions->rend(); it++, i--) {
			Instruction* instr = *it;
			in_prims[i] = instr->in();
			out_prims[i] = instr->out();

			for (Instruction* s : instr->succ())
				for (Variable* n : s->in())
					instr->out().push_back(n);
			for (Variable* n : instr->use()) instr->in().push_back(n);
			for (Variable* n : instr->out())
				if (!variableExists(n, instr->def()))
					instr->in().push_back(n);

			instr->out().sort();
			instr->out().unique();
			instr->in().sort();
			instr->in().unique();
		}
		if (done(instructions, in_prims, out_prims)) break;
	}
}
