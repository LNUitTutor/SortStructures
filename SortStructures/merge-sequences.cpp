#include "data-procedures.h"
#include "new-types.h"

int* Merge(int* a, unsigned n, int* b, unsigned m);
List_t BuildSortedList(int* a, unsigned n);
List_t Merge(List_t a, List_t b);
void MergeAndCut(List_t& a, List_t& b);

void MergeSequences()
{
	cout << "\n *Злиття впорядкованих масивів*\n\n";
	int a[] = { 1,2,5,7,9 };
	int b[] = { 3,4,6,8 };
	const unsigned n = sizeof a / sizeof a[0];
	const unsigned m = sizeof b / sizeof b[0];
	cout << "Масиви перед злиттям:\n";
	PrintVector(a, n);
	PrintVector(b, m);
	int* c = Merge(a, n, b, m);
	cout << "Отриманий масив:\n";
	PrintVector(c, n + m);
	delete[] c;
	system("pause");
	cout << "\n\n *Злиття впорядкованих списків*\n\n";
	List_t list_a = BuildSortedList(a, n);
	List_t list_b = BuildSortedList(b, m);
	cout << "Списки перед злиттям:\n";
	PrintChain(list_a, cout);
	cout << '\n';
	PrintChain(list_b, cout);
	List_t list_c = Merge(list_a, list_b);
	cout << "Отриманий список:\n";
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

// об'єднання двох впорядкованих масивів у новий
int* Merge(int* a, unsigned n, int* b, unsigned m)
{
	unsigned curr_a = 0;  // задані масиви переглядаємо з першого елемента
	unsigned curr_b = 0;
	unsigned dest = 0;    // результат заповнюємо також від початку
	int* c = new int[n + m]; // новий масив міститиме обидва задані
	while (curr_a < n && curr_b < m)
	{                        // конкурують елементи заданих масивів
		if (a[curr_a] < b[curr_b])     // «виграє» менший
			c[dest++] = a[curr_a++];
		else c[dest++] = b[curr_b++];
	}
	// дописування «хвоста», спрацює лише один з циклів
	while (curr_a < n) c[dest++] = a[curr_a++];
	while (curr_b < m) c[dest++] = b[curr_b++];
	return c;
}
// об'єднання двох впорядкованих списків у новий копіюванням елементів
List_t Merge(List_t a, List_t b)
{
	// задані списки переглядаємо з першого елемента, на них вказують а і b
	// допоміжна ланка, щоб перша ланка результату не була «особливою»
	ChainNode phantom;
	// результат будуємо поступово, по одній ланці, спочатку він містить
	List_t r = &phantom;     // лише заголовну ланку
	while (a != nullptr && b != nullptr)
	{
		    // конкурують елементи заданих масивів
			if (a->elem < b->elem)          // «виграє» менший
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
	// дописуємо «хвости»
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
	cout << "\n *Злиття впорядкованих списків переміщенням ланок*\n\n";
	int a[] = { 1,2,5,7,9 };
	int b[] = { 3,4,6,8 };
	const unsigned n = sizeof a / sizeof a[0];
	const unsigned m = sizeof b / sizeof b[0];
	List_t list_a = BuildSortedList(a, n);
	List_t list_b = BuildSortedList(b, m);
	cout << "Списки перед злиттям:\n";
	PrintChain(list_a, cout);
	cout << '\n';
	PrintChain(list_b, cout);
	MergeAndCut(list_a, list_b);
	cout << "Отриманий список:\n";
	PrintChain(list_a, cout);
	DeleteChain(list_a);
	return;
}

void MergeAndCut(List_t& a, List_t& b)
{
	List_t result; // результат починається з «меншого» списку
	if (a->elem < b->elem) result = a;
	else
	{
		result = b; b = a; a = result;
	}
	// b містить ланки, які ще не стали частиною результату
	while (b != nullptr)
	{
		// скільки ланок без зміни зв'язків потрапляють у результат?
		while (a->link != nullptr && a->link->elem < b->elem)
			a = a->link;
		// обмін: список b долучається до результату,
		// хвіст списку а стає списом b
		List_t helper = a->link;
		a->link = b;
		b = helper;
		a = a->link;
	}
	a = result;
}
