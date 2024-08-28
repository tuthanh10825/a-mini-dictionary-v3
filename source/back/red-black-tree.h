#pragma once

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

#include <cassert>
#include <vector>
#include <xutility>
#include <fstream>
#include <uni_algo/all.h>
using namespace std; 
template<typename T>
class ordered_set
{
private:
	struct TreeNode
	{
		T val;
		TreeNode* left;
		TreeNode* right;
		TreeNode* p;
		bool color = 0;  // 0 for black, 1 for right

		TreeNode() : val(T()), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(T x) : val(x), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), p(nullptr) {}
		TreeNode(T x, TreeNode* parent) : val(x), p(parent) {}
		TreeNode(T x, TreeNode* left, TreeNode* right, TreeNode* parent) : val(x), left(left), right(right), p(parent) {}

	};

	//global constant variable
	
	bool red = 1, black = 0;
	//querying operator, the same as bst
	inline static TreeNode* const nil = new TreeNode();
	TreeNode* root = nil;

	TreeNode* search(T key)
	{
		TreeNode* curr = root;
		while (curr != nil)
		{
			if (curr->val > key) curr = curr->left;
			else if (curr->val < key) curr = curr->right;
			else return curr;
		}
		return curr;
	}
	TreeNode* maximum()
	{
		if (root == nil) return nil;
		TreeNode* ans = root;
		while (ans->right != nil) ans = ans->right;
		return ans;
	}
	TreeNode* minimum()
	{

		if (root == nil) return root;
		TreeNode* ans = root;
		while (ans->left != nil) ans = ans->left;
		return ans;
	}
	TreeNode* successror(TreeNode*& node)
	{
		if (node->right != nil)
		{
			TreeNode* ans = node->right;
			while (ans->left != nil) ans = ans->left;
			return ans;
		}
		TreeNode* ans = node;
		while (ans->p != nil && ans->p->right == ans) ans = ans->p;
		return ans->p;
	}
	TreeNode* predecessror(TreeNode*& node)
	{
		if (node->left != nil)
		{
			TreeNode* ans = node->left;
			while (ans->right != nil) ans = ans->right;
			return ans;
		}
		TreeNode* curr = node;
		while (curr->p != nil && curr->p->left == curr) curr = curr->p;
		return curr->p;
	}
