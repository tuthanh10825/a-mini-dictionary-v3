#pragma once
#include <cassert>
#include <vector>
#include <xutility>
using std::pair; 
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
	inline static TreeNode* const nil = new TreeNode();
	bool red = 1, black = 0;
	//querying operator, the same as bst
	inline static TreeNode* root = nil;

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
	void clear() { clear(root); }
	~ordered_set()
	{
		clear(); 
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
			return this->curr -= other.curr;
		}
		T& operator *()
		{
			return curr->val;
		}
	};

	iterator begin()
	{
		if (root == nil) assert("Empty set can not have element. ");
		TreeNode* curr = root;
		while (curr->left != nil) curr = curr->left;
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
	inline static TreeNode* root = nil;

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
	void clear() { clear(root);  }
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
		if (root == nil) assert("Empty set can not have element. ");
		TreeNode* curr = root;
		while (curr->left != nil) curr = curr->left;
		return iterator(curr);
	}
	iterator end()
	{
		return iterator(nil);
	}
	
};
static void loadInserting(); 
static void loadRemoving(); 

static void saveInserting(); 
static void saveRemoving(); 
