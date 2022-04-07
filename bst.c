#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node*left;
	struct Node*right;
}Node;

void traverse(Node*head){
	if(head == NULL){
		return;
	}
	traverse(head->left);
	printf("%d\t",head->data);
	traverse(head->right);
}

Node* spawn(int data){
	Node*statement = malloc(sizeof(Node));
	statement->data = data;
	statement->left = NULL;
	statement->right = NULL;
	return statement;
}

void add(Node**head,int data){
	if(*head == NULL){
		*head = spawn(data);
		return;
	}

	Node*root = *head;
	int done = 0;
	while(!done){
		if(data == root->data){
			return;
		}
		if(data < root->data){
			if(root->left == NULL){
				root->left = spawn(data);
				done = 1;
			}else{
				root = root->left;
			}
		}else{
			if(root->right == NULL){
				root->right = spawn(data);
				done = 1;
			}else{
				root = root->right;
			}
		}
	}
}

void deref(Node*head){
	if(head == NULL){
		return;
	}
	deref(head->left);
	deref(head->right);
	free(head);

}

int main(int argc, char* argv[]){

	FILE*fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("error\n");
	}else{
		Node*head = NULL;
		char character;
		int data;
		while(!feof(fp)){
			fscanf(fp,"%c\t%d\n",&character,&data);
			if(character == 'i'){
				add(&head,data);
			}
			
		}
		traverse(head);
		printf("\n");
		deref(head);
		
	}
}