public:
	
	bool remove(T val)
	{
		TreeNode* z = search(val);
		if (z == nil) return false;
		TreeNode* y = z;
		TreeNode* x = 0;
		bool y_origin_color = y->color;
		if (z->left == nil)
		{
			x = z->right;
			transplant(root, z, z->right);
		}
		else if (z->right == nil)
		{
			x = z->left;
			transplant(root, z, z->left);

		}
		else
		{
			//y = minimum(z->right);
			y = z->right;
			while (y->left != nil) y = y->left;

			y_origin_color = y->color;
			x = y->right;
			if (y != z->right)
			{
				transplant(root, y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			else
				x->p = y;
			transplant(root, z, y);
			y->left = z->left; y->left->p = y;
			y->color = z->color;

		}
		if (y_origin_color == black)
			remove_fixup(root, x);
		return true;

	}
	void insert(T val)
	{
		TreeNode* prev = nil;
		TreeNode* curr = root;
		while (curr != nil && curr->val != val)
		{
			prev = curr;
			if (val > curr->val) curr = curr->right;
			else if (val < curr->val) curr = curr->left;
		}
		if (curr != nil) return;
		else
		{
			TreeNode* add = new TreeNode(val, nil, nil, prev);
			add->color = 1;

			if (prev != nil)
			{
				if (val > prev->val) prev->right = add;
				else if (val < prev->val) prev->left = add;
			}
			else
			{
				root = add;
			}
			insert_fixup(root, add);
		}
	}
	vector<T> to_vector()
	{
		vector<T> ans; 
		std::stack<TreeNode*> st; 
		st.push(root); 
		while (!st.empty())
		{
			for (TreeNode* curr = st.top(); curr != nil; curr = curr->left) st.push(curr->left); 
			st.pop();
			if (st.empty()) break; 
			TreeNode* curr = st.top(); st.pop(); 
			ans.push_back(curr->val); 
			st.push(curr->right); 
		}
		return std::move(ans); 
	}
	bool clear()
	{ 
		if (root == nil) return false; 
		clear(root); 
		return true; 
	}
	
	//modifying operations
private:
	void clear(TreeNode*& curr)
	{
		if (curr == nil) return; 
		clear(curr->left); 
		clear(curr->right); 
		delete curr; curr = nil; 
	}
	void left_rotate(TreeNode* curr, TreeNode*& root)
	{
		if (curr == nil || curr->right == nil) return;
		else
		{
			TreeNode* z = curr->right->left;
			TreeNode* new_root = curr->right;
			TreeNode* parent = curr->p;
			if (parent != nil)
			{
				if (parent->left == curr) parent->left = new_root;
				else parent->right = new_root;
			}
			curr->right = z;
			if (z != nil) z->p = curr;

			new_root->left = curr;
			curr->p = new_root;

			curr = new_root;
			curr->p = parent;
			if (parent == nil) root = curr;
			return;
		}
	}
	void right_rotate(TreeNode* curr, TreeNode*& root)
	{

		if (curr == nil || curr->left == nil) return;
		else
		{

			TreeNode* z = curr->left->right;
			TreeNode* new_root = curr->left;
			TreeNode* parent = curr->p;
			if (parent != nil)
			{
				if (parent->left == curr) parent->left = new_root;
				else parent->right = new_root;
			}

			curr->left = z;
			if (z != nil) z->p = curr;


			new_root->right = curr;
			curr->p = new_root;

			curr = new_root;
			curr->p = parent;

			if (parent == nil) root = curr;
			return;
		}
	}
	void insert_fixup(TreeNode*& root, TreeNode*& z)
	{
		while (z->p->color == 1)
		{
			if (z->p == z->p->p->left)
			{

				TreeNode* uncle = z->p->p->right;
				if (uncle->color == red)
				{
					z->p->color = uncle->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else if (uncle->color == black)
				{
					if (z == z->p->right)
					{
						z = z->p;
						left_rotate(z, root);
					}
					z->p->color = black;
					z->p->p->color = red;
					right_rotate(z->p->p, root);
				}
			}
			else if (z->p == z->p->p->right)
			{
				TreeNode* uncle = z->p->p->left;
				if (uncle->color == red)
				{
					z->p->color = uncle->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else if (uncle->color == black)
				{
					if (z == z->p->left)
					{
						z = z->p;
						right_rotate(z, root);
					}
					z->p->color = black;
					z->p->p->color = red;
					left_rotate(z->p->p, root);
				}
			}

		}
		root->color = black;
		return;
	}







	// code got from the book; read again and try to imple by own self. 

	void transplant(TreeNode*& root, TreeNode* u, TreeNode* v)
	{
		if (u->p == nil)	root = v;
		else if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
		v->p = u->p;
	}




	void remove_fixup(TreeNode*& root, TreeNode* x)
	{
		while (x != root && x->color == black)
		{
			if (x == x->p->left)
			{
				TreeNode* w = x->p->right;
				if (w->color == red)
				{
					w->color = black;
					x->p->color = red;
					left_rotate(x->p, root);
					w = x->p->right;
				}
				if (w->left->color == black && w->right->color == red)
				{
					w->color = red;
					x = x->p;
				}
				else
				{
					if (w->right->color == black)
					{
						w->left->color = black;
						w->color = red;
						right_rotate(w, root);
						w = x->p->right;
					}
					w->color = x->p->color;
					x->p->color = black;
					w->right->color = black;
					left_rotate(x->p, root);
					x = root;
				}
			}
			else
			{

				TreeNode* w = x->p->left;
				if (w->color == red)
				{
					w->color = black;
					x->p->color = red;
					right_rotate(x->p, root);
					w = x->p->left;
				}
				if (w->left->color == black && w->right->color == red)
				{
					w->color = red;
					x = x->p;
				}
				else
				{
					if (w->left->color == black)
					{
						w->right->color = black;
						w->color = red;
						left_rotate(w, root);
						w = x->p->left;
					}
					w->color = x->p->color;
					x->p->color = black;
					w->left->color = black;
					right_rotate(x->p, root);
					x = root;
				}
			}
		}
		return;
	}
public:
	class iterator
	{
		TreeNode* curr;
	public:
		iterator(TreeNode* node) : curr(node) {}
		iterator& operator++()
		{
			if (curr == nil) assert("Incrementing the after-the-end element.");
			if (curr->right != nil)
			{
				TreeNode* ans = curr->right;
				while (ans->left != nil) ans = ans->left;
				curr = ans;
			}
			else
			{
				TreeNode* ans = curr;
				while (ans->p != nil && ans->p->right == ans) ans = ans->p;
				curr = ans->p;
			}
			return *this;
		}
		iterator& operator--()
		{
			TreeNode* begin = root;
			while (begin != nil && begin->left != nil) begin = begin->left;

			if (curr == begin) assert("Decrementing the first element.");
			if (curr->left != nil)
			{
				TreeNode* ans = curr->left;
				while (ans->right != nil) ans = ans->right;
				curr = ans;
			}
			else
			{
				TreeNode* ans = curr;
				while (ans->p != nil && ans->p->left == ans) ans = ans->p;
				curr = ans->p;
			}
			return *this;
		}
		bool operator != (iterator other)
		{
			return this->curr != other.curr;
		}
		bool operator == (iterator other)
		{
			return this->curr == other.curr;
		}
		T& operator *()
		{
			return curr->val;
		}
	};

	iterator begin()
	{
		TreeNode* curr = root;
		while (curr != nil && curr->left != nil) curr = curr->left;
		return iterator(curr);
	}
	iterator end()
	{
		return iterator(nil);
	}
	iterator find(T val)
	{
		return iterator(search(val));
	}
	bool remove(iterator it)
	{
		this->remove(it.curr->val);
		it.curr = nil;
		return true;
	}
};


template<typename in, typename out>
class ordered_map
{
	struct TreeNode
	{
		pair<in, out> val;
		TreeNode* left;
		TreeNode* right;
		TreeNode* p;
		bool color = 0;  // 0 for black, 1 for right

		TreeNode() : val(pair<in, out>()), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(pair<in, out> x) : val(x), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(pair<in, out> x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), p(nullptr) {}
		TreeNode(pair<in, out> x, TreeNode* parent) : val(x), p(parent) {}
		TreeNode(pair<in, out> x, TreeNode* left, TreeNode* right, TreeNode* parent) : val(x), left(left), right(right), p(parent) {}
	};
	//global constant variable
	inline static TreeNode* const nil = new TreeNode();
	bool red = 1, black = 0;
	//querying operator, the same as bst
	TreeNode* root = nil;

	TreeNode* search(in key)
	{
		TreeNode* curr = root;
		while (curr != nil)
		{
			if (curr->val.first > key) curr = curr->left;
			else if (curr->val.first < key) curr = curr->right;
			else return curr;
		}
		return curr;
	}

	void insert(in val)
	{
		TreeNode* prev = nil;
		TreeNode* curr = root;
		while (curr != nil && curr->val.first != val)
		{
			prev = curr;
			if (val > curr->val.first) curr = curr->right;
			else if (val < curr->val.first) curr = curr->left;
		}
		if (curr != nil) return;
		else
		{
			TreeNode* add = new TreeNode(std::make_pair(val, out()), nil, nil, prev);
			add->color = 1;

			if (prev != nil)
			{
				if (val > prev->val.first) prev->right = add;
				else if (val < prev->val.first) prev->left = add;
			}
			else
			{
				root = add;
			}
			insert_fixup(root, add);
		}
	}
	//modifying operations
	
	//modifying operations
private:
	void clear(TreeNode*& curr)
	{
		if (curr == nil) return;
		clear(curr->left);
		clear(curr->right);
		delete curr; curr = nil;
	}
	void left_rotate(TreeNode* curr, TreeNode*& root)
	{
		if (curr == nil || curr->right == nil) return;
		else
		{
			TreeNode* z = curr->right->left;
			TreeNode* new_root = curr->right;
			TreeNode* parent = curr->p;
			if (parent != nil)
			{
				if (parent->left == curr) parent->left = new_root;
				else parent->right = new_root;
			}
			curr->right = z;
			if (z != nil) z->p = curr;

			new_root->left = curr;
			curr->p = new_root;

			curr = new_root;
			curr->p = parent;
			if (parent == nil) root = curr;
			return;
		}
	}
	void right_rotate(TreeNode* curr, TreeNode*& root)
	{

		if (curr == nil || curr->left == nil) return;
		else
		{

			TreeNode* z = curr->left->right;
			TreeNode* new_root = curr->left;
			TreeNode* parent = curr->p;
			if (parent != nil)
			{
				if (parent->left == curr) parent->left = new_root;
				else parent->right = new_root;
			}

			curr->left = z;
			if (z != nil) z->p = curr;


			new_root->right = curr;
			curr->p = new_root;

			curr = new_root;
			curr->p = parent;

			if (parent == nil) root = curr;
			return;
		}
	}
	void insert_fixup(TreeNode*& root, TreeNode*& z)
	{
		while (z->p->color == 1)
		{
			if (z->p == z->p->p->left)
			{

				TreeNode* uncle = z->p->p->right;
				if (uncle->color == red)
				{
					z->p->color = uncle->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else if (uncle->color == black)
				{
					if (z == z->p->right)
					{
						z = z->p;
						left_rotate(z, root);
					}
					z->p->color = black;
					z->p->p->color = red;
					right_rotate(z->p->p, root);
				}
			}
			else if (z->p == z->p->p->right)
			{
				TreeNode* uncle = z->p->p->left;
				if (uncle->color == red)
				{
					z->p->color = uncle->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else if (uncle->color == black)
				{
					if (z == z->p->left)
					{
						z = z->p;
						right_rotate(z, root);
					}
					z->p->color = black;
					z->p->p->color = red;
					left_rotate(z->p->p, root);
				}
			}

		}
		root->color = black;
		return;
	}

public:
	bool clear()
	{ 
		if (root == nil) return false; 
		clear(root);
		return true; 
	}
	out& operator[] (in key)
	{
		insert(key);
		TreeNode* ans = search(key);
		return ans->val.second;
	}

	class iterator
	{
		TreeNode* curr;
	public:
		iterator(TreeNode* node) : curr(node) {}
		iterator& operator++()
		{
			if (curr == nil) assert("Incrementing the after-the-end element.");
			if (curr->right != nil)
			{
				TreeNode* ans = curr->right;
				while (ans->left != nil) ans = ans->left;
				curr = ans;
			}
			else
			{
				TreeNode* ans = curr;
				while (ans->p != nil && ans->p->right == ans) ans = ans->p;
				curr = ans->p;
			}
			return *this;
		}
		iterator& operator--()
		{
			TreeNode* begin = root;
			while (begin != nil && begin->left != nil) begin = begin->left;

			if (curr == begin) assert("Decrementing the first element.");
			if (curr->left != nil)
			{
				TreeNode* ans = curr->left;
				while (ans->right != nil) ans = ans->right;
				curr = ans;
			}
			else
			{
				TreeNode* ans = curr;
				while (ans->p != nil && ans->p->left == ans) ans = ans->p;
				curr = ans->p;
			}
			return *this;
		}
		bool operator != (iterator other)
		{
			return this->curr != other.curr;
		}
		bool operator == (iterator other)
		{
			return this->curr -= other.curr;
		}
		pair<in, out> & operator *()
		{
			return curr->val;
		}
	};

	iterator begin()
	{
		TreeNode* curr = root;
		while (curr != nil && curr->left != nil) curr = curr->left;
		return iterator(curr);
	}
	iterator end()
	{
		return iterator(nil);
	}
	iterator find(in val)
	{
		return iterator(search(val));
	}
};


extern ordered_map<std::u32string, std::string> addingEE;
extern ordered_map<std::u32string, std::string> addingEV;
extern ordered_map<std::u32string, std::string> addingVE;
extern ordered_map<std::u32string, std::string> addingSlang;
extern ordered_map<std::u32string, std::string> addingEmo;

extern ordered_set<std::u32string> removingEE;
extern ordered_set<std::u32string> removingEV;
extern ordered_set<std::u32string> removingVE;
extern ordered_set<std::u32string> removingSlang;
extern ordered_set<std::u32string> removingEmo;

static void saveRemoving()
{
	ofstream fout;
	fout.open(EEDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingEE.begin(); iter != removingEE.end();)
		{
			fout << una::utf32to8(*iter);
			if (++iter != removingEE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EVDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingEV.begin(); iter != removingEV.end();)
		{
			fout << una::utf32to8(*iter);
			if (++iter != removingEV.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(VEDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingVE.begin(); iter != removingVE.end();)
		{
			fout << una::utf32to8(*iter);
			if (++iter != removingVE.end()) fout << "\n";
		}
	}
	fout.close(); fout.open(SLDELETE);
	if (fout.is_open())
	{
		for (auto iter = removingSlang.begin(); iter != removingSlang.end();)
		{
			fout << una::utf32to8(*iter);
			if (++iter != removingSlang.end()) fout << "\n";
		}
	}
	fout.close(); fout.open(EMODELETE);
	if (fout.is_open())
	{
		for (auto iter = removingEmo.begin(); iter != removingEmo.end();)
		{
			fout << una::utf32to8(*iter);
			if (++iter != removingEmo.end()) fout << "\n";
		}
	}
	fout.close();
	return;
}


static void loadInserting()
{
	ifstream fin; fin.open(EEINSERT);
	if (fin.is_open())
	{
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
					addingEE[una::utf8to32u(name)] = defi;
					name = tempLine;
					defi.clear();
					break;
				}
				else
					defi += '\n' + tempLine;
			}
		}
		if (!name.empty())
		{
			name.erase(name.begin());
			addingEE[una::utf8to32u(name)] = defi;
		}
	}
	fin.close(); fin.open(EVINSERT);
	if (fin.is_open())
	{
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

					addingEV[una::utf8to32u(name)] = defi;
					name = tempLine;
					defi.clear();
					break;
				}
				else
					defi += '\n' + tempLine;
			}

		}
		if (!name.empty())
		{
			name.erase(name.begin());
			addingEV[una::utf8to32u(name)] = defi;
		}
	}
	fin.close(); fin.open(VEINSERT);
	if (fin.is_open())
	{
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
					addingVE[una::utf8to32u(name)] = defi;
					name = tempLine;
					defi.clear();
					break;
				}
				else
					defi += '\n' + tempLine;
			}

		}
		if (!name.empty())
		{
			name.erase(name.begin());
			addingVE[una::utf8to32u(name)] = defi;
		}
	}
	fin.close(); fin.open(SLINSERT);
	if (fin.is_open())
	{
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
					addingSlang[una::utf8to32u(name)] = defi;
					name = tempLine;
					defi.clear();
					break;
				}
				else
					defi += '\n' + tempLine;
			}

		}
		if (!name.empty())
		{
			name.erase(name.begin());
			addingSlang[una::utf8to32u(name)] = defi;
		}
	}
	fin.close(); fin.open(EMOINSERT);
	if (fin.is_open())
	{
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
					addingEmo[una::utf8to32u(name)] = defi;
					name = tempLine;
					defi.clear();
					break;
				}
				else
					defi += "\n" + tempLine;
			}

		}
		if (!name.empty())
		{
			name.erase(name.begin());
			addingEmo[una::utf8to32u(name)] = defi;
		}
	}
	return;
}
static void saveInserting()
{
	ofstream fout;
	fout.open(EEINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEE.begin(); iter != addingEE.end();)
		{	
			if ((*iter).second.empty())
			{
				++iter;
				continue;
			}
			fout << "@" << una::utf32to8((*iter).first) << (*iter).second;
			if (++iter != addingEE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EVINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEV.begin(); iter != addingEV.end();)
		{
			if ((*iter).second.empty())
			{
				++iter;
				continue;
			}
			fout << "@" << una::utf32to8((*iter).first) << (*iter).second;
			if (++iter != addingEV.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(VEINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingVE.begin(); iter != addingVE.end();)
		{
			if ((*iter).second.empty())
			{
				++iter;
				continue;
			}
			fout << "@" << una::utf32to8((*iter).first) << (*iter).second;
			if (++iter != addingVE.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(SLINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingSlang.begin(); iter != addingSlang.end();)
		{
			if ((*iter).second.empty())
			{
				++iter;
				continue;
			}
			fout << "@" << una::utf32to8((*iter).first) << (*iter).second;
			if (++iter != addingSlang.end()) fout << "\n";
		}

	}
	fout.close(); fout.open(EMOINSERT);
	if (fout.is_open())
	{
		for (auto iter = addingEmo.begin(); iter != addingEmo.end();)
		{
			if ((*iter).second.empty())
			{
				++iter;
				continue;
			}
			fout << "@" << una::utf32to8((*iter).first)<< (*iter).second;
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
	if (fin.is_open())
		for (std::string temp; getline(fin, temp); )
		{
			std::u32string real = una::utf8to32u(temp);
			removingEE.insert(real);
		}
	fin.close(); fin.open(EVDELETE);
	if (fin.is_open())
		for (std::string temp; getline(fin, temp); )
		{
			std::u32string real = una::utf8to32u(temp);
			removingEV.insert(real);
		}
	fin.close(); fin.open(VEDELETE);
	if (fin.is_open())
		for (std::string temp; getline(fin, temp); )
		{
			std::u32string real = una::utf8to32u(temp);
			removingVE.insert(real);
		}

	fin.close(); fin.open(SLDELETE);
	if (fin.is_open())
		for (std::string temp; getline(fin, temp); )
		{
			std::u32string real = una::utf8to32u(temp);
			removingSlang.insert(real);
		}
	fin.close(); fin.open(EMODELETE);
	if (fin.is_open())
		for (std::string temp; getline(fin, temp); )
		{
			std::u32string real = una::utf8to32u(temp);
			removingEmo.insert(real);
		}
	fin.close();
	return;
}



