
#include <fstream>
#include <uni_algo/all.h>
#include "red-black-tree.h"
#include "Globals.h"
using namespace std; 
static void loadInserting()
{
	ifstream fin; fin.open(EVINSERT); 
	if (fin.is_open())
	{
		
	}
}
static void saveInserting()
{
	ofstream fout;
	fout.open(EEINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEE.begin(); iter != addingEE.end();)
		{
			fout << *iter.first << "\n" << *iter.second; 
			if (++iter != removingEE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EVINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEV.begin(); iter != addingEV.end();)
		{
			fout << *iter.first << "\n" << *iter.second;
			if (++iter != addingEV.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(VEINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingVE.begin(); iter != addingVE.end();)
		{
			fout << *iter.first << "\n" << *iter.second;
			if (++iter != addingVE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(SLINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingSlang.begin(); iter != addingSlang.end();)
		{
			fout << *iter.first << "\n" << *iter.second;
			if (++iter != addingSlang.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EMOINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEmo.begin(); iter != addingEmo.end();)
		{
			fout << *iter.first << "\n" << *iter.second;
			if (++iter != addingEmo.end()) fout << "\n";
		}

	}
	fout.close();
	return;
}






static void loadRemoving()
{
	ifstream fin; 
	fin.open(EEDELETE); 
	if(fin.is_open())
		for (std::string temp; getline(temp, fin); )
		{
			std::u32string real = una::utf8to32(temp);
			removingEE.insert(real); 
		}
	fin.close(); fin.open(EVDELETE); 
	if (fin.is_open())
		for (std::string temp; getline(temp, fin); )
		{
			std::u32string real = una::utf8to32(temp);
			removingEV.insert(real);
		}
	fin.close(); fin.open(VEDELETE);
	if (fin.is_open())
		for (std::string temp; getline(temp, fin); )
		{
			std::u32string real = una::utf8to32(temp);
			removingVE.insert(real);
		}

	fin.close(); fin.open(SLDELETE);
	if (fin.is_open())
		for (std::string temp; getline(temp, fin); )
		{
			std::u32string real = una::utf8to32(temp);
			removingSlang.insert(real);
		}
	fin.close(); fin.open(EMODELETE);
	if (fin.is_open())
		for (std::string temp; getline(temp, fin); )
		{
			std::u32string real = una::utf8to32(temp);
			removingEmo.insert(real);
		}
	fin.close(); 
	return; 
}
static void saveRemoving()
{
	ofstream fout; 
	fout.open(EEDELETE); 
	if (fout.is_open())
	{
		for (auto iter = removingEE.begin(); iter != removingEE.end();)
		{
			fout << *iter;
			if (++iter != removingEE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EVDELETE); 
	if (fout.is_open())
	{
		for (auto iter = removingEV.begin(); iter != removingEV.end();)
		{
			fout << *iter;
			if (++iter != removingEV.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(VEDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingVE.begin(); iter != removingVE.end();)
		{
			fout << *iter;
			if (++iter != removingVE.end()) fout << "\n";
		}
	}
	fout.close(); fout.open(SLDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingSlang.begin(); iter != removingSlang.end();)
		{
			fout << *iter;
			if (++iter != removingSlang.end()) fout << "\n";
		}
	}
	fout.close(); fout.open(EMODELETE); 
	if (fout.is_open())
	{
		for (auto iter = removingEmo.begin(); iter != removingEmo.end();)
		{
			fout << *iter;
			if (++iter != removingEmo.end()) fout << "\n";
		}
	}
	fout.close(); 
	return; 
}