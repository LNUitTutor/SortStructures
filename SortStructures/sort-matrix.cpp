#include "data-procedures.h"

void SortMatrix()
{
	cout << "\n *—ортуванн€ р€дк≥в матриц≥ за зростанн€м перших елемент≥в*\n\n";
	// ƒл€ спрощенн€ розм≥ри матриц≥ задамо в код≥ програми
	int a[n][m];
	// ¬водимо задану матрицю
	ReadMatrix(a);
	// ¬ѕќ–яƒ ”¬јЌЌя ѕ≈–Ўќ√ќ —“ќ¬ѕ÷я ћј“–»÷≤ «ј ƒќѕќћќ√ќё ¬»Ѕќ–” Ќј…Ѕ≤Ћ№Ўќ√ќ
	for (unsigned last_unsorted = n - 1; last_unsorted > 0; --last_unsorted)
	{
		// знаходимо найб≥льший елемент невпор€дкованоњ частини
		unsigned index_of_max = 0;                  // початковий номер найб≥льшого
		for (unsigned i = 1; i <= last_unsorted; ++i) // перев≥р€Їмо вс≥ решту
			if (a[i][0] > a[index_of_max][0]) index_of_max = i;
		if (index_of_max != last_unsorted)
			// м≥н€Їмо м≥сц€ми р€дки: останн≥й з найб≥льшим
			SwapArray(a[last_unsorted], a[index_of_max], m);
	}
	// ƒрукуЇмо результати
	PrintMatrix(a);
	return;
}