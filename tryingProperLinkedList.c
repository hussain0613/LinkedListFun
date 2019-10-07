#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

struct Value{
	int type: 3;
	union{
		char *ch;
		int i;
		double d;
	}val;
};

typedef struct Value Value;

struct Element{
	//int type: 2;
	Value val;
	struct Element *prev;
	struct Element *next;
};

typedef struct Element El;

struct List{
	El *head;
	El *tail;
	int len;
};

typedef struct List List;



void initialize(List *list);
void print(List list);
void append(Value val, List *list);

El *__get__(int index, List list);
El get(int index, List list);
int isEqual(Value val1, Value val2);
int find(Value value, List list);

int __insert__(Value val, int index, List *list, El *next);
void insert(Value val, int index, List *list);

void del (int index, List *list);
void reasign(Value val, int index, List *list);


int main()
{
	int i;
	Value val;
	El head, tail;
	List list;
	
	
	head.prev = NULL;
	head.val.type = 0;
	head.val.val.ch = "matha";
	head.next = &tail;
	
	
	tail.prev = &head;
	tail.val.type = 0;
	tail.val.val.ch = "i rock";
	tail.next = NULL;
	
	
	initialize(&list);
	list.head = &head;
	list.tail = &tail;
	list.len = 2;
	
	for(i = 0; i < 5; i++){
		val.type = 1;
		val.val.i = i+1;
		append(val, &list);
	}
	
	for(i = 0; i < 5; i++){
		val.type = 2;
		val.val.d = i+1.5;
		append(val, &list);
	}
	
	print(list);
	
	printf("%d\n", list.len);
	
	printf("%d\n", get(5, list).val.val);
	val.type = 2;
	val.val.d = 2.5;
	printf("%d\n", find(val, list));
	
	val.type = 0;
	val.val.ch = "Hello World";
	insert(val, 0, &list);
	print(list);
	printf("\n");
	
	val.type = 0;
	val.val.ch = "Hello World1";
	insert(val, 5, &list);
	print(list);
	printf("\n");
	
	val.type = 0;
	val.val.ch = "Hello World2";
	insert(val, 14, &list);
	print(list);
	printf("\n");
	printf("%d\n", list.len);
	
	del(5, &list);
	print(list);
	printf("%d\n", list.len);
	
	val.type = 1;
	val.val.i = 512;
	reasign(val, 4,&list);
	print(list);
	printf("%d\n", list.len);
	
	return 0;
}



void initialize(List *list)
{
    list->head=NULL;
    list->tail = NULL;
    list->len = 0;
}



void print(List list)
{
	El *current;
	for(current = list.head; current; current = current->next){
		if (current->val.type == 0) printf("%s, ", current->val.val);
		else if (current->val.type == 1) printf("%d, ", current->val.val);
		else printf("%lf, ", current->val.val);
	}
	printf("\n");
}


void append(Value val, List *list)
{
	El *current;
	current = (El*) malloc(sizeof(El));
	
	//current->val.type = type;
	current->val = val;
	current->next = NULL;
	
	if(list->head){
		current->prev = list->tail;
		(list->tail)->next = current;
	}
	else{
		current->prev = NULL;
		list->head = current;
	}
	list->tail = current;
	(list->len)++;
}



El *__get__(int index, List list)
{
	El *current;
	int i;
	
	if(index>=list.len) return NULL;
	
	for(i = 0, current = list.head; i<index && current; i++, current=current->next);
	
	return current;
}

El get(int index, List list)
{
	return *__get__(index, list);
}


int isEqual(Value val1, Value val2)
{
	if(val1.type != val2.type) return 0;
	switch(val1.type)
	{
		case 0:{
			return val1.val.ch == val2.val.ch;
			break;
		}
		case 1:{
			return val1.val.i == val2.val.i;
			break;
		}
		case 2:{
			return val1.val.d == val2.val.d;
			break;
		}
		default:{
			return 0;
			break;
		}
	}
}

int find(Value value, List list)
{
	int i = 0;
	El *current = list.head;
	for(;current && i < list.len;current = current->next, i++){
		if (isEqual(value, current->val)) return i;
	}
	return -1;
}


int __insert__(Value val, int index, List *list, El *next)
{
	if (index > list->len || index < 0){
		printf("In __insert__: index out of range!!\n");
		return 0;
	}
	if (index == list->len){
		append(val, list);
		return 0;
	}
	
	El *current, *prev = next->prev;
	current = (El*) malloc(sizeof(El));
	
	current->val = val;
	current->next = next;
	current->prev = prev;
	
	next->prev = current;
	
	if(prev) prev->next = current;
	else list->head = current;
	return 1;
}


void insert(Value val, int index, List *list)
{
	El *next = __get__(index, *list);
	if(__insert__(val, index, list, next)) (list->len)++;
}

void del (int index, List *list)
{
	if (index >= list->len || index < 0){
		printf("In del: index out of range!!\n");
		return;
	}
	
	El *current, *prev, *next;
	
	if(!index){
		current = list->head;
		list->head = current->next;
		list->head->prev = NULL;
		free(current);
		list->len--;
		return;
	}
	
	if(index == list->len - 1){
		current = list->tail;
		list->tail = current->prev;
		list->tail->next = NULL;
		free(current);
		list->len--;
		return;
	}
	
	current = __get__(index, *list);
	prev = current->prev;
	next = current->next;
	
	prev->next = next;
	next->prev = prev;
	free(current);
	
	list->len--;
}



void reasign(Value val, int index, List *list)
{
	if (index >= list->len || index < 0){
		printf("In reasign: index out of range!!\n");
		return;
	}
	
	El *current;
	
	if(!index){
		list->head->val = val;
		return;
	}
	
	if(index == list->len - 1){
		list->tail->val = val;
		return;
	}
	
	current = __get__(index, *list);
	current->val = val;
}



