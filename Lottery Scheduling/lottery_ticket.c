#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int no_tickets = 0;

struct node{
	int ticket_start;
	int ticket_end;
	int process;
	struct node *next;
};

void add_process(struct node **root){
	int i = 2;
	if(*root == NULL){
		struct node *temp = (struct node *) malloc (sizeof(struct node));
		temp->ticket_start = 1;
		temp->ticket_end = rand() % 10 + 1;
		temp->next = NULL;
		temp->process = 1;
		printf("The ticket count of process %d is %d - %d\n", temp->process, temp->ticket_start, temp->ticket_end);		//Generate number of tickets the process has
		
		*root = temp;
		no_tickets += temp->ticket_end;
	}else{
		struct node *ptr = *root;
		struct node *temp = (struct node *) malloc (sizeof(struct node));
		while(ptr->next != NULL){
			i++;
			ptr = ptr->next;
		}
		temp->next = NULL;
		temp->process = i;
		temp->ticket_start = no_tickets + 1;
		temp->ticket_end = no_tickets + rand() % 10 + 1;
		printf("The ticket count of process %d is %d - %d\n", temp->process, temp->ticket_start, temp->ticket_end);
		
		ptr->next = temp;
		no_tickets = temp->ticket_end;
	}
}

void delete_process(struct node **root, struct node *ptr){
	int gap;
	if(ptr == (*root)){
		gap = (ptr->ticket_end - ptr->ticket_start) + 1;		//Used for renumbering the ticket_start and ticket_end of the next processes.
		while(ptr != NULL){
			ptr->ticket_start -= gap;
			ptr->ticket_end -= gap;
			ptr = ptr->next;
		}
		printf("Process %d has been deleted\n", (*root)->process);
		ptr = *root;
		(*root) = ptr->next;
		free(ptr);
	}else{
		int temp = ptr->process;
		ptr = *root;
		while(ptr->next->process != temp){
			ptr = ptr->next;
		}
		struct node *del = ptr->next;
		ptr->next = del->next;
		gap = (del->ticket_end - del->ticket_start) + 1;
		free(del);
		printf("Process %d has been deleted\n", temp);
		
		ptr = ptr->next;
		while(ptr != NULL){
			ptr->ticket_start -= gap;
			ptr->ticket_end -= gap;
			ptr = ptr->next;
		}
		
	}
	//Prints the remaining processes
	struct node *rover = *root;
	printf("\nThe remaining processes are:\n");
	while(rover != NULL){
		printf("Process %d has ticket count %d - %d\n", rover->process, rover->ticket_start, rover->ticket_end);
		rover = rover->next;
	}
	no_tickets -= gap;
	printf("\nThe maximum ticket count is %d\n", no_tickets);
	printf("-----------------------------------------");
}

void process_processes(struct node **root){
	struct node *ptr = *root;
	int i = 1, j = 0;
	while(ptr->next != NULL){				//Counts how many processes are needed to be done
		ptr = ptr->next;
		i++;
	}
	while(j < i){
		ptr = *root;
		int number = rand() % no_tickets + 1;
		printf("\nThe winner is %d\n", number);
		
		while(!(number >= ptr->ticket_start && number <= ptr->ticket_end)){
			ptr = ptr->next;
		}
			//once node with the ticket count is found
		printf("Process %d is being processed\n", ptr->process);
		delete_process(root, ptr);
		j++;
	}
	printf("\nAll processes have been processed\n");
	
}

int main(){
	struct node **root = (struct node **) malloc(sizeof(struct node *));
	*root = NULL;

	int i;
	
	srand(time(NULL));
	for(i = 0; i < 5; i++){
		add_process(root);
	}
	
	printf("\nThe total number of tickets right now is %d\n", no_tickets);		//Prints out the total number of tickets after adding all of the processes
	
	process_processes(root);
}