#include<stdio.h>
#include<stdlib.h>


struct Node
{
	int data;
	struct Node *prev, *next;
};


struct Node* create_node(int data)
{
	struct Node *new_node = (struct Node*)(malloc(sizeof(struct Node)));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}


void push(struct Node **headref, int data)
{
	if(*headref == NULL)
	{
		struct Node *new_node = create_node(data);
		*headref = new_node;
		return;
	}

	struct Node *new_node = create_node(data);
	new_node->next = *headref;
	(*headref)->prev = new_node;
	*headref = new_node;
}


void insert_after(struct Node *head, int key, int data)
{
	if(head == NULL)
	{
		printf("List is empty, cannot find the given key\n");
		return;
	}

	while(head->next != NULL && head->data != key)
		head = head->next;

	struct Node *new_node = create_node(data);
	new_node->next = head->next;
	head->next = new_node;
	new_node->prev = head;

	if(new_node->next != NULL)
		new_node->next->prev = new_node;
}


void append(struct Node **headref, int data)
{
	struct Node *last = *headref;

	if(*headref == NULL)
	{
		push(headref, data);
		return;
	}

	while(last->next != NULL)
		last = last->next;

	struct Node *new_node = create_node(data);
	last->next = new_node;
	new_node->prev = last;
}


int get_count(struct Node *head)
{
	int count = 0;
	while(head)
	{
		head = head->next;
		count++;
	}

	return count;
}


void delete(struct Node **headref, int key)
{
	if(*headref == NULL)
	{
		printf("List is empty. Insert some elements into the linked list using the Insertion menu.\n");
		return;
	}

	struct Node *current = *headref;

	if(current->data == key)
	{
		int count = get_count(current);
		if(count != 1)
		{
			current->next->prev = NULL;
			*headref = current->next;
		}
		else
		{
			*headref = NULL;
			printf("List is empty now");
		}

		free(current);
		return;
	}

	while(current != NULL && current->data != key)
		current = current->next;

	if(current == NULL)
	{
		printf("Element %d not found in the linked list\n", key);
		return;
	}

	current->prev->next = current->next;
	if(current->next != NULL)
		current->next->prev = current->prev;
	free(current);

}


void reverse(struct Node **headref)
{
	struct Node *head = *headref;

	if(head == NULL)
	{
		printf("Cannot reverse an empty list\n");
		return;
	}

	struct Node *next = NULL;

	while(head->next != NULL)
	{
		next = head->next;
		head->next = head->prev;
		head->prev = next;
		head = next;
	}

	next = head->next;
	head->next = head->prev;
	head->prev = next;

	*headref = head;
}


void print_list(struct Node *head)
{
	int c=0;

	if(head == NULL)
	{
		printf("There are no elements in the current linked list. Please put some elements onto the linked list by using Insertion menu\n");
		return;
	}

	while(head != NULL)
	{
		if(c==0)
		{
			printf("%d",head->data);
			c++;
		}

		else
			printf("<=>%d", head->data);

		head = head->next;
	}
	printf("\n\n");
}


int main()
{
	struct Node *head = NULL, *head1 = NULL, *head2 = NULL;

	int ele, prev_node_data, ch1, ch2, pos, count, val1, val2;
	while(1)
	{
		loop1: printf("\n1. Insertion\n2. Deletion\n3. Count the elements in the list\n4. Reverse the doubly linked list\n5. Quit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch1);
		switch(ch1)
		{
			case 1: 	while(1)
						{
							printf("\n\nInsertion Menu");
							printf("\n1. Insertion at the head of linked list\n2. Inserion at the tail of linked list\n3. Insertion after a specified position in linked list\n4. Insert all the elements in one go\n5. Stop insertion\n");
							printf("Enter your choice: ");
							scanf("%d", &ch2);
							switch(ch2)
							{
								case 1: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											push(&head, ele);
											printf("Current Linked list:\t");
											print_list(head);
											break;

								case 2: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											append(&head, ele);
											printf("Current Linked list:\t");
											print_list(head);
											break;

								case 3: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											printf("\nEnter the element after which you want to insert the new element: ");
											scanf("%d", &prev_node_data);
											insert_after(head, prev_node_data, ele);
											if(head != NULL)
											{	
												printf("Current Linked list:\t");
												print_list(head);
											}
											break;

								case 4:		printf("Enter the elements of the linked list (enter -1 to stop insertion):\t");
											while(1)
											{
												scanf("%d", &ele);
												if(ele == -1)
													break;
												append(&head, ele);

											}

								case 5: 	if(head == NULL)
												goto loop1;
											else
											{
												printf("Created list is:\t");
												print_list(head);
												goto loop1;
											}

								default : 	printf("Wrong option inserted. Choose again.\n");
							}

						}

			case 2: 	while(1)
						{
							printf("\nDeletion Menu");
							printf("\n1. Delete a specific element\n2. Stop Deletion\n");
							printf("Enter your choice: ");
							scanf("%d", &ch2);
							switch(ch2)
							{
								case 1:		printf("Enter the element to be deleted: ");
											scanf("%d", &ele);
											delete(&head, ele);
											if(head != NULL)
											{
												printf("Current Linked list:\t");
												print_list(head);
											}
											break;

								case 2: 	if(head != NULL)
											{
												printf("Current Linked list:\t");
												print_list(head);
											}
											goto loop1;

								default:	printf("Wrong option inserted, Choose again\n");
							}	
						}


			case 3: 	count = get_count(head);
						printf("\nNumber of elements in the current linked list: %d", count);
						break;


			case 4:		printf("Current list\t");
						print_list(head);
						reverse(&head);
						printf("After Reversal:\t");
						print_list(head);
						break;

			case 5:		exit(1);

			default : 	printf("You have entered a wrong number. Please choose again\n");
		}
	}

	return 0;
}