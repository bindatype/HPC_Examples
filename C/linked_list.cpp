#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct blob {
	struct blob *next;
	struct blob *prev;
	int value; 
} ;


int main(int argc, char **argv) {

	struct blob a;
	a.prev = NULL;
	a.next = NULL;
	struct blob b;
	b.prev = NULL;
	b.next = NULL;
	struct blob c;
	c.prev = NULL;
	c.next = NULL;

	a.next = &b;
	b.next = &c;
	
	b.prev = &a;
	c.prev = &b;

	struct blob *p;

	p = &a;
	
	int count = 0;
	do {
		p->value = count++; 
		cout << "Value pointed at: "<<p->value<<endl;
		p = p->next;
	} while ( NULL != p->next);

	struct blob d;
	d.prev = NULL;
	d.next = NULL;	

	d.prev = &a;
	d.next = &b;

	a.next = &d;
	b.prev = &d;

	d.value = 100; 

	p = &a;
	count = 0;
	do {
		cout << "Value pointed at: "<<p->value<<endl;
		p = p->next;
	} while ( NULL != p->next);



	return 0;
}

