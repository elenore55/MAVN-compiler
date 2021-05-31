/* Autor: Milica Popović Datum: 31.05.2021. */

#include "ConcreteGenerators.h"

// generates add instruction
Instruction* ADD::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates sub instruction
Instruction* SUB::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates nor instruction
Instruction* NOR::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates seq instruction
Instruction* SEQ::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates addi instruction
Instruction* ADDI::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates la instruction
Instruction* LA::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_LA, dstVars, srcVars);
	instr->instructionString() = "la `d, " + srcName + ";";
	return instr;
}

// generates lw instruction
Instruction* LW::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	std::string constant = (++it)->getValue();
	it++;
	std::string srcName = (++it)->getValue();
	Variables dstVars = { variablesMap[dstName] };
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_LW, dstVars, srcVars);
	instr->instructionString() = "lw `d, " + constant + "(`s);";
	return instr;
}

// generates sw instruction
Instruction* SW::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string srcName1 = (++it)->getValue();
	it++;
	std::string constant = (++it)->getValue();
	it++;
	std::string srcName2 = (++it)->getValue();
	Variables dstVars = {};
	Variables srcVars = { variablesMap[srcName1], variablesMap[srcName2] };
	Instruction* instr = new Instruction(++instrCount, I_SW, dstVars, srcVars);
	instr->instructionString() = "sw `s, " + constant + "(`s);";
	return instr;
}

// generates abs instruction
Instruction* ABS::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
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

// generates li instruction
Instruction* LI::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string dstName = (++it)->getValue();
	it++;
	Variables dstVars = { variablesMap[dstName] };
	Instruction* instr = new Instruction(++instrCount, I_LI, dstVars, Variables());
	instr->instructionString() = "li `d, " + (++it)->getValue() + ";";
	return instr;
}

// generates bltz instruction
Instruction* BLTZ::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	std::string srcName = (++it)->getValue();
	it++;
	Variables srcVars = { variablesMap[srcName] };
	Instruction* instr = new Instruction(++instrCount, I_BLTZ, Variables(), srcVars);
	instr->instructionString() = "btlz `s, " + (++it)->getValue() + ";";
	instr->label() = it->getValue();
	return instr;
}

// generates b instruction
Instruction* B::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	Instruction* instr = new Instruction(++instrCount, I_B, Variables(), Variables());
	instr->instructionString() = "b " + (++it)->getValue() + ";";
	instr->label() = it->getValue();
	return instr;
}

// generates nop instruction
Instruction* NOP::generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount)
{
	Instruction* instr = new Instruction(++instrCount, I_NOP, Variables(), Variables());
	instr->instructionString() = "nop;";
	return instr;
}