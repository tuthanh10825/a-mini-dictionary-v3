#include <cassert>

template <typename T>

class redBlackTree <T>
{
private:
	struct TreeNode
	{
		int val = -1;
		TreeNode* left;
		TreeNode* right;
		TreeNode* p;
		bool color = 0;  // 0 for black, 1 for right

		TreeNode() : val(-1), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr), p(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), p(nullptr) {}
		TreeNode(int x, TreeNode* parent) : val(x), p(parent) {}
		TreeNode(int x, TreeNode* left, TreeNode* right, TreeNode* parent) : val(x), left(left), right(right), p(parent) {}

	};

	//global constant variable
	TreeNode* const nil = new TreeNode();
	bool red = 1, black = 0;
	TreeNode* root = nil;

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
			transplant(z, z->right);
		}
		else if (z->right == nil)
		{
			x = z->left;
			transplant(z, z->left);

		}
		else
		{
			y = minimum(z->right);
			y_origin_color = y->color;
			x = y->right;
			if (y != z->right)
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			else
				x->p = y;
			transplant(z, y);
			y->left = z->left; y->left->p = y;
			y->color = z->color;

		}
		if (y_origin_color == black)
			remove_fixup(x);
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
			insert_fixup(add);
		}
	}
private: 
//pure accessing function. 
//querying operator, the same as bst
	TreeNode* search(T key)
	{
		if (root == nil) return root;
		if (root->val == key) return root;
		else if (root->val > key) return search(root->left, key);
		else return search(root->right, key);
	}

	TreeNode* search(T& key)
	{
		if (root == nil) return root;
		if (root->val == key) return root;
		else if (root->val > key) return search(root->left, key);
		else return search(root->right, key);
	}
	TreeNode* maximum()
	{
		if (root == nil) return root;
		TreeNode* curr = root;
		while (curr->right != nil) curr = curr->right;
		return curr;
	}
	TreeNode* minimum()
	{
		if (root == nil) return root;
		TreeNode* curr = root;
		while (curr->left != nil) curr = curr->left;
		return curr;
	}
	TreeNode* successror(TreeNode*& node)
	{
		if (node->right != nil) return minimum(node->right);
		TreeNode* ans = node;
		while (ans->p != nil && ans->p->right == ans) ans = ans->p;
		return ans->p;
	}
	TreeNode* predecessror(TreeNode*& node)
	{
		if (node->left != nil) return maximum(node->left);
		TreeNode* curr = node;
		while (curr->p != nil && curr->p->left == curr) curr = curr->p;
		return curr->p;
	}

//helper function. 
	void left_rotate(TreeNode* curr)
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
	void right_rotate(TreeNode* curr)
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
	void insert_fixup(TreeNode*& z)
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
						left_rotate(z);
					}
					z->p->color = black;
					z->p->p->color = red;
					right_rotate(z->p->p);
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
						right_rotate(z);
					}
					z->p->color = black;
					z->p->p->color = red;
					left_rotate(z->p->p);
				}
			}

		}
		root->color = black;
		return;
	}
	
	// code got from the book; read again and try to imple by own self. 

	void transplant(TreeNode* u, TreeNode* v)
	{
		if (u->p == nil) root = v;
		else if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
		v->p = u->p;
	}



	
	void remove_fixup(TreeNode* x)
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
					left_rotate(x->p);
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
						right_rotate(w);
						w = x->p->right;
					}
					w->color = x->p->color;
					x->p->color = black;
					w->right->color = black;
					left_rotate(x->p);
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
					right_rotate(x->p);
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
						left_rotate(w);
						w = x->p->left;
					}
					w->color = x->p->color;
					x->p->color = black;
					w->left->color = black;
					right_rotate(x->p);
					x = root;
				}
			}
		}
		return;
	}
	class iterator
	{
		TreeNode* curr = nil;
		iterator(TreeNode* curr) : this->curr(curr) {}
		
	public: 
		iterator& operator++()
		{
			if (curr == nil) assert("try to increment the last element");
			TreeNode* ans = successor(curr); 
			curr = ans; 
			return &this; 
		}
		iterator operator++(decltype(*this))
		{
			if (curr == nil) assert("try to increment the last element");
			iterator old = *this; 
			TreeNode* ans = successor(curr);
			curr = ans;
			return old; 
		}
		iterator& operator--()
		{
			TreeNode* ans; 

			if (curr == nil) ans = maximum(); 
			else ans = predecessor(curr); 

			if (ans == nil) assert("try to decrement the first element");
			curr = ans;
			return &this;
		}
		iterator operator--(decltype(*this))
		{
			iterator old = *this;
			TreeNode* ans; 

			if (curr == nil) ans = maximum();
			else ans = predecessor(curr); 

			if (ans == nil) assert("try to decrement the first element");
			curr = ans;
			return old;
		}
		bool operator == (iterator it)
		{
			if (it.curr == this->curr) return true;
			else return false; 
		}

	};
public: 
	iterator begin()
	{
		return iterator(minimum()); 
	}
	iterator end()
	{
		return iterator(nil); 
	}
	iterator find(T element)
	{
		return iterator(search(elememt));
		
	}
};