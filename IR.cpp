#include "IR.h"

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


bool variableExists(Variable* variable, Variables variables)
{
	bool ret = false;

	Variables::iterator it;

	for (it = variables.begin(); it != variables.end(); it++)
	{
		if (*it == variable)
		{
			ret = true;
			break;
		}
	}

	return ret;
}

Instructions& getInstructions()
{
	// TODO: insert return statement here
	return Instructions();
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
