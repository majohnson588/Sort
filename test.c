#include "Sort.h"

void TestInsertionSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	InsertionSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestShellSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	ShellSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestSelectionSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	SelectionSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestBubbleSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	BubbleSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestQuickSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	QuickSort(a,0, sizeof(a) / sizeof(int)-1);
	PrintArray(a, sizeof(a) / sizeof(int));
}

int main()
{
	//TestInsertionSort();
	//TestShellSort();
	//TestOP();
	//TestSelectionSort();
	//TestBubbleSort();
	TestQuickSort();

	return 0;
}
