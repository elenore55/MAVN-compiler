/* Autor: Milica Popović Datum: 29.05.2021. */

#pragma once

#include "IR.h"
#include "LexicalAnalysis.h"


class InstrGeneratingFunc
{
public:

	/**
	* Virulal method for generating instruction from tokens
	* 
	* @ return pointer to generated instruction
	*/
	virtual Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) = 0;
};

/**
* Derived classes for generating concrete instructions
*/

class ADD : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class SUB : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};
 
class NOR : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class SEQ : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class ADDI : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class LA : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class LW : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class SW : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class ABS : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class LI : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class BLTZ : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class B : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};

class NOP : public InstrGeneratingFunc
{
public:
	Instruction* generate(TokenList::iterator it, std::map<std::string, Variable*>& variablesMap, int& instrCount) override;
};
