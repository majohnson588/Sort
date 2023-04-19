#include "Sort.h"
#include "Stack.h"

int callCount = 0;

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
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

void AdjustUp(int* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//堆排序
//升序建大堆，降序建小堆
void HeapSort(int* a, int n)
{
	//建堆方式1：O(N*logN)
	//for (int i = 0; i < n; ++i)
	//{
	//	AdjustUp(a, i);
	//}

	//建堆方式2：O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	//O(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

//冒泡排序
//时间复杂度：O(N^2)
//最好O(N)
//对比插入排序，谁最好？ - 还是冒泡排序好
void BubbleSort(int* a, int n)
{
	assert(a);

	int exchange = 0;
	for (int i = 1; i < n; ++i)
	{
		if (a[i - 1] > a[i])
		{
			Swap(&a[i - 1], &a[i]);
			exchange = 1;
		}
	}

	if (exchange == 0)
	{
		break;
	}
}


//快速排序 - 最强算法
// 时间复杂度O(N*logN)
// 最坏是O(N^2),且若数组已经有序或接近有序则处于最坏或较坏情况，容易出现栈溢出
// 原因是该算法无法判断是否已经有序
// 最理想为key取中

int GetMidIndex(int* a, int begin, int end)
{
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
		{
			return mid;
		}
		else if (a[begin] < a[end])
		{
			return end;
		}
		else
		{
			return begin;
		}
	}
	else //(a[begin] > a[mid])
	{
		if (a[mid] > a[end])
		{
			return mid;
		}
		else if (a[begin] < a[end])
		{
			return begin;
		}
		else
		{
			return end;
		}
	}
}

//1、hoare版本（霍尔版本）————hoare是发明这个算法的人
int PartSort1(int* a, int begin, int end)
{
	int left = begin, right = end;
	int keyi = a[left];//排升序时，左边做key右边先走，右边做key左边先走
	while (left < right)
	{
		//右边先走，找小
		while (left < right && a[right] >= a[keyi])
		{
			--right;
		}

		//左边再走，找大
		while (left < right && a[left] <= a[keyi])
		{
			++left;
		}

		Swap(&a[left], &a[right]);
	}

	Swap(&a[keyi], &a[left]);

	return keyi;
}

//2、挖坑法 - 细微差别（理解更简单）
int PartSort2(int* a, int begin, int end)
{
	int key = a[begin];
	int piti = begin;
	while (begin < end)
	{
		//右边找小，填到左边的坑里面去。这个位置形成新的坑
		while (begin < end && a[end] >= key)
		{
			--end;
		}

		a[piti] = a[end];
		piti = end;

		//左边找大，填到右边的坑里面去。这个位置形成新的坑
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}

		a[piti] = a[begin];
		piti = begin;
	}

	a[piti] = key;
	return piti;
}

//3、前后指针法
int PartSort3(int* a, int begin, int end)
{
	int prev = begin;
	int cur = begin + 1;
	int keyi = begin;

	//三数取中
	int midi = GetMidIndex(a, begin, end);
	Swap(&a[keyi], &a[midi]);

	while (cur <= end)
	{
		//cur位置的值小于keyi位置值
		if (a[cur] < a[keyi] && ++prev != cur)
			Swap(&a[prev], &a[cur]);

		++cur;
	}

	Swap(&a[prev], &a[keyi]);
	keyi = prev;

	return keyi;
}

void QuickSort(int* a, int begin,int end)
{
	callCount++;

	//区间不存在，或者只有一个值则不需要再处理
	if (begin >= end)
	{
		return;
	}

	//最后10个数留给InsertSort,极大减少递归深度（大概70%）
	if (end - begin > 20)
	{
		//int keyi = PartSort1(a, begin, end);
        //int keyi = PartSort2(a, begin, end);
		int keyi = PartSort3(a, begin, end);
		// [begin, keyi-1] keyi [keyi+1, end]
		QuickSort(a, begin, keyi - 1);
		QuickSort(a, keyi + 1, end);
	}
	else
	{
		InsertSort(a + begin, end - begin + 1);
	}
}

