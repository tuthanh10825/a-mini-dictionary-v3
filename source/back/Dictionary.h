#pragma once

#include "tst.h"
class Dictionary {
private:
	TST data;

public:
	Dictionary();
	Dictionary(std::string path);
	~Dictionary();

	bool isEmpty();


};