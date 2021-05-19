#pragma once

#include "IR.h"
#include "LexicalAnalysis.h"
#include <map>

class InstructionGenerator
{
public:
	InstructionGenerator(TokenList tokenList);
	Instructions* getInstructions();
	Variables* getVariables();
	
private:
	TokenList m_tokenList;
	std::map<std::string, Variable*> m_variablesMap;
	std::map<std::string, int> m_lablesMap;
	std::map<std::string, int> m_functionsMap;
	std::map<int, Instruction*> m_instructionsMap;

	void determinePredAndSucc(Instructions* instructions);
};