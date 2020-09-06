#include "binary_tree.h"

// Creates an empty binary tree
binary_tree::binary_tree()
{
	tree = nullptr;
}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
	tree = new node;
	tree->data = value;
	tree->left = nullptr;
	tree->right = nullptr;
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{
	for (int i = 0; i < values.size(); i++)
		insert(values[i]);
		
}

node* node::copy(node* tree)
{
	node* copytree = nullptr;
	if (tree != NULL)
	{
		copytree = new node;
		copytree->data = tree->data;
		copytree->left = copy(tree->left);
		copytree->right = copy(tree->right);
	}
	return copytree;
	
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	if (rhs.tree == NULL)
		tree = NULL;
	else
		tree = tree->copy(rhs.tree);
}

void del(node *tree)
{
	if (tree == nullptr)
		return;
	else
	{
		del((tree)->left);
		del((tree)->right);
	}
	delete (tree);
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
	del(tree);
}


void binary_tree::insert1(node *tree, int value)
{
	if (tree != nullptr)
	{
		if (value < tree->data)
		{
			if (tree->left != nullptr)
				insert1(tree->left, value);
			else
			{
				tree->left = new node;
				tree->left->data = value;
				tree->left->right = nullptr;
				tree->left->left = nullptr;
			}
		}
		else if (value > tree->data)
		{
			if (tree->right != nullptr)
				insert1(tree->right, value);
			else
			{
				tree->right = new node;
				tree->right->data = value;
				tree->right->right = nullptr;
				tree->right->left = nullptr;
			}
		}

	}
}

// Adds a value to the tree
void binary_tree::insert(int value)
{
	if (tree == nullptr)
	{
		tree = new node;
		tree->data = value;
		tree->left = nullptr;
		tree->right = nullptr;
	}
	else
		insert1(tree, value);
}

int minVal(node *tree)
{
	if (tree->left == nullptr)
		return tree->data;
	else
		minVal(tree->left);
}


void removeStuff(node **tree, int value)
{
	if (*tree != nullptr)
	{
		if (value < (*tree)->data)
			removeStuff(&(*tree)->left, value);
		else if (value >(*tree)->data)
			removeStuff(&(*tree)->right, value);
		else
		{
			if ((*tree)->left == nullptr && (*tree)->right == nullptr)
			{
				*tree = nullptr;
				delete *tree;
			}
			else if ((*tree)->right == nullptr && (*tree)->left != nullptr)
			{
				node *temp = *tree;
				*tree = (*tree)->left;
				delete temp;
			}
			else if ((*tree)->left == nullptr && (*tree)->right != nullptr)
			{
				node *temp = *tree;
				*tree = (*tree)->right;
				delete temp;
			}
			else
			{
				int a = minVal((*tree)->right);
				(*tree)->data = a;
				removeStuff(&((*tree)->right), a);
			}
		}
	}
}

// Removes a value from the tree
void binary_tree::remove(int value)
{
	removeStuff(&tree, value);
}

bool existsin(node *tree, int value)
{
	if (tree == nullptr)
		return false;
	else
	{
		if (tree->data == value)
			return true;
		else if (value > tree->data)
			return existsin(tree->right, value);
		else
			return existsin(tree->left, value);
	}
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
	return existsin(tree, value);
}

std::string inorder1(node *tree) 
{
	if (tree != nullptr)
	{
		if (tree->left != nullptr && tree->right != nullptr)
			return inorder1(tree->left) + " " + std::to_string(tree->data) + " " + inorder1(tree->right);
		else if (tree->right == nullptr && tree->left != nullptr)
			return inorder1(tree->left) + " " + std::to_string(tree->data);
		else if (tree->left == nullptr && tree->right != nullptr)
			return std::to_string(tree->data) + " " + inorder1(tree->right);
		else if (tree->left == nullptr && tree->right == nullptr)
			return std::to_string(tree->data);
	}
	else
		return "";
}
// Prints the tree to standard out in numerical order

std::string binary_tree::inorder() const
{
	return inorder1(tree);
}

std::string preorder1(node *tree)
{
	if (tree != nullptr)
	{
		if (tree->left != nullptr && tree->right != nullptr)
			return std::to_string(tree->data) + " " + preorder1(tree->left) + " " + preorder1(tree->right);
		else if (tree->right == nullptr && tree->left != nullptr)
			return std::to_string(tree->data) + " " + preorder1(tree->left);
		else if (tree->left == nullptr && tree->right != nullptr)
			return std::to_string(tree->data) + " " + preorder1(tree->right);
		else if (tree->left == nullptr && tree->right == nullptr)
			return std::to_string(tree->data);
	}
	else
		return "";
}
// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
    return preorder1(tree);
}

std::string postorder1(node *tree)
{
	if (tree != nullptr)
	{
		if (tree->left != nullptr && tree->right != nullptr)
			return postorder1(tree->left) + " " + postorder1(tree->right) + " " + std::to_string(tree->data);
		else if (tree->right == nullptr && tree->left != nullptr)
			return postorder1(tree->left) + " " + std::to_string(tree->data);
		else if (tree->left == nullptr && tree->right != nullptr)
			return postorder1(tree->right) + " " + std::to_string(tree->data);
		else if (tree->left == nullptr && tree->right == nullptr)
			return std::to_string(tree->data);
	}
	else
		return "";
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
	return postorder1(tree);
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
    return binary_tree(other);
}

bool equal(node* a, node* b)
{
	if (a == nullptr && b == nullptr)
		return true;
	if (a != nullptr && b != nullptr)
		return (a->data == b->data && equal(a->left, b->left) && equal(a->right, b->right));
	else
		return false;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
		return equal(this->tree, other.tree);
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
	return !(equal(this->tree, other.tree));
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	insert(value);
    return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	remove(value);
    return binary_tree();
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
	int a;
	while (in >> a)
	{
		value.insert(a);
	}
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
	out << value.inorder();

    return out;
}
