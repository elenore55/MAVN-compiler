#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "InstructionGenerator.h"
#include "LivelinessAnalysis.h"
#include "InstructionGenerator.h"
#include "ResourceAllocation.h"
#include "Simplification.h"
#include "FileWriter.h"

using namespace std;

int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		std::string outFileName = ".\\..\\examples\\simple.s";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syntax(lex);
		bool retval = syntax.Do();
		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}
		InstructionGenerator gen(lex.getTokenList());
		Variables* vars = gen.getVariables();
		Instructions* instructions = gen.getInstructions();
		for (Instruction* ins : (*instructions))
			std::cout << ins << endl;
		livenessAnalysis(instructions);

		InterferenceGraph* ig;
		stack<Variable*>* simplificationStack;

		ig = doInterferenceGraph(instructions);
		ig->size = ig->variables->size();
		printInterferenceGraph(ig);

		simplificationStack = doSimplification(ig, __REG_NUMBER__);
		if (simplificationStack == NULL)
		{
			cout << "Spill detected!\n";
		}
		else
		{
			printSimplificationStack(simplificationStack);
			doResourceAllocation(simplificationStack, ig);
			if (checkResourceAllocation(ig))
				std::cout << "yay\n";
			else
				std::cout << "no\n";
		}

		Labels labels = gen.getLabels();
		Functions functions = gen.getFunctions();

		FileWriter writer(outFileName);
		writer.writeToSFile(instructions, vars, labels, functions);
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
