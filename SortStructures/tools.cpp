#include "data-procedures.h"
#include "new-types.h"
#include <iomanip>

void ReadMatrix(int a[n][m])
{
	cout << "������ �������� ������� " << n << 'x' << m << '\n';
	for (unsigned i = 0; i < n; ++i)
		for (unsigned j = 0; j < m; ++j) cin >> a[i][j];
}

void PrintMatrix(int a[n][m])
{
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < m; ++j) cout << '\t' << a[i][j];
		cout << '\n';
	}
}

// ������������� ������ � �������� ���������
void SimpleInsertSort(int* a, unsigned n)
{
	// �������� ������������� � ���� ������ ������� �����������
	// ���������� �� ���� � ����� � ��� �������� �� �������� ����
	for (unsigned j = 1; j < n; ++j)
	{
		// ������ ���� ��� j-�� ��������
		int b = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > b)
		{					// ������� ����������� ��������
			a[i + 1] = a[i];
			--i;
		}
		// ��������� j-�� ������� � ������������ �������
		a[i + 1] = b;
	}
	return;
}

// ���� ������� ���� ������ (����� �������)
void SwapArray(int* a, int* b, unsigned n)
{
	for (unsigned i = 0; i < n; ++i)
	{
		int to_swap = a[i];
		a[i] = b[i];
		b[i] = to_swap;
	}
}

void PrintVector(int* a, unsigned n)
{
	for (unsigned i = 0; i < n; ++i)
		cout << std::setw(5) << a[i];
	cout << std::endl;
}

// ��������� ��������-��������� �����
std::istream& operator>>(std::istream& is, DataEntry& e)
{
	is >> e.key >> e.value;
	return is;
}
std::ostream& operator<<(std::ostream& os, const DataEntry& e)
{
	os << e.key << '\t' << e.value;
	return os;
}

bool operator<(const DataEntry& left, const DataEntry& right)
{
	return left.key < right.key;
}

bool operator>(const DataEntry& left, const DataEntry& right)
{
	return left.key > right.key;
}

// ���� ������'������ ������
void PrintChain(ChainNode* head, std::ostream& os)
{
	while (head != nullptr)
	{
		os << '\t' << head->elem << '\n';
		head = head->link;
	}
}

// ������� ����� � ������������� ������
void InsertNode(ChainNode* head, const DataEntry& e)
{
	ChainNode* current = head;
	// ����� ����
	while (current->link != nullptr && current->link->elem < e)
		current = current->link;
	// ����������
	current->link = new ChainNode(e, current->link);
}

// ��������� � ���'�� ������'������ ������
void DeleteChain(ChainNode*& head)
{
	ChainNode* victim;
	while (head != nullptr)
	{
		victim = head;
		head = head->link;
		delete victim;
	}
	head = nullptr;
}

// ��������� �������� ������ � ���� (inorder �����)
void PrintTree(TreeNode* root, std::ostream& os)
{
	if (root->left_tree != nullptr) PrintTree(root->left_tree, os);
	os << '\t' << root->elem << '\n';
	if (root->right_tree != nullptr) PrintTree(root->right_tree, os);
}

// ���������� �������� � ������ ������
void InsertTreeNode(TreeNode*& root, const DataEntry& e)
{
	if (root == nullptr)
		root = new TreeNode(e);
	else if (e < root->elem)
		InsertTreeNode(root->left_tree, e);
	else
		InsertTreeNode(root->right_tree, e);
}

// ��������� � ���'�� ������ ������
void DeleteTree(TreeNode*& root)
{
	if (root->left_tree != nullptr) DeleteTree(root->left_tree);
	if (root->right_tree != nullptr) DeleteTree(root->right_tree);
	delete root;
}