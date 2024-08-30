#pragma once
#include <fstream>
#include <wx/wx.h>
#include <string>
#include <uni_algo/all.h>
#include <vector>
#include <xutility>
#include <stack>
#include <chrono>
#include <random>
#include <cstdlib>
#include "red-black-tree.h"

using std::vector;
using std::pair;
class TST
{
public:
	struct TreeNode
	{
		char32_t val = 0;
		TreeNode* left = 0, * mid = 0, * right = 0;
		bool eow = false;
		std::string defi;
	};


	TreeNode* root = 0;
	void insert(std::string key, std::string value)
	{
		if (key.empty() || !una::is_valid_utf8(key) || !una::is_valid_utf8(value))
			return; 
		key = una::cases::to_lowercase_utf8(key); 
		std::u32string str = una::utf8to32u(key);
		
		std::u32string::iterator iter = str.begin(); 
		
		TreeNode* curr = root;
		TreeNode* prev = 0; 
		bool go_mid = true; 
		while (iter != str.end())
		{
			if (!curr)
			{
				curr = new TreeNode(); 
				curr->val = *iter; 
				if (prev)
				{
					if (!go_mid)
					{
						if (prev->val < *iter) prev->right = curr;
						else if (prev->val > *iter - 1) prev->left = curr;
					}
					else prev->mid = curr; 
				}
				else root = curr; 
			}
			prev = curr; 
			if (*iter == curr->val)
			{
				curr = curr->mid;
				go_mid = true;
				++iter;
			}
			else if (*iter < curr->val)
			{
				go_mid = false;
				curr = curr->left;
			}
			else
			{
				go_mid = false;
				curr = curr->right;
			}
			
		}
		prev->eow = true; 
		prev->defi += value;
		return; 
	}
	vector<wxString> searchByPrefix(std::u32string prefix)
	{
		
		std::u32string prefix_str = (prefix); 
		std::u32string::iterator iter = prefix_str.begin(); 

		TreeNode* curr = root; 
		TreeNode* prev = nullptr; 

		while (curr && (iter != prefix_str.end()))
		{
			prev = curr; 
			if (curr!= nullptr && *iter == curr->val)
			{
				curr = curr->mid;
				++iter;
			}
			else if (*iter < curr->val) curr = curr->left;
			else curr = curr->right;
			
		}

		if (iter != prefix_str.end()) return {}; 
		vector<wxString> ans; 

		if (prev!=nullptr &&  prev->eow) 
			ans.push_back(wxString(una::utf32to16(prefix))); 
		traverse(ans, prefix_str, 5, curr);
		return ans;
	}

	TreeNode* search(std::u32string word)
	{
		if (word.empty()) return 0; 
		std::u32string::iterator iter = word.begin();

		TreeNode* curr = root;
		TreeNode* prev = 0;
		while (curr && (iter != word.end()))
		{
			prev = curr;
			if (*iter == curr->val)
			{
				curr = curr->mid;
				++iter;
			}
			else if (*iter < curr->val) curr = curr->left;
			else curr = curr->right;
		}
		if (iter != word.end()) return 0; 
		return (prev -> eow) ? prev : 0; 
	}
 	void clear(TreeNode*& root)
	{
		if (!root) return;
		clear(root->left); clear(root->mid); clear(root->right);
		delete(root); root = 0;
		return;
	}
	
	void clear()
	{
		clear(root);
	}

	~TST()
	{
		clear(); 
		return;
	}