//改非递归
//递归最大的问题，极端场景下面，如果深度太深，会出现栈溢出
//1、直接改循环 -- 比如斐波那契数列、归并排序

//用栈实现
void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st, end);
	StackPush(&st, begin);

	while (!StackEmpty(&st))
	{
		int left = StackTop(&st);
		StackPop(&st);

		int right = StackTop(&st);
		StackPop(&st);

		int keyi = PartSort3(a, left, right);
		// [left, keyi-1] keyi[keyi+1, right]

		if (keyi + 1 < right)
		{
			StackPush(&st, right);
			StackPush(&st, keyi + 1);
		}

		if (left < keyi - 1)
		{
			StackPush(&st, keyi - 1);
			StackPush(&st, left);
		}
	}

	StackDestroy(&st);
}
//使用队列模拟也可以，但是模拟的方式不一样，他是层序遍历
//而栈是先左边深度遍历再走右边

void _MergeSort(int* a, int begin, int end,int* tmp)
{
	if (begin >= end)
		return;

	int mid = (begin + end) / 2;

	//[begin,mid] [mid+1,end] 分治递归，让子区间有序
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid + 1, end, tmp);

	//归并 [begin,mid] [mid+1,end]
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}

	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}

	//把归并数据拷贝回原数组
	memcpy(a + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

//归并排序
//时间复杂度O(N*logN)
//空间复杂度O(N)

//递归写法
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}

	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);

	memcpy(a, tmp, sizeof(int) * n);

	free(tmp);
}

//非递归写法
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}

	//_MergeSort(a, 0, n - 1, tmp);
    //free(tmp);
	int gap = 1;
	while (gap < n)
	{
		printf("gap=%d->", gap);
		for (int i = 0; i < n; i += 2 * gap)
		{
			// [i,i+gap-1][i+gap, i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			// 思路1；end1越界或者begin2越界，则可以不归并了
			if (end1 >= n || begin2 >= n)
			{
				break;
			}
			else if (end2 >= n)
			{
				end2 = n - 1;
			}

			//思路2：越界-修改边界
			if (end1 >= n)
			{
				end1 = n - 1;
				// [begin2,end2]修正为不存在区间
				begin2 = n;
				end2 = n - 1;
			}
			else if (end2 >= n)
			{
				// [begin2,end2]修正为不存在区间
				begin2 = n;
				end2 = n - 1;
			}
			else if (end2 >= n)
			{
				end2 = n - 1;
			}

			printf("[%d, %d] [%d, %d]--", begin1, end1, begin2, end2);

			int m = end2 - begin1 + 1;
			int j = begin1;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}
			}

			while (begin1 <= end1)
			{
				tmp[j++] = a[begin1++];
			}

			while (begin2 <= end2)
			{
				tmp[j++] = a[begin2++];
			}

			memcpy(a + i, tmp + i, sizeof(int) * m);
		}
		printf("\n");
		gap *= 2;
	 } 
	free(tmp);
}

//计数排序
//1、统计每个数据出现的次数
//2、排序（按出现次数写回原数组）
//局限性：
//1、如果是浮点数，字符串就不适用了
//2、如果数据范围很大，空间复杂度就会很高，相对不适合
//适合范围集中，重复数据多

void CountSort(int* a, int n)
{
	int min = a[0], max = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] < min)
			min = a[i];

		if (a[i] > max)
			max = a[i];
	}

	//统计次数的数组
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	memset(count, 0, sizeof(int) * range);

	//统计次数
	for (int i = 0; i < n; ++i)
	{
		count[a[i] - min]++;
	}

	//回写-排序
	int j = 0;
	for (int i = 0; i < range; ++i)
	{
		//出现几次就回写几个i+min
		while (count[i]--)
		{
			a[j++] = i + min;
		}
	}
}

//时间复杂度：O(max(range,N))
//空间复杂度：O(N)
