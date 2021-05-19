#include "InstructionGenerator.h"

InstructionGenerator::InstructionGenerator(TokenList tokenList) : m_tokenList(tokenList) {}

Instructions* InstructionGenerator::getInstructions()
{
	Instructions* instructions = new Instructions();
	Variables* variables = getVariables();
	int instrCount = 0;
	for (TokenList::iterator it = m_tokenList.begin(); it != m_tokenList.end(); it++)
	{
		switch (it->getType())
		{
		case T_ADD:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName1 = (++it)->getValue();
			it++;
			std::string srcName2 = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName1], m_variablesMap[srcName2] };
			Instruction* instr = new Instruction(++instrCount, I_ADD, dstVars, srcVars);
			instr->instructionString() = "add `d, `s, `s;";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_SUB:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName1 = (++it)->getValue();
			it++;
			std::string srcName2 = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName1], m_variablesMap[srcName2] };
			Instruction* instr = new Instruction(++instrCount, I_SUB, dstVars, srcVars);
			instr->instructionString() = "sub `d, `s, `s;";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_ADDI:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName = (++it)->getValue();
			it++;
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName]};
			Instruction* instr = new Instruction(++instrCount, I_ADDI, dstVars, srcVars);
			instr->instructionString() = "addi `d, `s, " + (++it)->getValue() + ";";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_LA:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_LA, dstVars, srcVars);
			instr->instructionString() = "la `d, `s;";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_LW:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string constant = (++it)->getValue();
			it++;
			std::string srcName = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_LW, dstVars, srcVars);
			instr->instructionString() = "lw `d, " + constant + "(`s);";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_SW:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string constant = (++it)->getValue();
			it++;
			std::string srcName = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_SW, dstVars, srcVars);
			instr->instructionString() = "sw `d, " + constant + "(`s);";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_LI:
		{
			std::string dstName = (++it)->getValue();
			it++;
			Variables dstVars = { m_variablesMap[dstName] };
			Instruction* instr = new Instruction(++instrCount, I_LI, dstVars, Variables());
			instr->instructionString() = "li `d, " + (++it)->getValue() + ";";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_BLTZ:
		{
			std::string dstName = (++it)->getValue();
			it++;
			Variables dstVars = { m_variablesMap[dstName] };
			Instruction* instr = new Instruction(++instrCount, I_BLTZ, dstVars, Variables());
			instr->instructionString() = "btlz `d, " + (++it)->getValue() + ";";
			instr->label() = it->getValue();
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_B:
		{
			Instruction* instr = new Instruction(++instrCount, I_B, Variables(), Variables());
			instr->instructionString() = "b, " + (++it)->getValue() + ";";
			instr->label() = it->getValue();
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_NOP:
		{
			Instruction* instr = new Instruction(++instrCount, I_NOP, Variables(), Variables());
			instr->instructionString() = "nop";
			instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_ID:
		{
			m_lablesMap[it->getValue()] = instrCount + 1;
			break;
		}
		case T_FUNC:
		{
			m_functionsMap[(++it)->getValue()] = instrCount + 1;
			break;
		}
		default:
			break;
		}
	}
	determinePredAndSucc(instructions);
	return instructions;
}

Variables* InstructionGenerator::getVariables()
{
	Variables* variables = new Variables();
	int varCount = -1;
	for (TokenList::iterator it = m_tokenList.begin(); it != m_tokenList.end(); it++)
	{
		switch (it->getType())
		{
		case T_MEM:
		{
			Variable* v = new Variable();
			v->type() = Variable::MEM_VAR;
			it++;
			v->name() = it->getValue();
			it++;
			v->value() = stoi(it->getValue()); // can this only be int
			m_variablesMap[v->name()] = v;
			variables->push_back(v);
			break;
		}
		case T_REG:
		{
			Variable* v = new Variable();
			v->type() = Variable::REG_VAR;
			it++;
			v->name() = it->getValue();
			m_variablesMap[v->name()] = v;
			v->pos() = ++varCount;
			variables->push_back(v);
			break;
		}
		default:
			break;
		}
	}
	return variables;
}

void InstructionGenerator::determinePredAndSucc(Instructions* instructions)
{
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++)
	{
		Instruction* instr = *it;
		if (instr->type() == I_BLTZ)
		{
			if (instr->pos() < m_instructionsMap.size())
			{
				instr->addSucc(m_instructionsMap[instr->pos() + 1]);
				m_instructionsMap[instr->pos() + 1]->addPred(instr);
			}
			int succPos = m_lablesMap[instr->label()];
			instr->addSucc(m_instructionsMap[succPos]);
			m_instructionsMap[succPos]->addPred(instr);
		}
		else if (instr->type() == I_B)
		{
			int succPos = m_lablesMap[instr->label()];
			instr->addSucc(m_instructionsMap[succPos]);
			m_instructionsMap[succPos]->addPred(instr);
		}
		else
		{
			if (instr->pos() < m_instructionsMap.size())
			{
				instr->addSucc(m_instructionsMap[instr->pos() + 1]);
				m_instructionsMap[instr->pos() + 1]->addPred(instr);
			}
		}
	}
}