	pair<std::u32string, std::string> random()
	{
		std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> dist(0, 256);
		std::u32string ans;

		TreeNode* curr_root;
		if (root != nullptr)
			curr_root = root;

		TreeNode* temp_root = 0; 
		vector<TreeNode*> currChoice; 
		while (curr_root != nullptr)
		{
			temp_root = curr_root; 
			currChoice.clear();
			std::stack<TreeNode*> choice; choice.push(curr_root);
			while (!choice.empty())
			{
				for (TreeNode* curr = choice.top(); curr != 0; curr = curr->left)
				{
					choice.push(curr->left);
				}
				choice.pop();
				if (choice.empty()) break; 
				TreeNode* next = choice.top()->right; 
				currChoice.push_back(choice.top()); choice.pop(); 
				choice.push(next); 
			}

			
			TreeNode* wordChoice = currChoice[dist(rng) % currChoice.size()];
			ans += wordChoice->val; 
			curr_root = wordChoice;
			if (wordChoice->eow)
			{
				
				bool isChosen = dist(rng) % (dist(rng) % 20 + 1); 
				if ( !isChosen || !wordChoice->mid) return { ans, wordChoice->defi }; 
			}
			curr_root = curr_root->mid; 
		}
		return make_pair(ans, temp_root->defi);
		
	}
	void loadWord(std::string filename)
	{

		std::ifstream fin; fin.open(filename);
		std::string currLang; 
		if (filename == "data/ee/data.txt") currLang = "ENG/ENG";
		else if (filename == "data/ev/data.txt") currLang = "ENG/VIE";
		else if (filename == "data/ve/data.txt") currLang = "VIE/ENG";
		else if (filename == "data/emo/data.txt") currLang = "EMOTICON";
		else if (filename == "data/slang/data.txt") currLang = "SLANG"; 
		if (!fin.is_open()) return;

		if (filename == "data/ev/data.txt" || filename == "data/ve/data.txt" ) {
			std::string name; 
			std::getline(fin, name);
			std::string defi;

			while (!fin.eof())
			{
				for (std::string tempLine; !fin.eof();)
				{
					std::getline(fin, tempLine);
					if (tempLine[0] == '@')
					{
						name.erase(name.begin()); 
						while (name.back() == ' ') name.pop_back(); 
						
						if (currLang == "ENG/ENG" && removingEE.find(una::utf8to32u(name)) != removingEE.end()); 
						else if (currLang == "ENG/VIE" && removingEV.find(una::utf8to32u(name)) != removingEV.end());
						else if (currLang == "VIE/ENG" && removingVE.find(una::utf8to32u(name)) != removingVE.end());
						else if (currLang == "EMOTICON" && removingEmo.find(una::utf8to32u(name)) != removingEmo.end());
						else if (currLang == "SLANG" && removingSlang.find(una::utf8to32u(name)) != removingSlang.end());
						else 
							this->insert(name, defi);
						
						
						name = tempLine;
						defi.clear();
						break;
					}
					else
						defi += '\n' + tempLine;
				}
			}
			name.erase(name.begin());
			this->insert(name, defi);
			}
		else if (filename == "data/ee/data.txt") {
			std::string name, type, def;
			std::string line;

			while (std::getline(fin, line)) {
				size_t pos = line.find("\t(");
				if (pos != std::string::npos) {
					name = line.substr(0, pos); 
					size_t type_start = pos;
					size_t type_end = line.find(")", type_start);
					if (type_end != std::string::npos) {
						type = line.substr(type_start + 1, type_end - type_start - 1); 
						type.erase(type.begin());
						def = line.substr(type_end + 1);
					}
				}
				if (currLang == "ENG/ENG" && removingEE.find(una::utf8to32u(name)) != removingEE.end());
				else if (currLang == "ENG/VIE" && removingEV.find(una::utf8to32u(name)) != removingEV.end());
				else if (currLang == "VIE/ENG" && removingVE.find(una::utf8to32u(name)) != removingVE.end());
				else if (currLang == "EMOTICON" && removingEmo.find(una::utf8to32u(name)) != removingEmo.end());
				else if (currLang == "SLANG" && removingSlang.find(una::utf8to32u(name)) != removingSlang.end());
				else this->insert(name, "\n*(" + type + ")\n-" + def);

		}
		}
		else 
		{
			std::string name, type, def;
			while (!fin.eof()) 
			{
				fin >> name >> type;
				getline(fin, def);

				def = "\n - " +  type + "\n - " + def;
				while (def[0] == ' ')
					def.erase(0, 1);

				if (currLang == "ENG/ENG" && removingEE.find(una::utf8to32u(name)) != removingEE.end());
				else if (currLang == "ENG/VIE" && removingEV.find(una::utf8to32u(name)) != removingEV.end());
				else if (currLang == "VIE/ENG" && removingVE.find(una::utf8to32u(name)) != removingVE.end());
				else if (currLang == "EMOTICON" && removingEmo.find(una::utf8to32u(name)) != removingEmo.end());
				else if (currLang == "SLANG" && removingSlang.find(una::utf8to32u(name)) != removingSlang.end());
				else this->insert(name, def);
			}
		}


		if (currLang == "ENG/ENG")
		{
			for (auto iter = addingEE.begin(); iter != addingEE.end(); ++iter)
			{
				TreeNode* node = this->search((*iter).first); 
				if (node != nullptr && !node ->defi.empty())
					node->defi = (*iter).second; 
				else
					this->insert(una::utf32to8((*iter).first), (*iter).second);
			}
		}
		else if (currLang == "ENG/VIE")
		{
			for (auto iter = addingEV.begin(); iter != addingEV.end(); ++iter)
			{
				TreeNode* node = this->search((*iter).first);
				if (node != nullptr && !(*iter).second.empty())
					node->defi = (*iter).second;
				else
					this->insert(una::utf32to8((*iter).first), (*iter).second);
			}
		}
		else if (currLang == "VIE/ENG")
		{
			for (auto iter = addingVE.begin(); iter != addingVE.end(); ++iter)
			{
				TreeNode* node = this->search((*iter).first);
				if (node != nullptr && !(*iter).second.empty())
					node->defi = (*iter).second;
				else
					this->insert(una::utf32to8((*iter).first), (*iter).second);
			}
		}
		else if (currLang == "SLANG")
		{
			for (auto iter = addingSlang.begin(); iter != addingSlang.end(); ++iter)
			{
				TreeNode* node = this->search((*iter).first);
				if (node != nullptr && !(*iter).second.empty())
					node->defi = (*iter).second;
				else
					this->insert(una::utf32to8((*iter).first), (*iter).second);
			}
		}
		else if (currLang == "EMOTICON")
		{
			for (auto iter = addingSlang.begin(); iter != addingSlang.end(); ++iter)
			{
				TreeNode* node = this->search((*iter).first);
				if(node != nullptr && !(*iter).second.empty())
					node->defi = (*iter).second;
				else
					this->insert(una::utf32to8((*iter).first), (*iter).second);
			}
		}

		fin.close();
	}
	
