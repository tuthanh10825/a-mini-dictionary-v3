
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
#include "red-black-tree.h"


using std::vector;

class suffixArr
{
public:
	std::u32string text;
	vector<int> SA_index;
	ordered_map <int, std::u32string> mapping;
	void loadFile(std::string filename)
	{
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
					if (fin.eof()) break;
					if (!una::is_valid_utf8(tempLine)) assert("String error");

					std::u32string line = una::utf8to32u(tempLine); 
					if (line[0] == '@')
					{

						
						name = line; 
						name.erase(name.begin());
						while (name.back() == ' ') name.pop_back();
						break;
					}
					else
					{
						
						if (line[0] == '-') text += (line + U"@");
						mapping[text.size() - 1] = name; 
					}
						
				}
			}
			
		}
		text += static_cast<char32_t>(0);
		this->build(); 
	}
	vector<std::u32string> findSubtring(std::u32string str, std::string type)
	{
		int k = str.size(); 
		vector<int> ans; 
		int start = 0, end = SA_index.size() - 1; 
		generate_ans(start, end, str, k, ans);
		ordered_set<std::u32string> real_ans; 
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
			else if (type == "EMOTICON" && removingEmo.find(mapping[val]) == removingSlang.end())
				real_ans.insert(mapping[val]); 
		}

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
	void build()
	{
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
public: 
	~suffixArr()
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