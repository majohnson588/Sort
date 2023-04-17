#include "Sort.h"

void Swap(int* p1, int* p2)
{
	int tmp = p1;
	p1 = p2;
	p2 = tmp;
}

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

//插入排序
//时间复杂度O(N^2)
void InsertionSort(int* a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		// [0,end]有序，把end+1位置的值插入，保持有序
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])//升序
			//if(tmp > a[end]) 降序
			{
				a[end + 1] = a[end];
				--end;
		    }
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}
	
//希尔排序
//1、预排序
//2、直接插入排序
//排升序，gap越大，大的数更快到后面，小的数可以更快的到前面，但是越不接近有序
//排升序，gap越小，越接近有序。当gap == 1，就是直接插入排序
//平均时间复杂度 O(N^1.3) 证明略
void ShellSort(int* a, int n)
{
	//gap > 1时是预排序
	//gap 最后一次等于1，是直接插入排序
	PrintArray(a, n);

	int gap = n;
	while (gap > 1)
	{
		gap = gap/3 + 1;
		//N/3/3/3.../3 == 1
		// 3^X = N
		// x = log3N（3为底数）
        //gap/=2;

		//gap很大的时候，大概是2N次
		//gap很小的时候，大概是N次
		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}

		printf("gap:%d->", gap);
		PrintArray(a, n);
	}
}

//等差数列求时间复杂度
//O (N^2)
//对比 插入排序 谁更好？ -- 插入
//插入排序最好为O(N),最差为O(N^2),而选择排序最好最差均为O(N)
//同情况下，选择排序为最差算法
void SelectionSort(int* a, int n)
{
	assert(a);

	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = begin;
		for (int i = begin + 1; i <= end; ++i)
		{
			if (a[i] < a[mini])
				mini = i;

			if (a[i] > a[maxi])
				maxi = i;
		}
		Swap(&a[begin], &a[mini]);

		//如果begin和maxi重叠，那么要修正一下maxi的位置
		if (begin == maxi)
		{
			maxi = mini;
		}

		Swap(&a[end], &a[maxi]);
		++begin;
		--end;
	}
}
