#include "data-procedures.h"
#include "new-types.h"

const char * InputFileName = "data.txt";
const char * OutputFileName = "treedata.txt";

void SortByTree()
{
	cout << "\n *Сортування файла за допомогою дерева пошуку*\n\n";
	ifstream input_file(InputFileName);
	TreeNode* tree = nullptr;
	while (!input_file.eof())
	{
		DataEntry e; input_file >> e;
		InsertTreeNode(tree, e);
	}
	input_file.close();
	// Друкуємо результати
	PrintTree(tree, cout);   // На екран
	ofstream result(OutputFileName);
	PrintTree(tree, result); // і до файла
	result.close();
	// Очищаємо динамічну пам'ять
	DeleteTree(tree);
	return;
}