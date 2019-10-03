#include<stdio.h>
#include<stdlib.h>

union Value{
	//int type: 2;
	char *ch;
	int i;
	double d;
};

typedef union Value Value;

struct Element{
	int type: 2;
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
void append(Value val, int type, List *list);


int main()
{
	int i;
	Value val;
	El head, tail;
	List list;
	initialize(&list);


	head.prev = NULL;
	head.type = 0;
	head.val.ch = "matha";
	head.next = &tail;


	tail.prev = &head;
	tail.type = 0;
	tail.val.ch = "i rock";
	tail.next = NULL;

    list.head = &head;
    list.tail = &tail;


	for(i = 0; i < 5; i++){
		val.i = i+1;
		append(val, 1, &list);
	}

	print(list);

	printf("%d\n", list.len);

	return 0;
}



void print(List list)
{
	El *current;
	for(current = list.head; current; current = current->next){
		if (current->type == 0) printf("%s, ", current->val);
		else if (current->type == 1) printf("%d, ", current->val);
		else printf("%lf, ", current->val);
	}
	printf("\n");
}


void initialize(List *list)
{
    list->head=NULL;
    list->tail = NULL;
    list->len = 0;
}

void append(Value val, int type, List *list)
{
	El *current;
	current = (El*) malloc(sizeof(El));

	current->type = type;
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


