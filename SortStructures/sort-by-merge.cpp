#include "data-procedures.h"
#include <ctime>

void SortByMerge()
{
	cout << "\n *Зовнішнє сортування файла парним злиттям*\n\n";
	const char * fileName = "mergeDat.txt";
	cout << "Розмір файла? >>> "; int n; cin >> n;
	ofstream file(fileName);
	FillFile(file, n);
	ShowFile(fileName);
	SortFile(fileName);
	ShowFile(fileName);
	return;
}

void FillFile(ofstream& f, unsigned n)
{
	// заповнює файл випадковими цілими значеннями
	int x;
	srand(time(0));
	for (int i = 0; i < n; ++i)
	{
		x = rand() % (n * 2);
		f << ' ' << x;
	}
	f.close();
}
void ShowFile(const char* file_name)
{
	// виводить вміст файла на екран
	ifstream f(file_name);
	int x;
	while (!f.eof())
	{
		f >> x;
		cout << ' ' << x;
	}
	cout << '\n' << '\n';
	f.close();
}

void SortFile(const char* file_name)
{
	// впорядкування файлу збалансованим двошляховим злиттям
	ifstream source(file_name);
	if (!source.is_open())
	{
		cout << "File " << file_name << " don\'t exists.\n";
		return;
	}

	// Будуємо початковий розподіл записів у тимчасових файлах
	ofstream file_f("_1.tmp");
	ofstream file_g("_2.tmp");
	long long ka, kb; // кількості відрізків у початковому розподілі
	Distribute(source, file_f, file_g, ka, kb);
	source.close();
	file_f.close();
	file_g.close();

	// приготуємося до виконання злиття
	ifstream file_a;
	ifstream file_b;
	long long segment_length = 2;  // початковий розмір впорядкованих відрізків
	bool odd = true;
	int a, b;         // елементи даних
	// Виконаємо злиття, поки відрізки є в обох файлах
	while (ka > 0 && kb > 0)
	{
		// джерела відкрили для читання приймачі - для запису
		if (odd)
		{
			file_a.open("_1.tmp"); file_b.open("_2.tmp");
			file_f.open(file_name); file_g.open("_3.tmp");
		}
		else
		{
			file_a.open(file_name); file_b.open("_3.tmp");
			file_f.open("_1.tmp"); file_g.open("_2.tmp");
		}
		// зливаємо відрізки почергово в різних приймачах
		for (long long segment_number = 0; segment_number < kb; ++segment_number)
		{
			if (segment_number % 2 == 0)
				MergeFile(file_a, file_b, file_f, segment_length);
			else MergeFile(file_a, file_b, file_g, segment_length);
		}
		// дописуємо «хвіст»
		if (ka > kb) // ПЕРШИЙ ФАЙЛ ДОВШИЙ
		{
			if (kb % 2)
			{
				ka /= 2; kb = ka;
				while (!file_a.eof()) // копіюємо його залишок
				{
					file_a >> a;
					file_g << ' ' << a;
				}
			}
			else // усі пари вже об’єднано!
			{
				kb /= 2; ka = kb + 1;
				while (!file_a.eof()) // копіюємо залишок першого файлу
				{
					file_a >> a;
					file_f << ' ' << a;
				}
			}
		}
		else // ФАЙЛИ МІСТЯТЬ ОДНАКОВУ К-СТЬ ВІДРІЗКІВ
		{
			if ((kb - 1) % 2)
			{
				ka /= 2; kb = ka;
			}
			else
			{
				kb /= 2; ka = kb + 1;
			}
		}
		segment_length *= 2;
		odd = !odd;
		file_f.close(); file_g.close();
		file_a.close(); file_b.close();
	}
	// Вилучимо тимчасові файли
	if (odd)
	{
		remove(file_name);
		rename("_1.tmp", file_name);
	}
	else remove("_1.tmp");
	remove("_2.tmp");
	remove("_3.tmp");
}

void Distribute(ifstream& source, ofstream& file_a, ofstream& file_b,
	long long& ka, long long& kb)
	// розподіляє записи файлу f до файлів a i b у відрізки по 2 записи
	// ka - кількість відрізків у файлі a, kb - у файлі b
{
	int x, y;        // елементи даних, отримані з файлу
	ka = 0; kb = 0;  // результуючі файли поки що порожні
	// цикл закінчимо процедурою break, коли досягнемо кінця файлу
	while (true)
	{
		// *** Спочатку записуємо до файлу a ***
		if (source.eof()) break;
		else
		{
			source >> x; ++ka;
			if (source.eof()) // прочитане число не має пари
			{
				file_a << ' ' << x;
				break;
			}
			else
			{
				source >> y;
				if (x < y) file_a << ' ' << x << ' ' << y;
				else file_a << ' ' << y << ' ' << x;
			}
		}
		// *** Тепер повторимо все для файлу b ***
		if (source.eof()) break;
		else
		{
			source >> x; ++kb;
			if (source.eof()) // прочитане число не має пари
			{
				file_b << ' ' << x;
				break;
			}
			else
			{
				source >> y;
				if (x < y) file_b << ' ' << x << ' ' << y;
				else file_b << ' ' << y << ' ' << x;
			}
		}
	}
}

void MergeFile(ifstream& file_a, ifstream& file_b, ofstream& result, long long k)
{
	// об'єднує відрізки довжини k з файлу file_a і з файлу file_b 
	// і записує їх у файл result
	int a, b;        // елементи даних, отримані з файлів
	file_a >> a; file_b >> b;  // прочитали перші елементи відрізків
	long long count_a = 1;     // лічильники прочитаного
	long long count_b = 1;
	while (true)
	{
		if (a < b)
		{
			result << ' ' << a;
			if (count_a >= k || file_a.eof()) // файл а закінчився
			{
				result << ' ' << b;
				break;
			}
			else            // читаємо наступне значення з файлу a
			{
				file_a >> a; ++count_a;
			}
		}
		else
		{
			result << ' ' << b;
			if (count_b >= k || file_b.eof()) // файл b закінчився
			{
				result << ' ' << a;
				break;
			}
			else            // читаємо наступне значення з файлу b
			{
				file_b >> b; ++count_b;
			}
		}
	}
	while (count_a < k && !file_a.eof()) // дописуємо "хвости"
	{
		file_a >> a; ++count_a;
		result << ' ' << a;
	}
	while (count_b < k && !file_b.eof())
	{
		file_b >> b; ++count_b;
		result << ' ' << b;
	}
}
