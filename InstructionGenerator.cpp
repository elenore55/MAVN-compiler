#include "InstructionGenerator.h"

InstructionGenerator::InstructionGenerator(TokenList tokenList) : m_tokenList(tokenList), m_instructions(nullptr) {}

Instructions* InstructionGenerator::getInstructions()
{
	if (m_instructions == nullptr)
		generateInstructions();
	return m_instructions;
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
			v->value() = stoi(it->getValue());
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

Labels InstructionGenerator::getLabels()
{
	return m_lablesMap;
}

Functions InstructionGenerator::getFunctions()
{
	return m_functionsMap;
}

void InstructionGenerator::generateInstructions()
{
	m_instructions = new Instructions();
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
			std::string s1 = m_variablesMap[srcName1]->type() == Variable::MEM_VAR ? srcName1 : "`s";
			std::string s2 = m_variablesMap[srcName2]->type() == Variable::MEM_VAR ? srcName2 : "`s";
			instr->instructionString() = "add `d, " + s1 + ", " + s2 + ";";
			m_instructions->push_back(instr);
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
			std::string s1 = m_variablesMap[srcName1]->type() == Variable::MEM_VAR ? srcName1 : "`s";
			std::string s2 = m_variablesMap[srcName2]->type() == Variable::MEM_VAR ? srcName2 : "`s";
			instr->instructionString() = "sub `d, " + s1 + ", " + s2 + ";";
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_NOR:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName1 = (++it)->getValue();
			it++;
			std::string srcName2 = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName1], m_variablesMap[srcName2] };
			Instruction* instr = new Instruction(++instrCount, I_NOR, dstVars, srcVars);
			std::string s1 = m_variablesMap[srcName1]->type() == Variable::MEM_VAR ? srcName1 : "`s";
			std::string s2 = m_variablesMap[srcName2]->type() == Variable::MEM_VAR ? srcName2 : "`s";
			instr->instructionString() = "nor `d, " + s1 + ", " + s2 + ";";
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_SEQ:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName1 = (++it)->getValue();
			it++;
			std::string srcName2 = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName1], m_variablesMap[srcName2] };
			Instruction* instr = new Instruction(++instrCount, I_SEQ, dstVars, srcVars);
			std::string s1 = m_variablesMap[srcName1]->type() == Variable::MEM_VAR ? srcName1 : "`s";
			std::string s2 = m_variablesMap[srcName2]->type() == Variable::MEM_VAR ? srcName2 : "`s";
			instr->instructionString() = "seq `d, " + s1 + ", " + s2 + ";";
			m_instructions->push_back(instr);
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
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_ADDI, dstVars, srcVars);
			std::string s = m_variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
			instr->instructionString() = "addi `d, " + s + ", " + (++it)->getValue() + ";";
			m_instructions->push_back(instr);
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
			std::string s = m_variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
			instr->instructionString() = "la `d, " + s + ";";
			m_instructions->push_back(instr);
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
			std::string s = m_variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
			instr->instructionString() = "lw `d, " + constant + "(" + s + ");";
			m_instructions->push_back(instr);
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
			std::string s = m_variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
			instr->instructionString() = "sw `d, " + constant + "(" + s + ");";
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_ABS:
		{
			std::string dstName = (++it)->getValue();
			it++;
			std::string srcName = (++it)->getValue();
			Variables dstVars = { m_variablesMap[dstName] };
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_ABS, dstVars, srcVars);
			std::string s = m_variablesMap[srcName]->type() == Variable::MEM_VAR ? srcName : "`s";
			instr->instructionString() = "abs `d, " + s + ";";
			m_instructions->push_back(instr);
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
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_BLTZ:
		{
			std::string srcName = (++it)->getValue();
			it++;
			Variables srcVars = { m_variablesMap[srcName] };
			Instruction* instr = new Instruction(++instrCount, I_BLTZ, Variables(), srcVars);
			instr->instructionString() = "btlz `s, " + (++it)->getValue() + ";";
			instr->label() = it->getValue();
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_B:
		{
			Instruction* instr = new Instruction(++instrCount, I_B, Variables(), Variables());
			instr->instructionString() = "b, " + (++it)->getValue() + ";";
			instr->label() = it->getValue();
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
			break;
		}
		case T_NOP:
		{
			Instruction* instr = new Instruction(++instrCount, I_NOP, Variables(), Variables());
			instr->instructionString() = "nop;";
			m_instructions->push_back(instr);
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
	determinePredAndSucc();
}

void InstructionGenerator::determinePredAndSucc()
{
	for (Instructions::iterator it = m_instructions->begin(); it != m_instructions->end(); it++)
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

void InstructionGenerator::generateInstructionString(Instruction* instr, std::string name, Variable* dst, Variable* src1, Variable* src2)
{
	Variables dstVars;
}
