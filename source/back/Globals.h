#pragma once
#include "tst.h"
#define EVDATASET "data/ev/data.txt"
#define VEDATASET "data/ve/data.txt"
#define EEDATASET "data/ee/data.txt"
#define EMODATASET "data/emo/data.txt"
#define SLDATASET "data/slang/data.txt"

#define EVDELETE "data/ev/delete.txt"
#define VEDELETE "data/ve/delete.txt"
#define EEDELETE "data/ee/delete.txt"
#define EMODELETE "data/emo/delete.txt"
#define SLDELETE "data/slang/delete.txt"


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
extern std::u32string deleted_word;