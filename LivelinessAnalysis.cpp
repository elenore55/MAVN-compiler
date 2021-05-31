/* Autor: Milica Popović Datum: 29.05.2021. */

#include "LivelinessAnalysis.h"
#include <vector>

LivelinessAnalysis::LivelinessAnalysis(Instructions* instructions) : m_instructions(instructions) {}

void LivelinessAnalysis::Do()
{
	for (Instructions::reverse_iterator it = m_instructions->rbegin(); it != m_instructions->rend(); it++) {
		Instruction* instr = *it;
		instr->in().clear();
		instr->out().clear();
		Variables defRegs;
		Variables useRegs;

		// analysis is conducted for register variables only
		// memory variables are being filterd out

		for (Variable* v : instr->def())
		{
			if (v->type() == Variable::REG_VAR)
			{
				defRegs.push_back(v);
			}
		}
			
		for (Variable* v : instr->use())
		{
			if (v->type() == Variable::REG_VAR)
			{
				useRegs.push_back(v);
			}
		}
			
		instr->use() = useRegs;
		instr->def() = defRegs;
		instr->src() = useRegs;
		instr->dst() = defRegs;
	}

	while (true) {
		std::vector<Variables> in_prims(m_instructions->size());
		std::vector<Variables> out_prims(m_instructions->size());
		int i = m_instructions->size() - 1;

		for (Instructions::reverse_iterator it = m_instructions->rbegin(); it != m_instructions->rend(); it++, i--) 
		{
			Instruction* instr = *it;
			in_prims[i] = instr->in();
			out_prims[i] = instr->out();

			for (Instruction* s : instr->succ())
			{
				for (Variable* n : s->in())
				{
					instr->out().push_back(n);
				}
			}
				
			for (Variable* n : instr->use())
			{
				instr->in().push_back(n);
			}
				
			for (Variable* n : instr->out())
			{
				if (!variableExists(n, instr->def()))
				{
					instr->in().push_back(n);
				}
			}

			instr->out().sort();
			instr->out().unique();
			instr->in().sort();
			instr->in().unique();
		}
		if (done(in_prims, out_prims)) break;
	}
}

// returns true if no changes occurred between two iterations
bool LivelinessAnalysis::done(const std::vector<Variables>& in_prims, const std::vector<Variables>& out_prims)
{
	int i = 0;
	for (Instruction* instr : *m_instructions) 
	{
		if (instr->in() != in_prims[i] || instr->out() != out_prims[i]) return false;
		i++;
	}
	return true;	
}
