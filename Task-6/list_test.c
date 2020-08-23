#include <stdio.h>
#include <stdlib.h>
#include "List.h"


void PrintList(List_t *list) {
	Node_t *curNode;
	if (list == NULL) {
		return;
	}
	curNode = GetHead(list);
	printf("[%u] ", GetSize(list));
	while (curNode != NULL) {
		printf("%i", *(int*)GetData(curNode));
		curNode = GetNext(curNode);
	}
	printf("\n");
}

int Equal(const int *first, const int *second)
{
	return *first == *second;
}


int main()
{

	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	List_t *list;
	Node_t *curNode, *nodeForDelete;
	int i;
	printf("Create list \n");
	list = CreateList();
	PrintList(list);

	printf("Insert \n");
	for (i = 1; i >= 0; i--) {
		PushFront(list, &arr[i], sizeof(arr[i]));
		PrintList(list);
	}

	for (i = 2; i < 4; i++) {
		PushBack(list, &arr[i], sizeof(arr[i]));
		PrintList(list);
	}

	PushAfter(list, GetHead(list), &arr[4], sizeof(arr[4]));
	PrintList(list);

	PushBefore(list, GetBack(list), &arr[5], sizeof(arr[5]));
	PrintList(list);

	PushAfter(list, GetNext(GetHead(list)), &arr[6], sizeof(arr[6]));
	PrintList(list);

	PushBefore(list, GetPrev(GetBack(list)), &arr[7], sizeof(arr[7]));
	PrintList(list);

	printf("Delete \n");
	for (i = 0; i < 2; i++) {
		PopFront(list);
		PrintList(list);
	}

	for (i = 0; i < 2; i++) {
		PopBack(list);
		PrintList(list);
	}

	curNode = GetHead(list);
	DeleteNode(list, &curNode);
	PrintList(list);

	curNode = GetHead(list);
	DeleteNode(list, &curNode);
	PrintList(list);

	for (i = 0; i < 4; i++) {
		PushBack(list, &arr[i], sizeof(arr[i]));
	}
	PrintList(list);

	curNode = GetNext(GetHead(list));
	for (i = 0; i < 2; i++) {
		nodeForDelete = curNode;
		curNode = GetNext(curNode);
		DeleteNode(list, &nodeForDelete);
		PrintList(list);
	}

	DeleteList(&list);

	printf("new List \n");
	list = CreateList();
	for (i = 0; i < 7; i++) {
		PushBack(list, &arr[i], sizeof(arr[i]));
	}
	PrintList(list);

	printf("Search %i \t", arr[3]);
	curNode = LinearFindNode(list, &arr[3], (int(*) (const void *, const void *))Equal);
	if (curNode) {
		printf("find: %i", *(int*)GetData(curNode));
	}
	else {
		printf("find: nothing");
	}
	printf("\nSearch %i \t", arr[8]);
	curNode = LinearFindNode(list, &arr[8], (int(*) (const void *, const void *))Equal);
	if (curNode) {
		printf("find: %i", *(int*)GetData(curNode));
	}
	else {
		printf("find: nothing");
	}
	printf("\n");
	printf("Search list`s head data \t\t");
	curNode = LinearFindNode(list, GetData(GetHead(list)), (int(*) (const void *, const void *))Equal);
	printf("%u = %u", (size_t)GetHead(list), (size_t)curNode);

	printf("\nSearch list`s tail data \t\t");
	curNode = LinearFindNode(list, GetData(GetBack(list)), (int(*) (const void *, const void *))Equal);
	printf("%u = %u", (size_t)GetBack(list), (size_t)curNode);


	printf("\nBad case\n");
	GetData(NULL);
	GetNext(NULL);
	GetPrev(NULL);
	GetHead(NULL);
	GetBack(NULL);
	SetData(NULL, NULL, sizeof(int));
	curNode = GetHead(list);
	DeleteNode(list, &curNode);
	DeleteNode(list, &curNode);
	DeleteList(&list);
	DeleteList(&list);

	return 0;
}




#pragma once
