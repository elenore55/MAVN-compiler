/* Autor: Milica Popović Datum: 31.05.2021. */

#pragma once

#include <fstream>
#include "IR.h"

class FileWriter
{
public:
	FileWriter(std::string path);

	/**
	* Writes assembly code to file 
	* 
	* @param instruction - pointer to list of all instructions
	* @param variables - pointer to list of all variables
	* @param labels - collection of labels
	* @param functions - collection of functions
	*/
	void writeToSFile(Instructions* instructions, Variables* variables, Labels labels, Functions functions);
private:

	/**
	* Path of output file
	*/
	std::string m_path;
};