	bool isLoaded() {
		if (root == nullptr)
			return false;
		return true;
	}

	TreeNode* deleteHelper(TreeNode* node, std::u32string& word, int depth) {
		if (!node) return nullptr;

		char32_t currentChar = word[depth];

		if (currentChar < node->val) {
			node->left = deleteHelper(node->left, word, depth);
		}
		else if (currentChar > node->val) {
			node->right = deleteHelper(node->right, word, depth);
		}
		else {
		
			if (depth + 1 == word.size()) {
				
				if (node->eow) {
					node->eow = false;
				}
			}
			else {
				node->mid = deleteHelper(node->mid, word, depth + 1);
			}

		
			if (!node->eow && !node->left && !node->mid && !node->right) {
				delete node;
				node = nullptr;
			}
		}
		return node;
	}

	void delete_word(TreeNode*& root, std::u32string& word) {
		root = deleteHelper(root, word, 0);
	}

private:
	void traverse(vector<wxString>& ans, std::u32string currStr, int limit, TreeNode *currNode)
	{

		if (ans.size() >= limit || !currNode) return; 
		else
		{
			if (currNode->eow) ans.push_back(wxString(una::utf32to16(currStr + currNode -> val)));
			traverse(ans, currStr, limit, currNode->left); 
			if (currNode->mid)
				traverse(ans, currStr + currNode->val, limit, currNode->mid); 
			traverse(ans, currStr, limit, currNode->right); 
		}
	}

	
};




