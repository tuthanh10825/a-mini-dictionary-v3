#pragma once
#include "tst.h"
#include "suffix-array.h"

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

static suffixArr EEDef; 
static suffixArr EVDef; 
static suffixArr VEDef;
static suffixArr SLDef; 
static suffixArr EMODef; 

static ordered_map<std::u32string, std::string> addingEE; 
static ordered_map<std::u32string, std::string> addingEV; 
static ordered_map<std::u32string, std::string> addingVE;
static ordered_map<std::u32string, std::string> addingSlang;
static ordered_map<std::u32string, std::string> addingEmo;

static ordered_set<std::u32string> removingEE; 
static ordered_set<std::u32string> removingEV; 
static ordered_set<std::u32string> removingVE; 
static ordered_set<std::u32string> removingSlang; 
static ordered_set<std::u32string> removingEmo; 

extern std::string& curr_type;
