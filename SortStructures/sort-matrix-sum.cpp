#include "data-procedures.h"
#include <cmath>

void SortMatrixSum()
{
	cout << "\n *Сортування рядків матриці за зростанням сум модулів*\n\n";
	// Для спрощення розміри матриці задамо в коді програми
	int a[n][m];
	// Вводимо задану матрицю
	ReadMatrix(a);
	// ФОРМУВАННЯ МАСИВУ КЛЮЧІВ
	int key[n] = {0};
	for (unsigned i = 0; i < n; ++i)
		for (unsigned j = 0; j < m; ++j) key[i] += abs(a[i][j]);
	// ВПОРЯДКУВАННЯ МАСИВУ КЛЮЧІВ & РЯДКІВ МАТРИЦІ
	for (unsigned last_unsorted = n - 1; last_unsorted > 0; --last_unsorted)
	{
		// знаходимо найбільший елемент невпорядкованої частини
		unsigned index_of_max = 0;                  // початковий номер ключа
		for (unsigned i = 1; i < last_unsorted; ++i) // перевіряємо всі решту
			if (key[i] > key[index_of_max]) index_of_max = i;
		if (index_of_max != last_unsorted)
		{
			// міняємо місцями ключі і рядки
			int toSwap = key[last_unsorted];
			key[last_unsorted] = key[index_of_max];
			key[index_of_max] = toSwap;
			SwapArray(a[last_unsorted], a[index_of_max], m);
		}
	}
	// Друкуємо результати
	cout << "\nКлючі:\n";
	for (unsigned i = 0; i < n; ++i) cout << '\t' << key[i];
	cout << "\n\nМатриця:\n";
	PrintMatrix(a);
	return;
}