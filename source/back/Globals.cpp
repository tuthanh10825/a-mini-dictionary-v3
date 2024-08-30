#include "globals.h"


TST* EVtree = new TST();
TST* VEtree = new TST();
TST* EEtree = new TST();
TST* EMOtree = new TST();
TST* SLtree = new TST();
 
std::u32string deleted_word;


bool LIGHTMODE = true; 
std::vector<word> dataHisto, dataFav;

bool isRebuildEE = 0; 
bool isRebuildEV = 0; 
bool isRebuildVE = 0; 
bool isRebuildEmo = 0; 
bool isRebuildSlang = 0; 

ordered_map<std::u32string, std::string> addingEE = ordered_map<std::u32string, std::string>();
ordered_map<std::u32string, std::string> addingEV = ordered_map<std::u32string, std::string>();
ordered_map<std::u32string, std::string> addingVE = ordered_map<std::u32string, std::string>();
ordered_map<std::u32string, std::string> addingSlang = ordered_map<std::u32string, std::string>();
ordered_map<std::u32string, std::string> addingEmo = ordered_map<std::u32string, std::string>();

ordered_set<std::u32string> removingEE = ordered_set<std::u32string>();
ordered_set<std::u32string> removingEV = ordered_set<std::u32string>();
ordered_set<std::u32string> removingVE = ordered_set<std::u32string>();
ordered_set<std::u32string> removingSlang = ordered_set<std::u32string>();
ordered_set<std::u32string> removingEmo = ordered_set<std::u32string>();
