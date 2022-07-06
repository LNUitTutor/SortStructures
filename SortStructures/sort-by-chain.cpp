#include "data-procedures.h"
#include "new-types.h"

const char * FileName = "data.txt";
const char * NewFileName = "chaindata.txt";

void SortByChain()
{
	cout << "\n *���������� ����� �� ��������� ������*\n\n";
	ifstream input_file(FileName);
	// ������� ������ ������ ���� ��������� �����
	ChainNode* chain = new ChainNode();
	while (!input_file.eof())
	{
		DataEntry e; input_file >> e;
		InsertNode(chain, e);
	}
	input_file.close();
	// ������� ����������
	PrintChain(chain->link, cout);
	ofstream result(NewFileName);
	PrintChain(chain->link, result);
	result.close();
	DeleteChain(chain);
	return;
}