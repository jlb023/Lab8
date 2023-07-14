#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	extraMemoryAllocated = 0;
	for (int i = n / 2 - 1; i >= 0; i--) {
		int root = i;
		int leftChild = 2 * root + 1;
		int rightChild = 2 * root + 2;

		while (leftChild < n) {
			int maxChild = leftChild;

			if (rightChild < n && arr[rightChild] > arr[leftChild]) {
				maxChild = rightChild;
			}

			if (arr[root] < arr[maxChild]) {
				int temp = arr[root];
				arr[root] = arr[maxChild];
				arr[maxChild] = temp;

				root = maxChild;
				leftChild = 2 * root + 1;
				rightChild = 2 * root + 2;
			}
			else {
				break;
			}
		}
	}

	// Perform sorting
	for (int i = n - 1; i > 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		int root = 0;
		int leftChild = 2 * root + 1;
		int rightChild = 2 * root + 2;

		while (leftChild < i) {
			int maxChild = leftChild;

			if (rightChild < i && arr[rightChild] > arr[leftChild]) {
				maxChild = rightChild;
			}

			if (arr[root] < arr[maxChild]) {
				int temp = arr[root];
				arr[root] = arr[maxChild];
				arr[maxChild] = temp;

				root = maxChild;
				leftChild = 2 * root + 1;
				rightChild = 2 * root + 2;
			}
			else {
				break;
			}
		}

	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r) {
		int mid = l + (r - l) / 2;

		mergeSort(pData, l, mid);
		mergeSort(pData, mid + 1, r);

		int n1 = mid - l + 1;
		int n2 = r - mid;

		int* L = (int*)malloc(n1 * sizeof(int));
		int* R = (int*)malloc(n2 * sizeof(int));
		extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);

		memcpy(L, &pData[l], n1 * sizeof(int));
		memcpy(R, &pData[mid + 1], n2 * sizeof(int));

		int i = 0, j = 0, k = l;

		while (i < n1 && j < n2) {
			if (L[i] <= R[j]) {
				pData[k] = L[i];
				i++;
			}
			else {
				pData[k] = R[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			pData[k] = L[i];
			i++;
			k++;
		}

		while (j < n2) {
			pData[k] = R[j];
			j++;
			k++;
		}

		free(L);
		free(R);
	}

}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n, * data;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (int*)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			fscanf(inFile, "%d ", &n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i = 0; i < 100; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\t");

	for (i = sz; i < dataSz; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
	double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };

	for (i = 0; i < 4; ++i)
	{
		int* pDataSrc, * pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int*)malloc(sizeof(int) * dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n", dataSz);
		printf("---------------------------\n");

		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//printf("%d %d", end, start);
		printf("\truntime\t\t\t: %.5lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.5lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}

}

