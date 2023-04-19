#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void InsertionSort(int* a, int n);
void ShellSort(int* a, int n);
void PrintArray(int* a, int n);
void SelectionSort(int* a, int n);
void Swap(int* p1, int* p2);
void BubbleSort(int* a, int n);
void QuickSort(int* a, int begin,int end);
void QuickSortNonR(int* a, int begin, int end);
void MergeSort(int* a, int n);
void _MergeSort(int* a, int begin, int end, int* tmp);
void MergeSortNonR(int* a, int n);
void CountSort(int* a, int n);

//声明
extern callCount;
