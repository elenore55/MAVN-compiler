/* Autor: Milica Popović Datum: 30.05.2021. */

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
		std::string fileName = ".\\..\\examples\\multiply.mavn";
		std::string outFileName = ".\\..\\examples\\multiply.s";
		//std::string igFileName = ".\\..\\examples\\multiply_ig.txt";

		/**
		* Lexical Analysis.
		*/
		LexicalAnalysis lex;
		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");
		lex.initialize();
		if (!lex.Do())
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}
		cout << "Lexical analysis finished successfully!" << endl;
		lex.printTokens();

		/**
		* Syntax Analysis.
		*/
		SyntaxAnalysis syntaxAnalysis(lex);
		if (!syntaxAnalysis.Do())
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}
		cout << "Syntax analysis finished successfully!" << endl;

		/**
		* Instruction Generation.
		*/
		Labels labels = syntaxAnalysis.getLabels();
		Functions functions = syntaxAnalysis.getFunctions();
		Variables* vars = syntaxAnalysis.getVariables();
		InstructionGenerator gen(lex.getTokenList(), labels, functions, vars);
		Instructions* instructions = gen.getInstructions();
		for (Instruction* ins : (*instructions))
		{
			std::cout << ins << endl;
		}

		/**
		* Liveliness Analysis.
		*/
		LivelinessAnalysis livelinessAnalysis(instructions);
		livelinessAnalysis.Do();

		/**
		* Interference Graph.
		*/
		InterferenceGraph* ig;
		ig = doInterferenceGraph(instructions);
		//testInterferenceGraph(igFileName, ig);
		ig->size = ig->variables->size();
		std::cout << "Interference graph successfully formed\n\n";
		printInterferenceGraph(ig);

		/**
		* Simplification Stack.
		*/
		stack<Variable*>* simplificationStack;
		simplificationStack = doSimplification(ig, __REG_NUMBER__);
		if (simplificationStack == NULL)
		{
			throw runtime_error("Spill detected!");
		}
		printSimplificationStack(simplificationStack);

		/**
		* Resource Analysis.
		*/
		ResourceAllocation resourceAllocation(simplificationStack, ig);
		resourceAllocation.Do();
		resourceAllocation.check();
		std::cout << "Resource Allocation successful!\n";
		
		/**
		* Generating Out File.
		*/
		FileWriter writer(outFileName);
		writer.writeToSFile(instructions, vars, labels, functions);

		freeInterferenceGraph(ig);
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
