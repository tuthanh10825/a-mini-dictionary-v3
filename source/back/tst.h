#pragma once
#include <fstream>
#include <wx/wx.h>
#include <string>
#include <uni_algo/all.h>
#include <vector>
using std::vector;
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
		prev->defi = value;
		return; 
	}
	vector<wxString> searchByPrefix(std::u32string prefix)
	{
		
		std::u32string prefix_str = (prefix); 
		std::u32string::iterator iter = prefix_str.begin(); 

		TreeNode* curr = root; 
		TreeNode* prev = 0; 
		while (curr && (iter != prefix_str.end()))
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
		if (iter != prefix_str.end()) return {}; 
		vector<wxString> ans; 
		if (prev->eow) ans.push_back(wxString(una::utf32to16(prefix))); 
		traverse(ans, prefix_str, 5, curr);
		return ans;
	}

	TreeNode* search(std::u32string word)
	{
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

	~TST()
	{
		clear(root);
		return;
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

static TST loadWord(std::string filename)
{
	TST ans; 

	std::ifstream fin; fin.open(filename); 
	if (!fin.is_open()) return ans; 
	//for (int i = 0; i < 3; ++i) fin.ignore();
	std::string name; std::getline(fin, name); 

	std::string defi; 
	while (!fin.eof())
	{
		for (std::string tempLine; !fin.eof();)
		{
			std::getline(fin, tempLine); 
			if (fin.eof()) break;
			if (tempLine[0] == '@')
			{
				name.erase(name.begin());
				ans.insert(name, defi);
				name = tempLine; 
				defi.clear();
				break; 
			}
			else
				defi += '\n' + tempLine; 
		} 
	}
	ans.insert(name, defi); 
	return ans; 
}


