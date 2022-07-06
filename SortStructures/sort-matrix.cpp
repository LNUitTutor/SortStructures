#include "data-procedures.h"

void SortMatrix()
{
	cout << "\n *���������� ����� ������� �� ���������� ������ ��������*\n\n";
	// ��� ��������� ������ ������� ������ � ��� ��������
	int a[n][m];
	// ������� ������ �������
	ReadMatrix(a);
	// ������������� ������� ������� �����ֲ �� ��������� ������ �����������
	for (unsigned last_unsorted = n - 1; last_unsorted > 0; --last_unsorted)
	{
		// ��������� ��������� ������� �������������� �������
		unsigned index_of_max = 0;                  // ���������� ����� ����������
		for (unsigned i = 1; i <= last_unsorted; ++i) // ���������� �� �����
			if (a[i][0] > a[index_of_max][0]) index_of_max = i;
		if (index_of_max != last_unsorted)
			// ������ ������ �����: ������� � ���������
			SwapArray(a[last_unsorted], a[index_of_max], m);
	}
	// ������� ����������
	PrintMatrix(a);
	return;
}