#include<iostream>
using namespace std;

typedef char Element;
typedef struct LNode* list;
struct LNode {
	Element data;
	list next;
};

void Stack(list* top);
void Pop(list top);
Element Top(list top);
void Push(list top, Element e);

int main() {

	return 0;
}

void Stack(list* top) {
	*top = (list)malloc(sizeof(struct LNode));
	(*top)->next = NULL;
}

bool IsEmpty(list top) {
	if (top->next == NULL) {
		return 1;
	}
	return 0;
}

void Pop(list top){
	if (IsEmpty(top)){
		cout << "Õ»Îª¿Õ" << endl;
	}
	list p;
	p = top->next;
	top->next = top->next->next;
	free(p);
}
Element Top(list top) {
	Element t = top->data;
	return t;
}

void Push(list top, Element e) {
	list p = (list)malloc(sizeof(struct LNode));
	p->data = e;
	p->next = top->next;
	top->next = p;
}