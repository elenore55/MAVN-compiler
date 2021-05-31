/* Autor: Milica Popović Datum: 27.05.2021. */

#pragma once

#include <fstream>
#include "IR.h"

class FileWriter
{
public:
	FileWriter(std::string path);

	/**
	* Writes assembly code to file 
	*/
	void writeToSFile(Instructions* instructions, Variables* variables, Labels labels, Functions functions);
private:

	/**
	* Path of output file
	*/
	std::string m_path;
};
