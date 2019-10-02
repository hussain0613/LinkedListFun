#include<stdio.h>
#include<stdlib.h>

struct Element{
	int val;
	int vindex;
	struct Element *prev;
	struct Element *next;
};


typedef struct Element el;


void append(int val, el **head, el **tail, int *lenp);
int __insert__(int val, int index, el **head, el **tail, el *next, int *lenp);
void insert(int val, int index, el **head, el **tail, int *lenp);
void del(int index, el **head, el **tail, int *lenp);


void selfLinkSwap(el **e);
void physicalSwap(el **e1, el **e2);
//void valueSwap(el **e1, el **e2);
//void swap(el **e1, el **e2);
//void swap2(el **e1, el **e2);// for sorting

void sort(el **head, el **tail, int len);

void reasign(int index, int val, el **head, el **tail, int len);

void reverse(el **head, el **tail);
el* find(int index, el *head, int len);
void show(el *head, int rev);


int main()
{
	int i, len, val, index;
	char inp;
	el *head, *tail, *current;
	head = NULL; tail = NULL;
	
	
	int flag = 1;
	len = 0;
	while(flag)
	{
		printf("Enter Choice: ");
		scanf("%c", &inp);
		getchar();
		switch(inp)
		{
			case 'A':{
				scanf("%d", &val);
				getchar();
				
				append(val, &head, &tail, &len);
				
				show(head, 0);
				
				break;
			}
			case 'I':{
				scanf("%d%d", &index, &val);
				getchar();
				insert(val, index, &head, &tail, &len);
				show(head, 0);
				break;
			}
			case 'D':{
				scanf("%d", &index);
				getchar();
				del(index, &head, &tail, &len);
				show(head, 0);
				break;
			}
			case 'F':{
				scanf("%d", &index);
				getchar();
				current = find(index, head, len);
				if(current)
					printf("%d-> %d\n", index, current->val);
				else
					printf("Index out of range!\n");
				show(head, 0);
				break;
			}
			case 'r':{
				show(tail, 1);
				break;
			}
			case 'R':{
				reverse(&head, &tail);
				show(head, 0);
				break;
			}
			case 'S':{
				sort(&head, &tail, len);
				show(head, 0);
				break;
			}
			case 'a':{
				scanf("%d%d", &index, &val);
				getchar();
				reasign(index, val, &head, &tail, len);
				show(head, 0);
				break;
			}
			case 'L':{
				printf("%d\n", len);
				break;
			}
			case 's':{
				show(head, 0);
				break;
			}
			case 'T':{
				printf("Terminating...");
				flag = 0;
				break;
			}
			default:{
				printf("Invalid input! Try again.\n");
				break;
			}
		}
		printf("\n");
	}
	
	
	return 0;
}


void append(int val, el **head, el **tail, int *lenp) //if it is a simple pointer, tail shob thikase... 
													// khali ekta shomoshsha... outside tail change hoy na...
													// because this tail is just a pointer to the tail element of the array, 
													//not a pointer to the special tail variable
{
	el *temp;
	temp = (el*) malloc(sizeof(el));
	//printf("in append: temp has been created\n");
	
	temp->val = val;
	temp->next = NULL;
	
	
	if (*head) // working with the previous element if exists
	{
		(*tail)->next = temp;
		temp->prev = *tail;
		temp->vindex = (*tail)->vindex+1;
	}
	else
	{
		temp->prev = NULL;
		temp->vindex = 0;
		*head = temp;
	 }
	
	*tail = temp; //changing the tail outside tail variable
	++(*lenp);
}



int __insert__(int val, int index, el **head, el **tail, el *next, int *lenp)
{
	el *prev, *temp;
	
	
	if(index > *lenp || index < 0){
		printf("in __insert__: Index out of range!\n");
		return 0;
	}
	
	if(index == *lenp){ // last element adding
		append(val, head, tail, lenp);
		return 1;
	}
	
	//next = find(index, *head, *lenp);
	prev = next->prev;
	
	temp = (el*) malloc(sizeof(el));
	
	temp->val = val;
	temp->vindex = index;
	
	temp->next = next;
	temp->prev = prev;
	
	next->prev = temp;
	next->vindex = index+1;
	
	if(prev) prev->next = temp; // prev thakle... orthat 0 er upore hoile
		
	else *head = temp; // prev na thakle... orthat 0 hoile / changing the outside first element
	
	//++(*lenp);
	return 1;
	
}


void insert(int val, int index, el **head, el **tail, int *lenp)
{
	
	el *next = find(index, *head, *lenp);
	(*lenp) += __insert__(val, index, head, tail, next, lenp);
}



void del(int index, el **head, el **tail, int *lenp)
{
	int len = *lenp;
	el *temp, *prev, *next;
	
	
	if(index>=len || index<0){
		printf("del: Index out of range!\n");
		return;
	}


	if(!index){
		temp = (*head)->next;
		free(*head);
		*head = temp;
		(*head)->prev = NULL;
	} 
	else if(index == len-1){
		temp = (*tail)->prev;
		free(*tail);
		*tail = temp;
		(*tail)->next = NULL;
	}
	else{
		temp = find(index, *head, len);
		prev = temp->prev;
		next = temp->next;
		prev->next = next;
		next->prev = prev;
		free(temp);
	}
	(*lenp)--;
}


void valueSwap(el **e1, el **e2)
{
	int temp;
	temp = (*e1)->val;
	(*e1)->val = (*e2)->val;
	(*e2)->val = temp;
}

void physicalSwap(el **e1, el **e2)
{
	el *temp;
	temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

void selfLinkSwap(el **e)
{
	el *temp;
	
	temp = (*e)->next;
	(*e)->next = (*e)->prev;
	(*e)->prev = temp;
	
}


void reverse(el **head, el **tail)
{
	el *p, *temp, *temp2;
	
	for(p = (*head)->next; p->next;){ // head er porerta theike tail er ager ta porjonto
		temp = p;
		p = p->next;
		selfLinkSwap(&temp);
	}
	
	
	selfLinkSwap(head);
	selfLinkSwap(tail);
	
	physicalSwap(head, tail);
	
}

void sort(el **head, el **tail, int len)
{
	el *p, *q, *key, *pprev, *pnext, *next;
	int i, j;
	
	for(p = (*head)->next, i = 1; p; p = p->next, i++)
	{
		q = p->prev;
		next = p;
		pprev = p->prev;
		pnext = p->next;
		j = i - 1;
		while (q && (q->val > p->val))
		{
			q = q->prev;
			j--;
			if(!(q)){
				next = next->prev;
				break;
			}
			next = q->next;
		}
		
		if(j == i-1) continue;
		__insert__(p->val, j+1, head, tail, next, &len);
		
		pprev->next = p->next;
		if(pnext)
			pnext->prev = p->prev;
		else
			(*tail) = pprev;
	}
}



void reasign(int index, int val, el **head, el **tail, int len)
{
	el *current = find(index, *head, len);
	if (current) current->val = val;
	else{
		printf("reassign: Index out of range!\n");
	}
}



el* find(int index, el *head, int len)
{
	if(index>=len || index<0){
		//printf("find: Index out of range!\n");
		return NULL;
	}
	
	int i;
	el *p;
	p = head;
	for(i=0; i<index; i++) p = p->next;
	
	return p;
	
}


void show(el *start, int rev)
{
	el *p;
	if(rev) for(p = start; p; p = p->prev) printf("%d  ", p->val);
	else for(p = start; p; p = p->next) printf("%d  ", p->val);
	printf("\n");
}


