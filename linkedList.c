#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int data;
	struct Node* next;	
}Node;

void printList(Node*head){
	int hold;
	if(head != NULL){
		printf("%d\t",head->data);
		hold = head->data;
		for(Node*ptr = head; ptr != NULL; ptr = ptr->next){
			if(hold != ptr->data){
				printf("%d\t",ptr->data);
			}
			hold = ptr->data;
		}
	}
	printf("\n");
}

Node* spawn(int value){
	Node *newNode = malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;
	return newNode;
}
Node* spawnW(int value, Node*link){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = link;
	return newNode;
}
void insert(Node** head, int value){
	
	if((*head)==NULL){
		*head = spawn(value);
	}else{
		Node*slow = NULL;
		for(Node*fast = *head; fast != NULL;  fast = fast->next){
			if(value<=fast->data && slow == NULL){
				*head = spawnW(value,(*head));
				break;
			}else if(fast->next == NULL && value>=fast->data){
				fast->next = spawn(value);
				break;
			}else if( slow!= NULL && value>= slow->data && value<= fast->data){
				slow->next = spawnW(value,slow->next);
				break;
			}else{
				slow = fast;
			}
		}
	}
}

void rem(int target, Node**head){
	if((*head) != NULL){
		if((*head)->data == target){
			Node*del = *head;
			*head = (*head)->next;
			del->next = NULL;
			free(del);
			
		}else{
			Node*slow = NULL;
			for(Node*ptr = *head; ptr!=NULL; ptr = ptr->next){
				if(ptr->data == target){
					slow->next = ptr->next;
					ptr->next = NULL;
					free(ptr);
					break;
				}
				slow = ptr;
			}
		}
	}
}

void deref(Node**head){
	Node*p;
	Node*store;
	p = *head;
	while(p!=NULL){
		store = p->next;
		free(p);
		p= store;
	}
}

int main(int argc, char* argv[]){

	FILE* fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("error\n");
	}else{
		Node*head = NULL;
		char character;
		int data;
		int scan;
		int count = 0;
		while(!feof(fp)){
			scan = fscanf(fp,"%c\t%d\n",&character,&data);
			if(scan != 2){
				break;
			}
			if(character == 'i'){
				insert(&head, data);
				count++;
			}else {
				rem(data, &head);
			}
		}
		printf("%d\n",count);
		printList(head);
		deref(&head);
		fclose(fp);
	}

	return 0;
}









