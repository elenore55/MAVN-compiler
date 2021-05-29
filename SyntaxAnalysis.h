#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

class SyntaxAnalysis 
{
public:
	SyntaxAnalysis(LexicalAnalysis& lex);
	bool Do();
	Labels getLabels();
	Functions getFunctions();
	Variables* getVariables();
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

	void Q();

	void S();

	void L();

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

	int m_instructionCount;
	int m_lineCount;
	Labels m_lablesMap;
	Functions m_functionsMap;
	bool m_isFunction;
	Variables* m_variables;
	int m_varCount = -1;
	std::map<std::string, Variable*> m_variablesMap;
	bool m_variableForming;
	Variable* m_currentVariable;
};