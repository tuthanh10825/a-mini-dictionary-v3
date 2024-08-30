
#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <uni_algo/all.h>
#include <cassert>
#include <map>
#include <sstream>
#include "red-black-tree.h"
typedef std::basic_stringstream<char32_t> u32stringstream;

using std::vector;

class suffixArr
{
public:
	std::u32string text;
	vector<int> SA_index;
	ordered_map <int, std::u32string> mapping;
	void loadText(std::string filename)
	{
		text.clear();
		mapping.clear();
		std::ifstream fin; fin.open(filename);
 		if (!fin.is_open()) return;

		if (filename == "data/ev/data.txt" || filename == "data/ve/data.txt") 
		{
			std::u32string name; 
			while (!fin.eof())
			{
				for (std::string tempLine; !fin.eof();)
				{
					std::getline(fin, tempLine);
					if (!una::is_valid_utf8(tempLine)) assert("String error");
					std::u32string line = una::utf8to32u(tempLine); 
					if (line[0] == U'@')
					{
						name = line; 
						name.erase(name.begin());
						while (name.back() == ' ') name.pop_back();
						break;
					}
					else
					{
						if (filename == "data/ev/data.txt" &&
							((addingEV.find(name) != addingEV.end() && !(*addingEV.find(name)).second.empty()) || removingEV.find(name) != removingEV.end()))
						{
							std::cerr << "Error"; 
						}
						if (filename == "data/ve/data.txt" &&
							((addingVE.find(name) != addingVE.end() && !(*addingVE.find(name)).second.empty()) || removingVE.find(name) != removingVE.end()))
						{
							std::cerr << "Error";
						}
						else
						{
							if (line[0] == U'-')
							{
								text += (line + U"@");
								mapping[text.size() - 1] = name;
							}
						}
					}
						
				}
			}
			if (filename == "data/ev/data.txt")
			{
				for (auto iter = addingEV.begin(); iter != addingEV.end(); ++iter)
				{
					if ((*iter).second.empty()) continue; 
					std::u32string totalDefi = una::utf8to32u((*iter).second);
					u32stringstream sin(totalDefi);
					for (std::u32string ltext; std::getline(sin, ltext);)
					{
						if (ltext[0] == U'-')
						{
							text += ltext + U"@";
							mapping[text.size() - 1] = (*iter).first;
						}
					}
				}
			}
			else if (filename == "data/ve/data.txt")
			{
				for (auto iter = addingVE.begin(); iter != addingVE.end(); ++iter)
				{
					if ((*iter).second.empty()) continue;
					std::u32string totalDefi = una::utf8to32u((*iter).second);
					u32stringstream sin(totalDefi);
					for (std::u32string ltext; std::getline(sin, ltext);)
					{
						if (ltext[0] == U'-')
						{
							text += ltext + U"@";
							mapping[text.size() - 1] = (*iter).first;
						}
					}
				}
			}
		}
		else
		{
			std::u32string prevWord;
			std::u32string defiLine;
			for (std::string line; std::getline(fin, line); )
			{
				std::u32string real_line = una::utf8to32u(line);
				std::u32string word = real_line.substr(0, real_line.find(U'\t'));
				if (filename == "data/ee/data.txt" &&
					((addingEE.find(word) != addingEE.end() && !(*addingEE.find(word)).second.empty()) || removingEE.find(word) != removingEE.end()));

				if (filename == "data/emo/data.txt" &&
					((addingEmo.find(word) != addingEmo.end() && !(*addingEmo.find(word)).second.empty()) || removingEmo.find(word) != removingEmo.end()));

				if (filename == "data/slang/data.txt" &&
					((addingSlang.find(word) != addingSlang.end() && !(*addingSlang.find(word)).second.empty()) || removingSlang.find(word) != removingSlang.end()));
				
				else
				{
					real_line = real_line.substr(real_line.find(U'\t') + 1);
					real_line = real_line.substr(real_line.find(U')') + 1);
					text += real_line + U'@';
					mapping[text.size() - 1] = word;
				}
			}
			if (filename == "data/ee/data.txt")
			{
				for (auto iter = addingEE.begin(); iter != addingEE.end();++iter)
				{
					if ((*iter).second.empty()) continue;
					std::u32string totalDefi = una::utf8to32u((*iter).second);
					u32stringstream sin(totalDefi);
					for (std::u32string ltext; std::getline(sin, ltext);)
					{
						if (ltext[0] == U'-')
						{
							text += ltext + U"@";
							mapping[text.size() - 1] = (*iter).first;
						}
					}
				}
			}
			else if (filename == "data/slang/data.txt")
			{
				for (auto iter = addingSlang.begin(); iter != addingSlang.end();++iter)
				{
					if ((*iter).second.empty()) continue;
					std::u32string totalDefi = una::utf8to32u((*iter).second);
					u32stringstream sin(totalDefi);
					for(std::u32string ltext; std::getline(sin, ltext);)
					{
						if (ltext[0] == U'-')
						{
							text += ltext + U"@";
							mapping[text.size() - 1] = (*iter).first;
						}
					}
				}
			}
			else if (filename == "data/emo/data.txt")
			{
				for (auto iter = addingEmo.begin(); iter != addingEmo.end(); ++iter)
				{
					if ((*iter).second.empty()) continue;
					std::u32string totalDefi = una::utf8to32u((*iter).second);
					u32stringstream sin(totalDefi);
					for (std::u32string ltext; std::getline(sin, ltext);)
					{
						if (ltext[0] == U'-')
						{
							text += ltext + U"@";
							mapping[text.size() - 1] = (*iter).first;
						}
					}
				}
			}
		}
		text += static_cast<char32_t>(0);
		//vector <std::u32string> t; 
		/*for (auto iter = removingEE.begin(); iter != removingEE.end(); ++iter)
			t.push_back(*iter); */
		return;
	}
	void serialize(std::string lang)
	{
		std::fstream fout;
		if (lang == "ENG/ENG") fout.open("data/ee/index.bin", std::ios::binary | std::ios::out);
		else if (lang == "ENG/VIE") fout.open("data/ev/index.bin", std::ios::binary | std::ios::out);
		else if (lang == "VIE/ENG") fout.open("data/ve/index.bin", std::ios::binary | std::ios::out);
		else if (lang == "SLANG") fout.open("data/slang/index.bin", std::ios::binary | std::ios::out);
		else if (lang == "EMOTICON") fout.open("data/emo/index.bin", std::ios::binary | std::ios::out);
	
		
		fout.write((char*)SA_index.data(), SA_index.size() * sizeof(int)); 
		fout.close(); 
		return; 
	}
	void deserialize(std::string lang)
	{
		std::fstream fin;
		if (lang == "ENG/ENG") 
			fin.open("data/ee/index.bin", std::ios::binary | std::ios::in);
		else if (lang == "ENG/VIE") 
			fin.open("data/ev/index.bin", std::ios::binary | std::ios::in);
		else if (lang == "VIE/ENG") 
			fin.open("data/ve/index.bin", std::ios::binary | std::ios::in);
		else if (lang == "SLANG") 
			fin.open("data/slang/index.bin", std::ios::binary | std::ios::in);
		else if (lang == "EMOTICON") 
			fin.open("data/emo/index.bin", std::ios::binary | std::ios::in);
		
		if (!fin)
		{
			std::cerr << "wtf?";
		}
		SA_index.resize(text.size()); 
		fin.read((char*)SA_index.data(), text.size() * sizeof(int)); 
		fin.close(); 
		return; 

	}
	vector<std::u32string> findSubtring(std::u32string str, std::string type)
	{
		int k = str.size(); 
		vector<int> ans; 
		int start = 0, end = SA_index.size() - 1; 
		/*vector<std::u32string> t;
		for (auto iter = removingEE.begin(); iter != removingEE.end(); ++iter)
			t.push_back(*iter);*/
		generate_ans(start, end, str, k, ans);
		ordered_set<std::u32string> real_ans; 
		
		/*for (auto iter = removingEE.begin(); iter != removingEE.end(); ++iter)
			t.push_back(*iter);*/
		for (const int& val : ans)
		{
			if (type == "ENG/ENG" && removingEE.find(mapping[val]) == removingEE.end())
				real_ans.insert(mapping[val]);
			else if (type == "ENG/VIE" && removingEV.find(mapping[val]) == removingEV.end())
				real_ans.insert(mapping[val]);
			else if (type == "VIE/ENG" && removingVE.find(mapping[val]) == removingVE.end())
				real_ans.insert(mapping[val]);
			else if (type == "SLANG" && removingSlang.find(mapping[val]) == removingSlang.end())
				real_ans.insert(mapping[val]);
			else if (type == "EMOTICON" && removingEmo.find(mapping[val]) == removingEmo.end())
				real_ans.insert(mapping[val]); 

			
		} 
		/*for (auto iter = removingEE.begin(); iter != removingEE.end(); ++iter)
			t.push_back(*iter);*/
		/*vector<std::u32string> ans_vector; 
		for (auto iter = real_ans.begin(); iter != real_ans.end(); ++iter)
			ans_vector.push_back(*iter);  */
		return real_ans.to_vector(); 
		 
	}
private: 
	void generate_ans(int start, int end, std::u32string str, int k, vector<int> &ans)
	{
		if (start > end) return; 
		if (text.substr(SA_index[start], k) > str || text.substr(SA_index[end], k) < str) return; 
		int mid = (start + end) / 2;
		if (text.substr(SA_index[mid], k) == str)
		{
			ans.push_back(text.find(U"@", SA_index[mid]));
			generate_ans(start, mid - 1, str, k, ans); 
			generate_ans(mid + 1, end, str, k, ans);
		}
		else if (text.substr(SA_index[mid], k) > str)
			generate_ans(start, mid - 1, str, k, ans);
		else
			generate_ans(mid + 1, end, str, k, ans); 
	
	}
	public: 
	void build()
	{
		SA_index.clear();
		int n = text.size();
		SA_index.resize(n);


		std::iota(SA_index.begin(), SA_index.end(), 0);
		std::sort(SA_index.begin(), SA_index.end(), [this](int a, int b) { return text[a] < text[b];  });


		vector<int> primary_key(n); int value = 0; primary_key[SA_index[0]] = 0;
		vector<bool> mark(n, false); mark[0] = true;

		for (int i = 1; i < n; ++i)
		{
			if (text[SA_index[i]] != text[SA_index[i - 1]])
			{
				++value;
				mark[i] = true;
			}
			else mark[i] = false;
			primary_key[SA_index[i]] = value;
		}
		if (value == n - 1) return;
		vector<int> temp_SA_index;
		int k = 1;

		while (k < n)
		{
			temp_SA_index.resize(n);
			for (int i = 0; i < n; ++i)
				temp_SA_index[i] = (SA_index[i] + n - k) % n;

			//using counting/radix sort to fix this. 
			//std::stable_sort(temp_SA_index.begin(), temp_SA_index.end(), [primary_key](int a, int b) {return primary_key[a] < primary_key[b]; });

			vector <int> cou(10000, 0);
			vector <int> temp_vector(n);
			for (int count = 1; count <= n; count *= 10000)
			{
				temp_vector.resize(n);
				std::fill(cou.begin(), cou.end(), 0);
				for (int i = 0; i < n; ++i)
					++cou[primary_key[temp_SA_index[i]] / count % 10000];
				for (int i = 1; i < 10000; ++i)
					cou[i] += cou[i - 1];
				for (int i = n - 1; i >= 0; --i)
					temp_vector[--cou[primary_key[temp_SA_index[i]] / count % 10000]] = temp_SA_index[i];
				temp_SA_index = std::move(temp_vector);
			}

			SA_index = std::move(temp_SA_index);
			for (int i = 1; i < n; ++i)
			{
				if (primary_key[(SA_index[i - 1] + k) % n] != primary_key[(SA_index[i] + k) % n])
					mark[i] = true;
			}
			int nkey = 0;
			for (int i = 0; i < n; ++i)
			{
				nkey += mark[i];
				primary_key[SA_index[i]] = nkey - 1;
			}
			if (nkey == n) break;
			k *= 2;
		}
	} 
void clear()
	{
		mapping.clear(); 
		SA_index.clear(); 
		text.clear(); 
	}
};

static suffixArr EEDef;
static suffixArr EVDef;
static suffixArr VEDef;
static suffixArr SLDef;
static suffixArr EMODef;