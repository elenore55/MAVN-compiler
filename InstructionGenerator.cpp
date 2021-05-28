#include "InstructionGenerator.h"

InstructionGenerator::InstructionGenerator(TokenList tokenList, Labels labels, Functions functions, Variables* variables) :
	m_tokenList(tokenList), m_lablesMap(labels), m_functionsMap(functions), m_instructions(nullptr)
{
	m_instructionsGenMap[T_ADD] = new ADD();
	m_instructionsGenMap[T_SUB] = new SUB();
	m_instructionsGenMap[T_ADDI] = new ADDI();
	m_instructionsGenMap[T_LI] = new LI();
	m_instructionsGenMap[T_LW] = new LW();
	m_instructionsGenMap[T_SW] = new SW();
	m_instructionsGenMap[T_NOR] = new NOR();
	m_instructionsGenMap[T_SEQ] = new SEQ();
	m_instructionsGenMap[T_NOP] = new NOP();
	m_instructionsGenMap[T_BLTZ] = new BLTZ();
	m_instructionsGenMap[T_B] = new B();
	m_instructionsGenMap[T_LA] = new LA();
	m_instructionsGenMap[T_ABS] = new ABS();

	for (Variable* v : *variables)
	{
		m_variablesMap[v->name()] = v;
	}
}

Instructions* InstructionGenerator::getInstructions()
{
	if (m_instructions == nullptr)
		generateInstructions();
	return m_instructions;
}

InstructionGenerator::~InstructionGenerator()
{
	for (std::map<TokenType, InstrGeneratingFunc*>::iterator it = m_instructionsGenMap.begin(); it != m_instructionsGenMap.end(); it++)
	{
		delete it->second;
	}
}

void InstructionGenerator::generateInstructions()
{
	m_instructions = new Instructions();
	int instrCount = 0;

	for (TokenList::iterator it = m_tokenList.begin(); it != m_tokenList.end(); it++)
	{
		switch (it->getType())
		{
		case T_ADD: case T_SUB: case T_ADDI: case T_NOR: case T_LA: case T_LW: case T_SW: 
		case T_SEQ: case T_ABS: case T_LI: case T_BLTZ: case T_B: case T_NOP:
		{
			Instruction* instr = m_instructionsGenMap[it->getType()]->generate(it, m_variablesMap, instrCount);
			m_instructions->push_back(instr);
			m_instructionsMap[instrCount] = instr;
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

