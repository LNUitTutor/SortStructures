#include "data-procedures.h"
#include "new-types.h"

int* Merge(int* a, unsigned n, int* b, unsigned m);
List_t BuildSortedList(int* a, unsigned n);
List_t Merge(List_t a, List_t b);
void MergeAndCut(List_t& a, List_t& b);

void MergeSequences()
{
	cout << "\n *������ ������������� ������*\n\n";
	int a[] = { 1,2,5,7,9 };
	int b[] = { 3,4,6,8 };
	const unsigned n = sizeof a / sizeof a[0];
	const unsigned m = sizeof b / sizeof b[0];
	cout << "������ ����� �������:\n";
	PrintVector(a, n);
	PrintVector(b, m);
	int* c = Merge(a, n, b, m);
	cout << "��������� �����:\n";
	PrintVector(c, n + m);
	delete[] c;
	system("pause");
	cout << "\n\n *������ ������������� ������*\n\n";
	List_t list_a = BuildSortedList(a, n);
	List_t list_b = BuildSortedList(b, m);
	cout << "������ ����� �������:\n";
	PrintChain(list_a, cout);
	cout << '\n';
	PrintChain(list_b, cout);
	List_t list_c = Merge(list_a, list_b);
	cout << "��������� ������:\n";
	PrintChain(list_c, cout);
	DeleteChain(list_a);
	DeleteChain(list_b);
	DeleteChain(list_c);
	return;
}
List_t BuildSortedList(int* a, unsigned n)
{
	ChainNode phantom;
	List_t r = &phantom;
	for (int i = 0; i < n; ++i)
	{
		DataEntry data = { a[i],"" };
		InsertNode(r, data);
	}
	return phantom.link;
}

// ��'������� ���� ������������� ������ � �����
int* Merge(int* a, unsigned n, int* b, unsigned m)
{
	unsigned curr_a = 0;  // ����� ������ ����������� � ������� ��������
	unsigned curr_b = 0;
	unsigned dest = 0;    // ��������� ���������� ����� �� �������
	int* c = new int[n + m]; // ����� ����� �������� ������ �����
	while (curr_a < n && curr_b < m)
	{                        // ���������� �������� ������� ������
		if (a[curr_a] < b[curr_b])     // �����ົ ������
			c[dest++] = a[curr_a++];
		else c[dest++] = b[curr_b++];
	}
	// ����������� �������, ������� ���� ���� � �����
	while (curr_a < n) c[dest++] = a[curr_a++];
	while (curr_b < m) c[dest++] = b[curr_b++];
	return c;
}
// ��'������� ���� ������������� ������ � ����� ���������� ��������
List_t Merge(List_t a, List_t b)
{
	// ����� ������ ����������� � ������� ��������, �� ��� �������� � � b
	// �������� �����, ��� ����� ����� ���������� �� ���� �����������
	ChainNode phantom;
	// ��������� ������ ���������, �� ���� �����, �������� �� ������
	List_t r = &phantom;     // ���� ��������� �����
	while (a != nullptr && b != nullptr)
	{
		    // ���������� �������� ������� ������
			if (a->elem < b->elem)          // �����ົ ������
			{
				r->link = new ChainNode(a->elem);
				a = a->link;
			}
			else
			{
				r->link = new ChainNode(b->elem);
				b = b->link;
			}
		r = r->link;
	}
	// �������� �������
	while (a != nullptr)
	{
		r->link = new ChainNode(a->elem);
		a = a->link;
		r = r->link;
	}
	while (b != nullptr)
	{
		r->link = new ChainNode(b->elem);
		b = b->link;
		r = r->link;
	}
	return phantom.link;
}

void MergeLists()
{
	cout << "\n *������ ������������� ������ ����������� �����*\n\n";
	int a[] = { 1,2,5,7,9 };
	int b[] = { 3,4,6,8 };
	const unsigned n = sizeof a / sizeof a[0];
	const unsigned m = sizeof b / sizeof b[0];
	List_t list_a = BuildSortedList(a, n);
	List_t list_b = BuildSortedList(b, m);
	cout << "������ ����� �������:\n";
	PrintChain(list_a, cout);
	cout << '\n';
	PrintChain(list_b, cout);
	MergeAndCut(list_a, list_b);
	cout << "��������� ������:\n";
	PrintChain(list_a, cout);
	DeleteChain(list_a);
	return;
}

void MergeAndCut(List_t& a, List_t& b)
{
	List_t result; // ��������� ���������� � �������� ������
	if (a->elem < b->elem) result = a;
	else
	{
		result = b; b = a; a = result;
	}
	// b ������ �����, �� �� �� ����� �������� ����������
	while (b != nullptr)
	{
		// ������ ����� ��� ���� ��'���� ����������� � ���������?
		while (a->link != nullptr && a->link->elem < b->elem)
			a = a->link;
		// ����: ������ b ���������� �� ����������,
		// ���� ������ � ��� ������ b
		List_t helper = a->link;
		a->link = b;
		b = helper;
		a = a->link;
	}
	a = result;
}
