/***********************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 07/09/2023
Description : The code takes in 1 file with integers seperated by a blank space.
			  Adds the integers in the file onto a linked list.
			  Sorts out the linked list using quicksort.
			  Prints the sorted integers seperated by blank spaces.

***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>


struct list {              // Declaring the linked list.
	int data;
	struct list* next;
};

void swap(int* a, int* b);               // Swaps the value of the 2 pointer inputs. 

void quicksort(struct list* start, struct list* end);     // Performs the quicksort recursively


int main(int argc, char* argv[]) {
	FILE* fptr = fopen(argv[1], "r");
	int buf;
	struct list* start = NULL;


	while (fscanf(fptr, "%d", &buf) != EOF){
		struct list* new_ele = (struct list*)malloc(sizeof(struct list));
		new_ele->data = buf;
		new_ele->next = start;
		start = new_ele;
	}


	struct list* fetch = start;
	while (fetch->next != NULL)
		fetch = fetch->next;

	quicksort(start, fetch);

	struct list* current = start;
	while(current->next != NULL){
		printf("%d ", current->data);
		current = current->next;
	}


	fclose(fptr);
	return 0;
}



void quicksort(struct list* head, struct list* end){
	if (head != end){

		struct list* pivot = head;

		struct list* startofsecond = head->next;
		struct list* endoffirst = head;

		struct list* cur2 = head->next;
		struct list* endofsecond = head;

		while(cur2->next != NULL){

			if(pivot->data > cur2->data){
				swap(&startofsecond->data, &cur2->data);

				startofsecond = startofsecond->next;
				endoffirst = endoffirst->next;
			}

			cur2 = cur2->next;
			endofsecond = endofsecond->next;
		}

		swap(&endoffirst->data, &head->data);

		quicksort(pivot, endoffirst);
		quicksort(startofsecond, endofsecond);
	}
}



void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}