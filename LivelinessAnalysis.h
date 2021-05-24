#pragma once

#include "IR.h"

class LivelinessAnalysis 
{
public:
	LivelinessAnalysis(Instructions* instructions);
	void Do();

private:
	Instructions* m_instructions;
	bool done(const std::vector<Variables>& in_prims, const std::vector<Variables>& out_prims);
};
