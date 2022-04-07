#include <stdio.h>
#include <stdlib.h>
#define space 10000

typedef struct Node{
	int data;
	struct Node*next;
}Node;

void printLink(Node*head){
	for(Node*ptr = head; ptr!=NULL; ptr = ptr->next){
		printf("%d--> ", ptr->data);
	}
	printf("\n");
}
typedef struct Hashtable{

	int collisions;
	int succesful;
	Node**entries;
	
}Hashtable;

Hashtable* create(){
	struct Hashtable*list = malloc(sizeof(Hashtable));
	list->collisions = 0;
	list->succesful = 0;
	list->entries = malloc(sizeof(Node)*space);

	for(int i = 0; i < space; i++){
		list->entries[i] = NULL;
	}

	return list;
}

Node* spawn(int value){
	Node *newNode = malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;
	return newNode;
}
Node* spawnW(int value, Node**link){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = *link;
	return newNode;
}
int hash(int key){
	int statement = key%space;
	if(statement < 0){
		return (space + statement);
	}
	return statement;
}

int search(int data, Hashtable*list){

	int index = hash(data);
	for(Node*head = list->entries[index];head != NULL; head = head->next){
		if(head->data == data){
			list->succesful++;
			return 1;
		}
	}
	return 0;
}

void add(int data, Hashtable*list){
	int index = hash(data);
	// printf("%d\n",index );
	Node*head = list->entries[index];
	// printf("I made it past the head\n");
	if(head == NULL){
		// printf("node at an index is Null\n");
		head = spawn(data);
		// printLink(*head);
		list->entries[index] = head;
	}else{
		// printf("adding to the middle\n");
		list->collisions++;
		int boo = search(data,list);
		if(boo != 1){
			Node*temp = head->next;
			head->next = spawnW(data,&temp);
			list->entries[index] = head;
		}else{
			list->succesful--;
		}

		
	}	
}

void unchain(Node*head){
	Node*p;
	Node*store;
	p = head;
	while(p!=NULL){
		store = p->next;
		free(p);
		p= store;
	}
	// if(ptr->next == NULL){
	// 	free(ptr);
	// 	return;
	// }
	// unchain(ptr->next);
}

void deref(Hashtable*list){
	for(int i = 0; i < space; i++){

		if(list->entries[i]==NULL){
			free(list->entries[i]);
			continue;
		}else{
			unchain(list->entries[i]);
		}	
	}
}

void traverse(Hashtable*list){
	for(int i = 0; i < space; i++){
		printf("index %d\t",i);
		for(Node*ptr = list->entries[i]; ptr != NULL; ptr = ptr->next){
			printf("%d--> ",ptr->data);
		}
		printf("\n");
	}
}


int main(int argc, char* argv[]){

	FILE*fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("error");
	}else{

		Hashtable*list = create();
		char character;
		int data;
		int scan;
		while(!feof(fp)){
			// printf("top of the forloop\n");
			scan = fscanf(fp,"%c\t%d\n",&character,&data);
			if(scan != 2){
				continue;
			}
			if(character == 'i'){
				// printf("adding\n");
				add(data,list);
				// printf("Woo, we can add\n");
			}else{
				search(data,list);
			}
		}
		printf("number of collisions:  %d\n",list->collisions);
		printf("number of searches: %d\n", list->succesful);
		// traverse(list);
		deref(list);
		free(list->entries);
		free(list);
	}
	return 0;
}


