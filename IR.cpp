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
