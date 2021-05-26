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
	Labels getLabels();
	Functions getFunctions();

private:
	TokenList m_tokenList;
	Instructions* m_instructions;
	Variables* m_variables;
	std::map<std::string, Variable*> m_variablesMap;
	Labels m_lablesMap;
	Functions m_functionsMap;
	std::map<int, Instruction*> m_instructionsMap;

	void generateVariables();
	void generateInstructions();
	void determinePredAndSucc();
	void validateLabels();
};