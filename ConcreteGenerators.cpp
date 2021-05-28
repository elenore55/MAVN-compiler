#include "ConcreteGenerators.h"

Instruction* ADD::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName1 = (++it)->getValue();
	it++;
	std::string srcName2 = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName1], variablesMap[srcName2] };
	Instruction* instr = new Instruction(++instrCount, I_ADD, dstVars, srcVars);
	instr->instructionString() = "add `d, `s, `s;";

	return instr;
}

Instruction* SUB::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName1 = (++it)->getValue();
	it++;
	std::string srcName2 = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName1], variablesMap[srcName2] };
	Instruction* instr = new Instruction(++instrCount, I_SUB, dstVars, srcVars);
	instr->instructionString() = "sub `d, `s, `s;";
	return instr;
}

Instruction* NOR::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName1 = (++it)->getValue();
	it++;
	std::string srcName2 = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName1], variablesMap[srcName2] };
	Instruction* instr = new Instruction(++instrCount, I_NOR, dstVars, srcVars);
	instr->instructionString() = "nor `d, `s, `s;";
	return instr;
}

Instruction* SEQ::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName1 = (++it)->getValue();
	it++;
	std::string srcName2 = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName1], variablesMap[srcName2] };
	Instruction* instr = new Instruction(++instrCount, I_SEQ, dstVars, srcVars);
	instr->instructionString() = "seq `d, `s, `s;";
	return instr;
}

Instruction* ADDI::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	it++;
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_ADDI, dstVars, srcVars);
	instr->instructionString() = "addi `d, `s, " + (++it)->getValue() + ";";
	return instr;
}

Instruction* LA::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_LA, dstVars, srcVars);
	std::string s = variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
	instr->instructionString() = "la `d, " + s + ";";
	return instr;
}

Instruction* LW::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string constant = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_LW, dstVars, srcVars);
	std::string s = variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
	instr->instructionString() = "lw `d, " + constant + "(" + s + ");";
	return instr;
}

Instruction* SW::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string srcName = (++it)->getValue();
	it++;
	std::string constant = (++it)->getValue();
	it++;
	std::string dstName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_SW, dstVars, srcVars);
	std::string s = variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`d";
	instr->instructionString() = "sw `s, " + constant + "(" + s + ");";
	return instr;
}

Instruction* ABS::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_ABS, dstVars, srcVars);
	instr->instructionString() = "abs `d, `s;";
	return instr;
}

Instruction* LI::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	Variables dstVars = { variablesMap[dstName] };
	Instruction* instr = new Instruction(++instrCount, I_LI, dstVars, Variables());
	instr->instructionString() = "li `d, " + (++it)->getValue() + ";";
	return instr;
}

Instruction* BLTZ::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string srcName = (++it)->getValue();
	it++;
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_BLTZ, Variables(), srcVars);
	instr->instructionString() = "btlz `s, " + (++it)->getValue() + ";";
	instr->label() = it->getValue();
	return instr;
}

Instruction* B::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	Instruction* instr = new Instruction(++instrCount, I_B, Variables(), Variables());
	instr->instructionString() = "b, " + (++it)->getValue() + ";";
	instr->label() = it->getValue();
	return instr;
}

Instruction* NOP::generate(TokenList::iterator& it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	Instruction* instr = new Instruction(++instrCount, I_NOP, Variables(), Variables());
	instr->instructionString() = "nop;";
	return instr;
}

Variable* MEM::generate(TokenList::iterator it)
{
	Variable* v = new Variable();
	v->type() = Variable::MEM_VAR;
	v->name() = it->getValue();
	*it++;
	v->value() = std::stoi(it->getValue());
	*it--;
	return v;
}

Variable* REG::generate(TokenList::iterator it)
{
	Variable* v = new Variable();
	v->type() = Variable::REG_VAR;
	v->name() = it->getValue();
	return v;
}
