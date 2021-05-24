#include "FileWriter.h"
#include <map>

FileWriter::FileWriter(std::string path) : m_path(path) {}

void FileWriter::writeToSFile(Instructions* instructions, Variables* variables, Labels labels, Functions functions)
{
	std::ofstream os;
	os.open(m_path);
	if (!os)
	{
		throw std::runtime_error("Could not opet output file.");
	}
	for (Functions::iterator it = functions.begin(); it != functions.end(); it++)
	{
		os << ".globl " << it->first << std::endl;
	}
	os << "\n.data\n";
	for (Variables::iterator it = variables->begin(); it != variables->end(); it++)
	{
		Variable* v = *it;
		if (v->type() == Variable::MEM_VAR)
			os << v->name() << ":\t.word " << v->value() << std::endl;
	}
	os << "\n.text\n";
	int instrCount = 1;
	for (Instructions::iterator it = instructions->begin(); it != instructions->end(); it++, instrCount++)
	{
		for (Functions::iterator it = functions.begin(); it != functions.end(); it++)
		{
			if (it->second == instrCount)
			{
				os << it->first << ":\n";
			}
		}
		for (Labels::iterator it = labels.begin(); it != labels.end(); it++)
		{
			if (it->second == instrCount)
			{
				os << it->first << ":\n";
			}
		}
		Instruction* instr = *it;
		instr->updateInstructionString();
		os << "\t" << instr->instructionString() << std::endl;
	}
	os.close();
}
