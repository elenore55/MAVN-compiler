/* Autor: Milica Popović Datum: 30.05.2021. */

#pragma once

#include "IR.h"
#include "LexicalAnalysis.h"
#include <map>
#include "ConcreteGenerators.h"

class InstructionGenerator
{
public:
	InstructionGenerator(TokenList tokenList, Labels labels, Functions functions, Variables* variables);
	
	/**
	* @ return a pointer to a list of instructions
	*/
	Instructions* getInstructions();

	~InstructionGenerator();

private:

	/**
	 * List of parsed tokens
	 */
	TokenList m_tokenList;

	/**
	* Pointer to the list of all instructions
	*/
	Instructions* m_instructions;

	/**
	* Map containing variable names as keys and variables as values
	*/
	std::map<std::string, Variable*> m_variablesMap;

	/**
	* Map containing lable names as keys and instruction positions as values
	*/
	Labels m_lablesMap;

	/**
	* Map containing function names as keys and instruction positions as values
	*/
	Functions m_functionsMap;

	/**
	* Map containing instruction positions as keys and instructios as values
	*/
	std::map<int, Instruction*> m_instructionsMap;

	/**
	* Map containing token types as keys and objects 
	* for genereting concrete instructions as values
	*/
	std::map<TokenType, InstrGeneratingFunc*> m_instructionsGenMap;

	/**
	* Generates list of instructions from tokens
	*/
	void generateInstructions();

	/**
	* Determines a set of predecessors and successors for each instruction
	*/
	void determinePredAndSucc();
};