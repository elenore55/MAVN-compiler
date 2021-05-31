/* Autor: Milica Popović Datum: 30.05.2021. */

#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

class SyntaxAnalysis 
{
public:
	SyntaxAnalysis(LexicalAnalysis& lex);

	/**
	* Conducts syntax analysis
	*/
	bool Do();

	/**
	* @return collection of labels
	*/
	Labels getLabels();

	/**
	* @return collection of functions
	*/
	Functions getFunctions();

	/**
	* @return collection of variables
	*/
	Variables* getVariables();

	/**
	* Deallocates memory allocated for variables
	*/
	void freeVariables();

private:

	/**
	* Prints the error message, and token that caused the syntax error
	*/
	void printSyntaxError(Token token);

	/**
	* Eats the current token if its type is "t"
	* otherwise reports syntax error
	*
	* param[in] - t - the expected token type
	*/
	void eat(TokenType t);

	/**
	* Returns the next token from the token list
	*/
	Token getNextToken();

	/**
	* Nonterminal Q
	*/
	void Q();

	/**
	* Nonterminal S
	*/
	void S();

	/**
	* Nonterminal S
	*/
	void L();

	/**
	* Nonterminal E
	*/
	void E();

	/**
	* Reference to lexical analysis module
	*/
	LexicalAnalysis& lexicalAnalysis;

	/**
	* Syntax error indicator
	*/
	bool errorFound;

	/**
	* Iterator to the token list which represents the output of the lexical analysis
	*/
	TokenList::iterator tokenIterator;

	/**
	* Current token that is being analyzed
	*/
	Token currentToken;

	/**
	* Current instruction ordinal
	*/
	int m_instructionCount;

	/**
	* Current line number
	*/
	int m_lineCount;

	/**
	* Current variable ordinal
	*/
	int m_varCount;

	/**
	* Map containing lable names as keys and instruction positions as values
	*/
	Labels m_lablesMap;

	/**
	* Map containing function names as keys and instruction positions as values
	*/
	Functions m_functionsMap;

	/**
	* Indicator of whether a function or a label is being detected
	*/
	bool m_isFunction;

	/**
	* List of variables
	*/
	Variables* m_variables;
	
	/**
	* Map containing variable names as keys and variables as values
	*/
	std::map<std::string, Variable*> m_variablesMap;

	/**
	* Indicator of whether a varable is being formed
	*/
	bool m_variableForming;

	/**
	* Variable that is currently being formed
	*/
	Variable* m_currentVariable;
};