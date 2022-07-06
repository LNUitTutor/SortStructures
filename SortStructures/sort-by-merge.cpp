#include "data-procedures.h"
#include <ctime>

void SortByMerge()
{
	cout << "\n *������ ���������� ����� ������ �������*\n\n";
	const char * fileName = "mergeDat.txt";
	cout << "����� �����? >>> "; int n; cin >> n;
	ofstream file(fileName);
	FillFile(file, n);
	ShowFile(fileName);
	SortFile(fileName);
	ShowFile(fileName);
	return;
}

void FillFile(ofstream& f, unsigned n)
{
	// �������� ���� ����������� ������ ����������
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
	// �������� ���� ����� �� �����
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
	// ������������� ����� ������������� ����������� �������
	ifstream source(file_name);
	if (!source.is_open())
	{
		cout << "File " << file_name << " don\'t exists.\n";
		return;
	}

	// ������ ���������� ������� ������ � ���������� ������
	ofstream file_f("_1.tmp");
	ofstream file_g("_2.tmp");
	long long ka, kb; // ������� ������ � ����������� �������
	Distribute(source, file_f, file_g, ka, kb);
	source.close();
	file_f.close();
	file_g.close();

	// ����������� �� ��������� ������
	ifstream file_a;
	ifstream file_b;
	long long segment_length = 2;  // ���������� ����� ������������� ������
	bool odd = true;
	int a, b;         // �������� �����
	// �������� ������, ���� ������ � � ���� ������
	while (ka > 0 && kb > 0)
	{
		// ������� ������� ��� ������� �������� - ��� ������
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
		// ������� ������ ��������� � ����� ���������
		for (long long segment_number = 0; segment_number < kb; ++segment_number)
		{
			if (segment_number % 2 == 0)
				MergeFile(file_a, file_b, file_f, segment_length);
			else MergeFile(file_a, file_b, file_g, segment_length);
		}
		// �������� �����
		if (ka > kb) // ������ ���� ������
		{
			if (kb % 2)
			{
				ka /= 2; kb = ka;
				while (!file_a.eof()) // ������� ���� �������
				{
					file_a >> a;
					file_g << ' ' << a;
				}
			}
			else // �� ���� ��� �ᒺ�����!
			{
				kb /= 2; ka = kb + 1;
				while (!file_a.eof()) // ������� ������� ������� �����
				{
					file_a >> a;
					file_f << ' ' << a;
				}
			}
		}
		else // ����� ̲����� �������� �-��� ²�в�ʲ�
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
	// �������� �������� �����
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
	// ��������� ������ ����� f �� ����� a i b � ������ �� 2 ������
	// ka - ������� ������ � ���� a, kb - � ���� b
{
	int x, y;        // �������� �����, ������� � �����
	ka = 0; kb = 0;  // ����������� ����� ���� �� ������
	// ���� �������� ���������� break, ���� ��������� ���� �����
	while (true)
	{
		// *** �������� �������� �� ����� a ***
		if (source.eof()) break;
		else
		{
			source >> x; ++ka;
			if (source.eof()) // ��������� ����� �� �� ����
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
		// *** ����� ��������� ��� ��� ����� b ***
		if (source.eof()) break;
		else
		{
			source >> x; ++kb;
			if (source.eof()) // ��������� ����� �� �� ����
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
	// ��'���� ������ ������� k � ����� file_a � � ����� file_b 
	// � ������ �� � ���� result
	int a, b;        // �������� �����, ������� � �����
	file_a >> a; file_b >> b;  // ��������� ����� �������� ������
	long long count_a = 1;     // ��������� �����������
	long long count_b = 1;
	while (true)
	{
		if (a < b)
		{
			result << ' ' << a;
			if (count_a >= k || file_a.eof()) // ���� � ���������
			{
				result << ' ' << b;
				break;
			}
			else            // ������ �������� �������� � ����� a
			{
				file_a >> a; ++count_a;
			}
		}
		else
		{
			result << ' ' << b;
			if (count_b >= k || file_b.eof()) // ���� b ���������
			{
				result << ' ' << a;
				break;
			}
			else            // ������ �������� �������� � ����� b
			{
				file_b >> b; ++count_b;
			}
		}
	}
	while (count_a < k && !file_a.eof()) // �������� "������"
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
