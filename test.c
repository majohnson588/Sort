#include "Sort.h"

void TestInsertionSort()
{
	int a[] = { 9,1,2,5,7,4,8,6,3,5 };
	InsertSort(a, sizeof(a) / sizeof(int));
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
	ShellSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

int main()
{
	//TestInsertionSort();
	//TestShellSort();
	//TestOP();
	TestSelectionSort();

	return 0;
}
