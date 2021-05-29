#include "SyntaxAnalysis.h"
#include "ConcreteGenerators.h"

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex) : 
	lexicalAnalysis(lex), errorFound(false), tokenIterator(lexicalAnalysis.getTokenList().begin()), 
	m_instructionCount(1), m_lineCount(1), m_isFunction(false), m_variables(new Variables()),
	m_varCount(-1), m_variableForming(false), m_currentVariable(nullptr)
{}

bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();

	//TO DO: Call function for the starting non-terminal symbol
	Q();

	return !errorFound;	
}

Labels SyntaxAnalysis::getLabels()
{
	return m_lablesMap;
}

Functions SyntaxAnalysis::getFunctions()
{
	return m_functionsMap;
}

Variables* SyntaxAnalysis::getVariables()
{
	return m_variables;
}

void SyntaxAnalysis::printSyntaxError(Token token)
{
	throw std::runtime_error("Syntax error! Token: " + token.getValue() + " unexpected");
}

void SyntaxAnalysis::eat(TokenType t)
{
	if (!errorFound)
	{
		if (currentToken.getType() == t)
		{	
			switch (currentToken.getType())
			{
			case T_FUNC:
				m_isFunction = true;
				break;
			case T_ID:
				if (m_isFunction)
				{
					if (m_functionsMap.find(currentToken.getValue()) != m_functionsMap.end())
					{
						throw std::runtime_error("Function " + currentToken.getValue() + " already defined");
					}
					m_functionsMap[currentToken.getValue()] = m_instructionCount;
					m_isFunction = false;
				}
				else
				{
					if (getNextToken().getType() != T_COL)
					{
						if (m_lablesMap.find(currentToken.getValue()) == m_lablesMap.end())
						{
							throw std::runtime_error("ERROR\nNon-existing label: " + currentToken.getValue() + " on line " + std::to_string(m_lineCount));
						}
					}
					else
					{
						if (m_lablesMap.find(currentToken.getValue()) != m_lablesMap.end())
						{
							throw std::runtime_error("Label " + currentToken.getValue() + " already defined");
						}
						m_lablesMap[currentToken.getValue()] = m_instructionCount;
					}
					*tokenIterator--;
				}
				break;
			case T_MEM:
			{
				m_variableForming = true;
				m_currentVariable = new Variable();
				m_currentVariable->type() = Variable::MEM_VAR;
				break;
			}
			case T_REG:
			{
				m_variableForming = true;
				m_currentVariable = new Variable();
				m_currentVariable->type() = Variable::REG_VAR;
				break;
			}
			case T_R_ID:
			{
				if (m_variableForming)
				{
					m_currentVariable->name() = currentToken.getValue();
					m_currentVariable->pos() = ++m_varCount;
					if (m_variablesMap.find(m_currentVariable->name()) != m_variablesMap.end())
					{
						throw std::runtime_error("ERROR\nRedeclared register variable: " + currentToken.getValue() + " on line " + std::to_string(m_lineCount));
					}
					m_variables->push_back(m_currentVariable);
					m_variablesMap[m_currentVariable->name()] = m_currentVariable;
					m_variableForming = false;
				}
				else if (m_variablesMap.find(currentToken.getValue()) == m_variablesMap.end())
				{
					throw std::runtime_error("ERROR\nUndeclared register variable: " + currentToken.getValue() + " on line " + std::to_string(m_lineCount));
				}
				break;
			}
			case T_M_ID:
			{
				if (m_variableForming)
				{
					m_currentVariable->name() = currentToken.getValue();
					if (m_variablesMap.find(m_currentVariable->name()) != m_variablesMap.end())
					{
						throw std::runtime_error("ERROR\nRedeclared memory variable: " + currentToken.getValue() + " on line " + std::to_string(m_lineCount));
					}
				}
				else if (m_variablesMap.find(currentToken.getValue()) == m_variablesMap.end())
					throw std::runtime_error("ERROR\nUndeclared memory variable: " + currentToken.getValue() + " on line " + std::to_string(m_lineCount));
				break;
			}
			case T_NUM:
			{
				if (m_variableForming)
				{
					m_currentVariable->value() = std::stoi(currentToken.getValue());
					m_variables->push_back(m_currentVariable);
					m_variablesMap[m_currentVariable->name()] = m_currentVariable;
					m_variableForming = false;
				}
				break;
			}
			case T_ADD: case T_ADDI: case T_SUB: case T_LA: case T_LI: case T_LW: case T_SW: 
			case T_BLTZ: case T_B: case T_NOP: case T_SEQ: case T_ABS: case T_NOR:
				m_instructionCount++;
				break;
			case T_SEMI_COL:
				m_lineCount++;
				break;
			default:
				break;
			}
			if (t != T_END_OF_FILE)
				currentToken = getNextToken();
		}
		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
		}
	}
}

Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw std::runtime_error("End of input file reached");
	return *tokenIterator++;
}

void SyntaxAnalysis::Q()
{
	S();
	eat(T_SEMI_COL);
	L();
}

void SyntaxAnalysis::S()
{
	if (currentToken.getType() == T_MEM)
	{
		eat(T_MEM);
		eat(T_M_ID);
		eat(T_NUM);
	}
	else if (currentToken.getType() == T_REG)
	{
		eat(T_REG);
		eat(T_R_ID);
	}
	else if (currentToken.getType() == T_FUNC)
	{
		eat(T_FUNC);
		eat(T_ID);
	}
	else if (currentToken.getType() == T_ID)
	{
		eat(T_ID);
		eat(T_COL);
		E();
	}
	else
	{
		E();
	}
}

void SyntaxAnalysis::L()
{
	if (currentToken.getType() == T_END_OF_FILE)
	{
		eat(T_END_OF_FILE);
	}
	else
	{
		Q();
	}
}

void SyntaxAnalysis::E()
{
	if (currentToken.getType() == T_ADD)
	{
		eat(T_ADD);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
	}
	else if (currentToken.getType() == T_ADDI)
	{
		eat(T_ADDI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
	}
	else if (currentToken.getType() == T_SUB)
	{
		eat(T_SUB);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
	}
	else if (currentToken.getType() == T_LA)
	{
		eat(T_LA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_M_ID);
	}
	else if (currentToken.getType() == T_LW)
	{
		eat(T_LW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
	}
	else if (currentToken.getType() == T_LI)
	{
		eat(T_LI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
	}
	else if (currentToken.getType() == T_SW)
	{
		eat(T_SW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
	}
	else if (currentToken.getType() == T_B)
	{
		eat(T_B);
		eat(T_ID);
	}
	else if (currentToken.getType() == T_BLTZ)
	{
		eat(T_BLTZ);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_ID);
	}
	else if (currentToken.getType() == T_ABS)
	{
		eat(T_ABS);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
	}
	else if (currentToken.getType() == T_NOR)
	{
		eat(T_NOR);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
	}
	else if (currentToken.getType() == T_SEQ)
	{
		eat(T_SEQ);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
	}
	else
	{
		eat(T_NOP);
	}
}
