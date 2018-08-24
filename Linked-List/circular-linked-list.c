#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node *next;
};

struct Node* create_node(int data)
{
	struct Node *new_node = (struct Node*)(malloc(sizeof(struct Node)));
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void push(struct Node **last, int data)
{
	struct Node *new_node = create_node(data);

	if(*last == NULL)
	{
		*last = new_node;
		(*last)->next = new_node;
		return;
	}

	new_node->next = (*last)->next;
	(*last)->next = new_node;
}


void insert_after(struct Node **last, int key, int data)
{

	if(*last == NULL)
	{
		push(last, data);
		return;
	}

	struct Node *current = *last;

	do
		current = current->next;
	while(current != *last && current->data!=key);

	if(current == *last)
	{
		printf("Key %d not found in the list, cannot insert an item after this key\n", key);
		return;
	}

	struct Node *new_node = create_node(data);
	new_node->next = current->next;
	current->next = new_node;
}


void append(struct Node **last, int data)
{
	if(*last == NULL)
	{
		push(last, data);
		return;
	}

	struct Node *new_node = create_node(data);
	new_node->next = (*last)->next;
	(*last)->next = new_node;
	*last = new_node;
}


void print_list(struct Node *last)
{
	int c=0;

	if(last == NULL)
	{
		printf("There are no elements in the current linked list. Please put some elements onto the linked list by using Insertion menu");
		return;
	}

	struct Node *temp = last->next;
	do
	{
		if(c==0)
		{
			printf("Last-Element->%d",temp->data);
			c++;
		}

		else
			printf("->%d", temp->data);

		temp = temp->next;
	}
	while(temp != last->next);
	printf("->First-Element");
	printf("\n\n");
}


int get_count(struct Node **last)
{
	struct Node *current = *last;
	int count = 0;

	do
	{
		current = current->next;
		count++;
	}
	while(current != *last);
	return count;
}


void delete(struct Node **last, int key)
{
	int c = 0;
	if(*last == NULL)
	{
		printf("List is empty. Please insert some elements first\n");
		return;
	}

	if((*last)->data == key)
		c = 1;

	struct Node *current = *last, *prev = NULL;
	do
	{
		prev = current;
		current = current->next;
	}
	while(current != *last && current->data != key);

	if(current == *last)
	{	

		if(!c)
		{
			printf("Key %d not found in the list\n", key);
			return;
		}

		else
		{
			if(get_count(last) == 1)
			{
				*last = NULL;
				free(prev);
				printf("List is empty now, please insert some elements\n");
				return;
			}

			prev->next = current->next;
			*last = prev;
			free(current);
		}
	}

	prev->next = current->next;
	free(current);
}


void split_list(struct Node *last, struct Node **last1, struct Node **last2)
{
	if(last == NULL)
	{
		printf("Cannor split an empty list");
		return;
	}

	struct Node *fast_ptr = last, *slow_ptr = last;

	while(fast_ptr->next != last && fast_ptr->next->next != last)
	{
		slow_ptr = slow_ptr->next;
		fast_ptr = fast_ptr->next->next;

		printf("%d %d\n", slow_ptr->data, fast_ptr->data);
	}

	if(fast_ptr->next->next == last)
		fast_ptr = fast_ptr->next->next;

	else
		fast_ptr = fast_ptr->next;

	slow_ptr = slow_ptr->next;

	struct Node *temp = slow_ptr->next;
	slow_ptr->next = fast_ptr->next;
	fast_ptr->next = temp;

	*last1 = slow_ptr;
	*last2 = fast_ptr;
}


void sorted_insertion(struct Node **last, int data)
{
	if(*last == NULL)
	{
		push(last, data);
		return;
	}

	struct Node *new_node = create_node(data);


	struct Node *current = (*last)->next, *prev = *last;

	do
	{

		if(current->data >= data)
			break;
		prev = current;
		current = current->next;
	}
	while(current != (*last));

	if(new_node->data >= (*last)->data)
	{
		new_node->next = (*last)->next;
		(*last)->next = new_node;
		*last = new_node;
		return;
	}

	new_node->next = current;
	prev->next = new_node;

} 

int main()
{
	struct Node *last = NULL, *head1 = NULL, *head2 = NULL;

	int ele, prev_node_data, ch1, ch2, pos, count, val1, val2;
	while(1)
	{
		loop1: printf("\n1. Insertion\n2. Deletion\n3. Count the elements in the list\n4. Split the linked list in two halves\n5. Quit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch1);
		switch(ch1)
		{
			case 1: 	while(1)
						{
							printf("\n\nInsertion Menu");
							printf("\n1. Insertion at the head of linked list\n2. Inserion at the tail of linked list\n3. Insertion after a specified position in linked list\n4. Insert all the elements in one go\n5. Sorted insertion\n6. Stop insertion\n");
							printf("Enter your choice: ");
							scanf("%d", &ch2);
							switch(ch2)
							{
								case 1: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											push(&last, ele);
											printf("Current Linked list:\t");
											print_list(last);
											break;

								case 2: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											append(&last, ele);
											printf("Current Linked list:\t");
											print_list(last);
											break;

								case 3: 	printf("Enter the element to be inserted: ");
											scanf("%d", &ele);
											printf("\nEnter the element after which you want to insert the new element: ");
											scanf("%d", &prev_node_data);
											insert_after(&last, prev_node_data, ele);
											printf("Current Linked list:\t");
											print_list(last);
											break;

								case 4:		printf("Enter the elements of the linked list (enter -1 to stop insertion):\t");
											while(1)
											{
												scanf("%d", &ele);
												if(ele == -1)
													break;
												append(&last, ele);

											}
											goto stop;

								case 5:		printf("Enter the elements of the linked list (enter -1 to stop insertion):\t");
											while(1)
											{
												scanf("%d", &ele);
												if(ele == -1)
													break;
												sorted_insertion(&last, ele);

											}
											goto stop;

						stop:	case 6: 	if(last == NULL)
												goto loop1;
											else
											{
												printf("Created list is:\t");
												print_list(last);
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
											delete(&last, ele);
											if(last != NULL)
											{
												printf("Current Linked list:\t");
												print_list(last);
											}
											break;

								case 2: 	if(last != NULL)
											{
												printf("Current Linked list:\t");
												print_list(last);
											}
											goto loop1;

								default:	printf("Wrong option inserted, Choose again\n");
							}	
						}


			case 3: 	count = get_count(&last);
						printf("\nNumber of elements in the current linked list: %d", count);
						break;

			case 4:		printf("Current list\t");
						print_list(last);
						struct Node *last1 = last, *last2 = last;
						split_list(last, &last1, &last2);
						printf("1st list after splitting:\t");
						print_list(last1);
						printf("2nd list after splitting:\t");
						print_list(last2);
						break;

			case 5:		exit(1);

			default : 	printf("You have entered a wrong number. Please choose again\n");
		}
	}

	return 0;
}