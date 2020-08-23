#include <stdlib.h> 
#include <string.h> 
#include "List.h" 

// Создать новый узел 
// Возвращает указатель на новый узел или NULL в случае ошибки 
Node_t* CreateNode(const void *const data, const size_t sizeofData); 

// Освобождить память для узла 
void FreeNode(Node_t **nodePtr); 


List_t* CreateList() { 
List_t *list; 
list = (List_t*)malloc(1 * sizeof(List_t)); 
if (!list) { 
return NULL; 
} 
list->size = 0; 
list->head = NULL; 
list->tail = NULL; 
return list; 
} 

Node_t* CreateNode(const void *const data, const size_t sizeofData) { 
Node_t * newNode; 
newNode = (Node_t*)malloc(1 * sizeof(Node_t)); 
if (!newNode) { 
return NULL; 
} 
newNode->data = (void*)malloc(1 * sizeofData); 
if (!newNode->data) { 
free(newNode); 
return NULL; 
} 
memcpy(newNode->data, data, sizeofData); 
newNode->sizeofData = sizeofData; 
newNode->next = NULL; 
newNode->prev = NULL; 
return newNode; 
} 


void FreeNode(Node_t **nodePtr) { 
Node_t *node; 
if (!nodePtr || !(*nodePtr)) 
return; 
node = *nodePtr; 
if (node->data) { 
free(node->data); 
} 
free(node); 
*nodePtr = NULL; 
} 


void* GetData(const Node_t *const node) { 
if (!node) { 
return NULL; 
} 
return node->data; 
} 


Node_t* SetData(Node_t *const node, const void *const newData, const size_t sizeofData) { 
if (!node) { 
return NULL; 
} 
if (sizeofData != node->sizeofData) { 
return NULL; 
} 
memcpy(node->data, newData, sizeofData); 
return node; 
} 

Node_t* GetNext(const Node_t *const node) { 
if (!node) { 
return NULL; 
} 
return node->next; 
} 

Node_t* GetPrev(const Node_t *const node) { 
if (!node) { 
return NULL; 
} 
return node->prev; 
} 


void DeleteList(List_t** list_ptr) { 
List_t* list; 
Node_t *tmp, *next; 
if (!list_ptr || !(*list_ptr)) { 
return; 
} 
list = *list_ptr; 
tmp = list->head; 
while (tmp) { 
next = tmp->next; 
FreeNode(&tmp); 
tmp = next; 
} 
free(list); 
*(list_ptr) = NULL; 
} 


Node_t* GetHead(const List_t *const list) { 
if (!list) { 
return NULL; 
} 
return list->head; 
} 


Node_t* GetBack(const List_t *const list) { 
if (!list) { 
return NULL; 
} 
return list->tail; 
} 


void PushFront(List_t *const list, const void *const data, const size_t sizeofData) { 
Node_t *newNode; 
if (!list) { 
return; 
} 
newNode = CreateNode(data, sizeofData); 
if (!newNode) { 
return; 
} 
if (list->head) { 
newNode->next = list->head; 
list->head->prev = newNode; 
} 
list->head = newNode; 
if (list->tail == NULL) { 
list->tail = list->head; 
} 
list->size += 1; 
} 

void PushBack(List_t *const list, const void *const data, const size_t sizeofData) { 
Node_t *newNode; 
if (!list) { 
return; 
} 
newNode = CreateNode(data, sizeofData); 
if (!newNode) { 
return; 
} 
if (list->tail) { 
newNode->prev = list->tail; 
list->tail->next = newNode; 
} 
list->tail = newNode; 
if (list->head == NULL) { 
list->head = list->tail; 
} 
list->size += 1; 
} 

// небезопасно, т.к. нет проверк того, есть ли указанный узел в списке или нет (но так вставка за О(1), а с поиском за О(n)) 
void PushAfter(List_t *const list, Node_t *const node, const void *const data, const size_t sizeofData) { 
Node_t *newNode, *prev, *next; 
if (!list || !node) { 
return; 
} 
if (node == list->tail) { 
PushBack(list, data, sizeofData); 
return; 
} 

newNode = CreateNode(data, sizeofData); 
if (!newNode) { 
return; 
} 
prev = node; 
next = node->next; 
prev->next = newNode; 
newNode->prev = prev; 
if (next) { 
next->prev = newNode; 
newNode->next = next; 
} 
list->size += 1; 
} 

// небезопасно, т.к. нет проверк того, есть ли указанный узел в списке или нет (но так вставка за О(1), а с поиском за О(n)) 
void PushBefore(List_t *const list, Node_t *const node, const void *const data, const size_t sizeofData) { 
Node_t *newNode, *prev, *next; 
if (!list || !node) { 
return; 
} 
if (node == list->head) { 
PushFront(list, data, sizeofData); 
return; 
} 

newNode = CreateNode(data, sizeofData); 
if (!newNode) { 
return; 
} 
prev = node->prev; 
next = node; 
if (prev) { 
prev->next = newNode; 
newNode->prev = prev; 
} 
next->prev = newNode; 
newNode->next = next; 
list->size += 1; 
} 


void PopFront(List_t *const list) { 
Node_t *curNode; 
if (!list || !list->head) { 
return; 
} 
curNode = list->head; 
if (list->head == list->tail) { 
list->head = NULL; 
list->tail = NULL; 
} 
else { 
list->head = curNode->next; 
if (list->head) { 
list->head->prev = NULL; 
} 
list->size -= 1; 
} 
FreeNode(&curNode); 
} 


void PopBack(List_t *const list) { 
Node_t *curNode; 
if (!list || !list->tail) { 
return; 
} 
curNode = list->tail; 
if (list->head == list->tail) { 
list->head = NULL; 
list->tail = NULL; 
} 
else { 
list->tail = curNode->prev; 
if (list->tail) { 
list->tail->next = NULL; 
} 
list->size -= 1; 
} 
FreeNode(&curNode); 
} 


// небезопасно, т.к. нет проверк того, есть ли удаляемый узел в списке или нет (но так удаление за О(1), а с поиском за О(n)) 
void DeleteNode(List_t *const list, Node_t **nodePtr){ 
Node_t *prev, *next, *node; 
if (!list || !nodePtr || !(*nodePtr)) { 
return; 
} 
node = *nodePtr; 
if (node == list->head) { 
PopFront(list); 
*nodePtr = NULL; 
return; 
} 
if (node == list->tail) { 
PopBack(list); 
*nodePtr = NULL; 
return; 
} 
prev = node->prev; 
next = node->next; 
if (prev) { 
prev->next = next; 
} 
if (next) { 
next->prev = prev; 
} 
FreeNode(&node); 
*nodePtr = NULL; 
list->size -= 1; 
} 


Node_t* LinearFindNode(const List_t *const list, const void *const data, int(*equal)(const void*, const void*)) { 
Node_t *curNode; 
if (!list) { 
return NULL; 
} 
curNode = list->head; 
while (curNode) { 
if (equal(curNode->data, data)) { 
return curNode; 
} 
curNode = curNode->next; 
} 
return NULL; 
} 

size_t GetSize(const List_t *const list) { 
if (!list) { 
return 0; 
} 
return list->size; 
}