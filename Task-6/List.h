#pragma once 

typedef struct Node_t { 
struct Node_t* next; 
struct Node_t* prev; 
size_t sizeofData; 
void* data; 
} Node_t; 

typedef struct List_t { 
struct Node_t* head; 
struct Node_t* tail; 
size_t size; 
} List_t; 

// Получить указатель на данные в узле 
// Возвращает указатель на данные или NULL в случае ошибки 
void* GetData(const Node_t *const node); 

// Заменить данные в узле 
// Возвращает указатель на старый узел с новыми данными или NULL в случае ошибки 
Node_t* SetData(Node_t *const node, const void *const newData, const size_t sizeofData); 

// Получить указатель на следующий элемент списка 
// Возвращает указатель на следующий элемент списка или NULL в случае ошибки 
Node_t* GetNext(const Node_t *const node); 

// Получить указатель на предыдущий элемент списка 
// Возвращает указатель на предыдущий элемент списка или NULL в случае ошибки 
Node_t* GetPrev(const Node_t *const node); 

// Создать новый пустой список
// Возвращает указатель на созданный список или NULL в случае ошибки 
List_t* CreateList(); 

// Полное удаление списка 
void DeleteList(List_t** listPtr); 

// Получить указатель на первый элемент списка 
// Возвращает указатель на первый элемент списка или NULL в случае ошибки 
Node_t* GetHead(const List_t *const list); 

// Получить указатель на последний элемент списка 
// Возвращает указатель на последний элемент списка или NULL в случае ошибки 
Node_t* GetBack(const List_t *const list); 

// Создать и вставить новый узел в начало списка 
void PushFront(List_t *const list, const void *const data, const size_t sizeofData); 

// Создать и вставить новый узел в конец списка 
void PushBack(List_t *const list, const void *const data, const size_t sizeofData); 

// Создать и вставить новый элемент после указанного 
void PushAfter(List_t *const list, Node_t *const node, const void *const data, const size_t sizeofData); 

// Создать и вставить новый элемент перед указанным 
void PushBefore(List_t *const list, Node_t *const node, const void *const data, const size_t sizeofData); 

// Удалить начальный узел списка 
void PopFront(List_t *const list); 

// Удалить последний узел списка 
void PopBack(List_t *const list); 

// Удалить узел из списка 
void DeleteNode(List_t *const list, Node_t **nodePtr); 

// Линейный поиск значения в списке 
// Возвращает узел, содержащий данное значение или NULL 
Node_t* LinearFindNode(const List_t *const list, const void *const data, int(*equal)(const void*, const void*)); 

// Получить размер списка 
// Возвращает количество узлов в списке 
size_t GetSize(const List_t *const list); 