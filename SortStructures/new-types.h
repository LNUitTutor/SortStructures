#ifndef _TYPES_GUARD_
#define _TYPES_GUARD_

#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

struct DataEntry   // елемент даних
{
	int key;
	string value;  // значення може мати довільний тип
};
// Для зручності роботи з даними перевантажимо оператори введення-виведення
std::istream& operator>>(std::istream& is, DataEntry& e);
std::ostream& operator<<(std::ostream& os, const DataEntry& e);
bool operator<(const DataEntry& left, const DataEntry& right);
bool operator>(const DataEntry& left, const DataEntry& right);

struct ChainNode
{
	ChainNode* link;
	DataEntry elem;
	ChainNode(): link(nullptr), elem() {}
	ChainNode(const DataEntry& e, ChainNode* p = nullptr): link(p), elem(e) {}
};

using List_t = ChainNode*;

void PrintChain(ChainNode* head, std::ostream& os);
void InsertNode(ChainNode* head, const DataEntry& E);
void DeleteChain(ChainNode*& head);

struct TreeNode
{
	TreeNode* left_tree;
	TreeNode* right_tree;
	DataEntry elem;
	TreeNode(): left_tree(nullptr), right_tree(nullptr), elem() {}
	TreeNode(const DataEntry& e, TreeNode* pl = nullptr, TreeNode* pr = nullptr): 
		left_tree(pl), right_tree(pr), elem(e) {}
};

void PrintTree(TreeNode* root, std::ostream& os);
void InsertTreeNode(TreeNode*& root, const DataEntry& E);
void DeleteTree(TreeNode*& root);

#endif