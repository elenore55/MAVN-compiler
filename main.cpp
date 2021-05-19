#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "InstructionGenerator.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\multiply.mavn";
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

	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
