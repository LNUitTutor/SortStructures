#include <Windows.h>
#include "data-procedures.h"

int main()
{
	// Сортування структур даних

	SetConsoleOutputCP(1251); // налаштуємо виведення кирилицею
	int answer;
	do
	{
		system("cls");
		cout << "Виберіть алгоритм для виконання:\n\n 1 - Впорядкування кожного рядка матриці\n"
			<< " 2 - Сортування рядків матриці\n 3 - Сортування рядків матриці за сумами модулів\n"
			<< " 4 - Впорядкування файла за допомогою списку\n 5 - Впорядкування файла бінарним деревом\n"
			<< " 6 - Злиття впорядкованих послідовностей\n 7 - Об'єднання впорядкованих списків\n"
			<< " 8 - Впорядкування файла злиттям\n 9 - Завершення роботи\n>>>> ";
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
		default: cout << "До побачення!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 9);
	return 0;
}