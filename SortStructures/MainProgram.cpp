#include <Windows.h>
#include "data-procedures.h"

int main()
{
	// ���������� �������� �����

	SetConsoleOutputCP(1251); // ��������� ��������� ���������
	int answer;
	do
	{
		system("cls");
		cout << "������� �������� ��� ���������:\n\n 1 - ������������� ������� ����� �������\n"
			<< " 2 - ���������� ����� �������\n 3 - ���������� ����� ������� �� ������ ������\n"
			<< " 4 - ������������� ����� �� ��������� ������\n 5 - ������������� ����� ������� �������\n"
			<< " 6 - ������ ������������� �������������\n 7 - ��'������� ������������� ������\n"
			<< " 8 - ������������� ����� �������\n 9 - ���������� ������\n>>>> ";
		cin >> answer;
		system("cls");
		switch (answer)
		{
		case 1: SortEachRow(); break;
		case 2: SortMatrix(); break;
		case 3: SortMatrixSum(); break;
		case 4: SortByChain(); break;
		case 5: SortByTree(); break;
		case 6: MergeSequences(); break;
		case 7: MergeLists(); break;
		case 8: SortByMerge(); break;
		default: cout << "�� ���������!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 9);
	return 0;
}