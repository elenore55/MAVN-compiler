/* Autor: Milica Popović Datum: 27.05.2021. */

#pragma once

#include "IR.h"

class LivelinessAnalysis 
{
public:
	LivelinessAnalysis(Instructions* instructions);

	/**
	* Conducts liveliness analysis
	*/
	void Do();

private:

	/**
	* Pointer to the list of generated instructions
	*/
	Instructions* m_instructions;

	/**
	* Checks the condition for stopping the algorithm
	*/
	bool done(const std::vector<Variables>& in_prims, const std::vector<Variables>& out_prims);
};
