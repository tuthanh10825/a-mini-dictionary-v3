#pragma once
#include "tst.h"
#include "suffix-array.h"
#include "red-black-tree.h"
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

#define EVINSERT "data/ev/insert.txt"
#define VEINSERT "data/ve/insert.txt"
#define EEINSERT "data/ee/insert.txt"
#define EMOINSERT "data/emo/insert.txt"
#define SLINSERT "data/slang/insert.txt"


struct word {
	std::string word;
	std::string type;
	std::string definition;
};

extern bool LIGHTMODE;

extern TST* EVtree;
extern TST* VEtree;
extern TST* EEtree;
extern TST* EMOtree;
extern TST* SLtree;

extern bool LIGHTMODE;
extern std::vector<word> dataHisto, dataFav;


extern std::vector<word> dataHisto, dataFav;
extern std::u32string deleted_word;



extern std::string& curr_type;

extern bool isRebuildEE;
extern bool isRebuildEV;
extern bool isRebuildVE;
extern bool isRebuildSlang;
extern bool isRebuildEmo;