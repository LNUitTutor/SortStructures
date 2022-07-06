#include "data-procedures.h"
#include "new-types.h"

const char * FileName = "data.txt";
const char * NewFileName = "chaindata.txt";

void SortByChain()
{
	cout << "\n *Сортування файла за допомогою списку*\n\n";
	ifstream input_file(FileName);
	// Порожній список містить лише заголовну ланку
	ChainNode* chain = new ChainNode();
	while (!input_file.eof())
	{
		DataEntry e; input_file >> e;
		InsertNode(chain, e);
	}
	input_file.close();
	// Друкуємо результати
	PrintChain(chain->link, cout);
	ofstream result(NewFileName);
	PrintChain(chain->link, result);
	result.close();
	DeleteChain(chain);
	return;
}