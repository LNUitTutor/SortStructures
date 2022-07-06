#include "data-procedures.h"
#include <cmath>

void SortMatrixSum()
{
	cout << "\n *���������� ����� ������� �� ���������� ��� ������*\n\n";
	// ��� ��������� ������ ������� ������ � ��� ��������
	int a[n][m];
	// ������� ������ �������
	ReadMatrix(a);
	// ���������� ������ ���ײ�
	int key[n] = {0};
	for (unsigned i = 0; i < n; ++i)
		for (unsigned j = 0; j < m; ++j) key[i] += abs(a[i][j]);
	// ������������� ������ ���ײ� & ���ʲ� �����ֲ
	for (unsigned last_unsorted = n - 1; last_unsorted > 0; --last_unsorted)
	{
		// ��������� ��������� ������� �������������� �������
		unsigned index_of_max = 0;                  // ���������� ����� �����
		for (unsigned i = 1; i < last_unsorted; ++i) // ���������� �� �����
			if (key[i] > key[index_of_max]) index_of_max = i;
		if (index_of_max != last_unsorted)
		{
			// ������ ������ ����� � �����
			int toSwap = key[last_unsorted];
			key[last_unsorted] = key[index_of_max];
			key[index_of_max] = toSwap;
			SwapArray(a[last_unsorted], a[index_of_max], m);
		}
	}
	// ������� ����������
	cout << "\n�����:\n";
	for (unsigned i = 0; i < n; ++i) cout << '\t' << key[i];
	cout << "\n\n�������:\n";
	PrintMatrix(a);
	return;
}