/* Autor: Milica Popović Datum: 31.05.2021. */

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
		std::string fileName = ".\\..\\examples\\example1.mavn";
		std::string outFileName = ".\\..\\examples\\example1.s";
		std::string igFileName = ".\\..\\examples\\example1_ig.txt";

		
		// Lexical Analysis
		
		LexicalAnalysis lex;
		lex.readInputFile(fileName);
		lex.initialize();
		lex.Do();
		cout << "Lexical analysis finished successfully!" << endl;
		lex.printTokens();

		
		// Syntax Analysis
		
		SyntaxAnalysis syntaxAnalysis(lex);
		syntaxAnalysis.Do();
		cout << "Syntax analysis finished successfully!" << endl;

		
		// Instruction Generation
	
		Labels labels = syntaxAnalysis.getLabels();
		Functions functions = syntaxAnalysis.getFunctions();
		Variables* vars = syntaxAnalysis.getVariables();
		InstructionGenerator gen(lex.getTokenList(), labels, functions, vars);
		Instructions* instructions = gen.getInstructions();
		/*for (Instruction* ins : (*instructions))
		{
			std::cout << ins << endl;
		}*/

		
		// Liveliness Analysis
		
		LivelinessAnalysis livelinessAnalysis(instructions);
		livelinessAnalysis.Do();
		for (Instruction* ins : (*instructions))
		{
			std::cout << ins << endl;
		}
		
		// Interference Graph
		
		InterferenceGraph* ig;
		ig = doInterferenceGraph(instructions);
		testInterferenceGraph(igFileName, ig);
		ig->size = ig->variables->size();
		std::cout << "Interference graph successfully formed!\n\n";
		printInterferenceGraph(ig);

		
		// Simplification Stack
		 
		stack<Variable*>* simplificationStack;
		simplificationStack = doSimplification(ig, __REG_NUMBER__);
		printSimplificationStack(simplificationStack);


		// Resource Analysis

		ResourceAllocation resourceAllocation(simplificationStack, ig);
		resourceAllocation.Do();
		resourceAllocation.check();
		std::cout << "Resource Allocation successful!\n";
		
		
		// Generating Out File
		
		FileWriter writer(outFileName);
		writer.writeToSFile(instructions, vars, labels, functions);
		std::cout << "File generated!\n";

		freeInterferenceGraph(ig);
		syntaxAnalysis.freeVariables();
		gen.freeInstructions();
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
