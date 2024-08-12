#pragma once

#include <vector>
#include <string>
class WordNDef {
public:
	std::vector<std::string> word;
	std::string type;
	std::vector<std::string> definition;

	WordNDef() {}
	WordNDef(std::vector<std::string> word, std::string type,
		std::vector<std::string> definition) {}

	~WordNDef(){}
};