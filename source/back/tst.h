#pragma once
#include <fstream>
#include <wx/wx.h>
#include <string>
class TST
{
public:
	struct TreeNode
	{
		char val = 0;
		TreeNode* low = 0, * mid = 0, * high = 0;
		bool eow = false;
		//std::string type;
		//std::string defi;
	};

	TreeNode* root = 0;

	TreeNode* search(std::string word)
	{

		TreeNode* curr = root; std::string::iterator it = word.begin();
		while (curr)
		{
			if (*it < curr->val) curr = curr->low;
			else if (*it > curr->val) curr = curr->high;
			else
			{
				if (++it == word.end()) return (curr->eow) ? curr : 0;
				curr = curr->mid;
			}
		}
		return 0;
	}
	wxArrayString getByPrefix(std::string prefix)
	{
		if (prefix.empty()) return wxArrayString();
		TreeNode* curr = root; std::string::iterator it = prefix.begin();
		while (curr)
		{
			if (*it < curr->val) curr = curr->low;
			else if (*it > curr->val) curr = curr->high;
			else
			{
				if (++it == prefix.end()) break;
				curr = curr->mid;
			}
		}
		if (!curr) return wxArrayString();
		curr = curr->mid;
		wxArrayString ans;
		inorder_search(curr, prefix, ans);
		return ans;

	}

private:

	TreeNode* insert(TreeNode*& curr, std::string::iterator& it, const std::string& word)//, const std::string& type, const std::string defi)
	{
		if (it == word.end()) return 0;
		if (!curr) { curr = new TreeNode(); curr->val = *it; }

		if (*it < curr->val) return insert(curr->low, it, word);//, type, defi);
		else if (*it > curr->val) return insert(curr->high, it, word);//, type, defi);
		else
		{
			if (++it == word.end())
			{
				curr->eow = true; //curr->type = type; curr->defi = defi;
				return curr;
			}
			return insert(curr->mid, it, word);// , type, defi);
		}
	}
	void inorder_search(TreeNode* curr, std::string& word, wxArrayString& ans)
	{
		if (!curr) return;
		inorder_search(curr->low, word, ans);

		word += curr->val;
		if (curr->eow) ans.Add(wxString(word));


		inorder_search(curr->mid, word, ans);
		word.pop_back();
		inorder_search(curr->high, word, ans);

	}
	void clear(TreeNode*& root)
	{
		if (!root) return;
		clear(root->low); clear(root->mid); clear(root->high);
		delete(root); root = 0;
		return;
	}

	void remove(TreeNode*& curr, std::string::iterator& it, const std::string& word)
	{
		if (!curr) return;

		if (*it < curr->val) remove(curr->low, it, word);
		else if (*it > curr->val) remove(curr->high, it, word);
		else
		{

			if (++it == word.end())
			{
				curr->eow = false;
				//curr->defi = curr->type = "";
			}
			else remove(curr->mid, it, word);

			if (!curr->mid)
			{
				TreeNode* temp = curr;
				if (!curr->high && !curr->low) curr = 0;
				else if (!curr->high) curr = curr->low;
				else if (!curr->low) curr = curr->high;
				else
				{
					TreeNode* prede = curr->low;
					TreeNode* prev = 0;
					while (prede->high)
					{
						prev = prede;
						prede = prede->high;
					}
					prev->high = 0;
					prede->low = curr->low;
					prede->high = curr->high;
					curr = prede;
				}
				delete temp;
			}

		}
	}

public:

	TreeNode* insert(std::string word)//, std::string type, std::string defi)
	{
		std::string::iterator it = word.begin();
		return insert(this->root, it, word);//, type, defi);
	}
	void clear() { clear(root); }
	void remove(std::string word)
	{
		std::string::iterator it = word.begin();
		remove(root, it, word);
	}
	void loadAll(std::string filename)
	{
		std::ifstream fin;

		fin.open(filename);
		if (!fin.is_open()) assert("File not found!");
		std::string firstline; std::getline(fin, firstline);

		for (std::string name, type, def; !fin.eof(); )
		{

			std::string temp;
			std::getline(fin, temp);
			name.assign(temp.begin(), std::find(temp.begin(), temp.end(), ','));
			temp.erase(temp.begin(), std::find(temp.begin(), temp.end(), ',') + 1);
			type.assign(temp.begin(), std::find(temp.begin(), temp.end(), ','));
			temp.erase(temp.begin(), std::find(temp.begin(), temp.end(), ',') + 1);
			def = temp;
			name[0] = std::tolower(name[0]);
			insert(name);// , type, def);
		}
		return;
	}
	~TST()
	{
		clear();
		return;
	}
};


