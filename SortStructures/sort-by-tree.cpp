#include "data-procedures.h"
#include "new-types.h"

const char * InputFileName = "data.txt";
const char * OutputFileName = "treedata.txt";

void SortByTree()
{
	cout << "\n *���������� ����� �� ��������� ������ ������*\n\n";
	ifstream input_file(InputFileName);
	TreeNode* tree = nullptr;
	while (!input_file.eof())
	{
		DataEntry e; input_file >> e;
		InsertTreeNode(tree, e);
	}
	input_file.close();
	// ������� ����������
	PrintTree(tree, cout);   // �� �����
	ofstream result(OutputFileName);
	PrintTree(tree, result); // � �� �����
	result.close();
	// ������� �������� ���'���
	DeleteTree(tree);
	return;
}