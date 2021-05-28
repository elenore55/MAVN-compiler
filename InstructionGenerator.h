#pragma once

#include "IR.h"
#include "LexicalAnalysis.h"
#include <map>
#include "ConcreteGenerators.h"

class InstructionGenerator
{
public:
	InstructionGenerator(TokenList tokenList, Labels labels, Functions functions, Variables* variables);
	
	Instructions* getInstructions();

	~InstructionGenerator();

private:
	TokenList m_tokenList;
	Instructions* m_instructions;
	std::map<std::string, Variable*> m_variablesMap;
	Labels m_lablesMap;
	Functions m_functionsMap;
	std::map<int, Instruction*> m_instructionsMap;
	std::map<TokenType, InstrGeneratingFunc*> m_instructionsGenMap;

	void generateInstructions();
	void determinePredAndSucc();
};