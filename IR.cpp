/* Autor: Milica Popović Datum: 31.05.2021. */

#include "IR.h"
#include <algorithm>

Variables& Instruction::use()
{
    return m_use;
}

Variables& Instruction::def()
{
    return m_def;
}

Variables& Instruction::in()
{
    return m_in;
}

Variables& Instruction::out()
{
    return m_out;
}

std::list<Instruction*>& Instruction::succ()
{
    return m_succ;
}

std::list<Instruction*>& Instruction::pred()
{
    return m_pred;
}

void Instruction::addPred(Instruction* instr)
{
	m_pred.push_back(instr);
}

void Instruction::addSucc(Instruction* instr)
{
	m_succ.push_back(instr);
}

int& Instruction::pos()
{
	return m_position;
}

void Instruction::updateInstructionString()
{
	if (m_def.size() > 0)
	{
		// replace placeholder for destination variable
		std::string destReg = "$t" + std::to_string((*(m_def.begin()))->assignment() - 1);
		auto destPos = m_instructionString.find("`d");
		m_instructionString.replace(destPos, 2, destReg);
	}
	if (m_use.size() > 0)
	{
		// replace placeholder for first source variable with assigned resource
		std::string srcReg1 = "$t" + std::to_string((*(m_use.begin()))->assignment() - 1);
		auto src1Pos = m_instructionString.find("`s");
		m_instructionString.replace(src1Pos, 2, srcReg1);
	}
	if (m_use.size() == 2)
	{
		// replace placeholder for second source variable with assigned resource
		Variables::iterator it = m_use.begin();
		it++;
		std::string srcReg2 = "$t" + std::to_string((*it)->assignment() - 1);
		auto src2Pos = m_instructionString.rfind("`s");
		m_instructionString.replace(src2Pos, 2, srcReg2);
	}
}

InstructionType& Instruction::type()
{
	return m_type;
}

std::string& Instruction::instructionString()
{
	return m_instructionString;
}

std::string& Instruction::label()
{
	return m_label;
}

Variables& Instruction::dst()
{
	return m_dst;
}

Variables& Instruction::src()
{
	return m_src;
}


std::ostream& operator<<(std::ostream& os, Variable* var)
{
	os << "NAME: " << var->m_name << "  TYPE: " << var->m_type << "  POS: " << var->m_position;
	return os;
}

std::ostream& operator<<(std::ostream& os, Instruction* instr)
{
	os << "=======================================================\n";
	os << "TYPE: " << instr->m_type << "  POS: " << instr->m_position << "\n";
	os << "DST:\n";
	for (Variable* var : instr->m_dst)
		os << "\t" << var << "\n";
	os << "SRC:\n";
	for (Variable* var : instr->m_src)
		os << "\t" << var << "\n";
	os << "INSTRUCTION STRING: " << instr->m_instructionString << "\n";
	os << "PRED:\n";
	for (Instruction* i : instr->m_pred)
		os << "\t" << i->instructionString() << "\n";
	os << "SUCC:\n";
	for (Instruction* i : instr->m_succ)
		os << "\t" << i->instructionString() << "\n";
	os << "IN:\n";
	for (Variable* var : instr->m_in)
		os << "\t" << var << "\n";
	os << "OUT:\n";
	for (Variable* var : instr->m_out)
		os << "\t" << var << "\n";
	os << "=======================================================\n";
	return os;
}

bool variableExists(Variable* variable, Variables variables)
{
	return find(variables.begin(), variables.end(), variable) != variables.end();
}

int& Variable::pos()
{
	return m_position;
}

std::string& Variable::name()
{
	return m_name;
}

Regs& Variable::assignment()
{
	return m_assignment;
}

Variable::VariableType& Variable::type()
{
	return m_type;
}

int& Variable::value()
{
	return m_value;
}
