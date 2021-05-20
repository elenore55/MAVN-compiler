#pragma once

#include <fstream>
#include "IR.h"

class FileWriter
{
public:
	FileWriter(std::string path);
	void writeToSFile(Instructions* instructions, Variables* variables, Labels labels, Functions functions);
private:
	std::string m_path;
};
