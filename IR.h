#ifndef __IR__
#define __IR__

#include <iostream>
#include "Types.h"
#include <map>

using Labels = std::map<std::string, int>;
using Functions = std::map<std::string, int>;

/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign), m_value(0) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign), m_value(0) {}
	int& pos();
	std::string& name();
	Regs& assignment();
	VariableType& type();
	int& value();

	friend std::ostream& operator<< (std::ostream& os, Variable* var)
	{
		os << "NAME: " << var->m_name << "  TYPE: " << var->m_type << "  POS: " << var->m_position;
		return os;
	}

private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
	int m_value;
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src), m_def(dst), m_use(src) 
	{
		m_src.sort();
		m_src.unique();
		m_use.sort();
		m_use.unique();
	}

	InstructionType& type();
	std::string& instructionString();
	std::string& label();

	Variables& dst();
	Variables& src();

	Variables& use();
	Variables& def();
	Variables& in();
	Variables& out();
	std::list<Instruction*>& succ();
	std::list<Instruction*>& pred();

	void addPred(Instruction* instr);
	void addSucc(Instruction* instr);

	int& pos();

	friend std::ostream& operator<< (std::ostream& os, Instruction* instr)
	{
		//os << "TYPE: " << instr->m_type << "  POS: " << instr->m_position << "\n";
		//os << "DST:\n";
		//for (Variable* var : instr->m_dst)
		//	os << var << "\n";
		//os << "SRC:\n";
		//for (Variable* var : instr->m_src)
		//	os << var << "\n";
		os << instr->m_instructionString << "\n";
		os << "PRED:\n";
		for (Instruction* i : instr->m_pred)
			os << i->instructionString() << "\n";
		os << "SUCC:\n";
		for (Instruction* i : instr->m_succ)
			os << i->instructionString() << "\n";
		return os; 
	}
	void formInstructionString();
	void updateInstructionString();

private:
	int m_position;
	InstructionType m_type;
	std::string m_instructionString;
	std::string m_label;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;

};


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;

bool variableExists(Variable* variable, Variables variables);

Instructions& getInstructions();

std::ostream& operator<< (std::ostream& os, Instruction* instr);

std::ostream& operator<< (std::ostream& os, Variable* var);

#endif
