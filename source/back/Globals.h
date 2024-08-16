#pragma once
#include "tst.h"
#define EVDATASET "data/ev/data.txt"
#define VEDATASET "data/ve/data.txt"
#define EEDATASET "data/ee/data.txt"
#define EMODATASET "data/emo/data.txt"
#define SLDATASET "data/slang/data.txt"


struct word {
	std::string word;
	std::string type;
	std::string definition;
};

extern TST* EVtree;
extern TST* VEtree;
extern TST* EEtree;
extern TST* EMOtree;
extern TST* SLtree;


extern std::vector<word> dataHisto, dataFav;