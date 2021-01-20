#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    Node *next;
};


typedef struct Node Node;


class List
{
private:
    Node *head, *tail;
    int length;

public:
    List()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }
    Node* begin();
    Node* end();
    int size();

    Node *get_node(int index);
    int get_value(int index);

    void print();

    void push_back(int value);
    void push_front(int value);

    void insert(int value, int index);
    void sorted_insert(int value);
    void remove(int index);

    void insert(int value, int index, Node *start_from, int offset);
    void remove(int index, Node *start_from, int offset);

    void sort();
    void reverse();
};



int main()
{
    List lst = List();
    for(int i = 0;i<5; ++i){
        lst.push_back(i);
    }
    lst.print();

    for(int i = 0;i<5; ++i){
        lst.push_front(i);
    }
    lst.print();

    lst.insert(25, 0);
    lst.insert(25, 6);
    lst.insert(25, lst.size());
    lst.print();

    lst.remove(6);
    lst.print();

    //lst.remove(0);
    //int *temp =
    lst.remove(3, NULL, -1);
    printf("sp remove: ");
    lst.print();
    lst.remove(lst.size()-1);
    lst.print();

    lst.insert(16, 5);
    lst.print();


    lst.push_back(-25);
    printf("after latest push back: ");
    lst.print();

    lst.sort();
    printf("after sorting: ");
    lst.print();

    /*lst.sorted_insert(-5);
    lst.sorted_insert(50);
    lst.sorted_insert(10);
    lst.print();*/

    lst.reverse();
    printf("after reversing: ");
    lst.print();

    return 0;
}

Node* List::get_node(int index)
{
    if(index<0 || index > length) {
        printf("invalid index while getting node! exiting...");
        exit(5);
    }
    int i = 0;
    Node *cn;
    for(cn = head; cn!= NULL && i<index; cn=cn->next, ++i);
    return cn;
}

int List::get_value(int index)
{
    return get_node(index)->value;
}

Node* List::begin()
{
    return head;
}
Node* List::end()
{
    return tail;
}

int List::size()
{
    return length;
}

void List::print()
{
    for(Node *cn = head; cn!=NULL; cn=cn->next){
        printf("%d ", cn->value);
    }
    printf("\n");
}


void List::push_back(int value)
{
    Node * newNode = (Node *) malloc(sizeof(Node));
    if(tail){
        tail->next = newNode;
        tail = newNode;
    }
    else{
        tail = newNode;
        head = tail;
    }

    tail->value = value;
    tail->next = NULL;
    ++length;
}



void List::push_front(int value)
{
    if(head){
        Node *temp = (Node *) malloc(sizeof(Node));
        temp->value = value;
        temp->next = head;
        head = temp;
    }else{
        return push_back(value);
    }
    ++length;
}


void List::insert(int value, int index, Node *start_from, int offset)
{
    if(index<0 || index > length) {
        printf("invalid index while inserting! exiting...");
        exit(5);
    }
    if(index == 0) return push_front(value);
    else if(index == length) return push_back(value);
    else{
        if(!start_from || offset<0){
            start_from = head;
            offset = 0;
        }

        int i = offset;
        Node *cn;
        for(cn = start_from; cn!= NULL && i<index-1; cn = cn->next, ++i);
        Node *temp = (Node *) malloc(sizeof(Node));
        temp->value = value;
        temp->next = cn->next;
        cn->next = temp;
        ++length;
    }
}

void List::insert(int value, int index)
{
    insert(value, index, head, 0);
}

void List::remove(int index, Node *start_from, int offset)
{
    if(index<0 || index >= length) {
        printf("invalid index (%d) while removing! exiting...", index);
        exit(5);
    }
    if(index == 0){
        Node *temp = head;
        head = head->next;
        free(temp);
        --length;
    }
    else{
        if(!start_from || offset<0){
            start_from = head;
            offset = 0;
        }
        int i = offset;
        Node *cn;
        for(cn = start_from; cn!= NULL && i<index-1; cn = cn->next, ++i);
        Node *temp = cn->next;
        cn->next = temp->next;
        if(temp == tail) tail = cn;
        free(temp);
        --length;
    }
}

void List::remove(int index)
{
    remove(index, head, 0);
}

void List::sort()
{
    int j = 1;
    Node *prev=head;
    for(Node *cn = head->next; cn != NULL; cn = cn->next){
        int key = cn->value;
        Node *cn2;
        int i = 0;
        Node *prev2 = NULL;
        for(cn2 = head; cn2 != cn; cn2 = cn2->next){
            if(key <= cn2->value){
                cn = prev;//cn->next;
                remove(j, prev, j-1); // optimize korte hobe with nodes
                insert(key, i, prev2, i-1); // optimize korte hobe with nodes
                break;
            }
            prev2 = cn2;
            ++i;
        }
        //if(i==j) cn= cn->next;
        prev = cn;
        ++j;
    }
}

void List::reverse()
{
    if(length == 0) return;
    int key;
    int i= 0;
    Node *prev = head;
    for(Node *cn = head->next; cn!= NULL;cn = cn->next){
        key = cn->value;
        cn = prev;
        remove(i, prev, i-1);
        push_front(key);
        ++i;
        prev = cn;
    }
}

void List::sorted_insert(int value)
{
    if(!head) return push_front(value);
    Node * newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    Node *cn = head, *prev = NULL;
    for(;cn!=NULL; cn=cn->next){
        if(value<=cn->value) break;
        prev = cn;
    }
    newNode->next = cn;
    if(cn == head) head = newNode;
    else prev->next = newNode;
    ++length;
}

