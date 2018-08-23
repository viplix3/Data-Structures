#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct Node
{
	int data;
	struct Node *next;
};


struct Node* create_node(int data)
{
	struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}


void push(struct Node **head, int data)
{
	struct Node *new_node = create_node(data);

	new_node->next = *head;
	*head = new_node;
}


void insert_after(struct Node **head, int prev_node_data, int data)
{
	struct Node *new_node = create_node(data);
	struct Node *prev_node = *head;

	while(prev_node->data != prev_node_data && prev_node != NULL)
		prev_node = prev_node->next;

	if(prev_node == NULL)
	{
		printf("Cannot add a new node as node with element %d is not in linked list", prev_node_data);
		return;
	}

	new_node->next = prev_node->next;
	prev_node->next = new_node;
}


void append(struct Node **head, int data)
{
	struct Node *new_node = create_node(data);

	if(*head == NULL)
	{
		*head = new_node;
		return;
	}

	struct Node *last = *head;

	while(last->next != NULL)
		last = last->next;

	last->next = new_node;
}


void delete(struct Node **head, int data)
{
	struct Node *temp = *head, *prev;

	if(*head == NULL)
	{
		printf("Linked list is empty, Please enter some elements first\n");
		return;
	}

	while(temp != NULL && temp->data == data)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while(temp != NULL && temp->data != data)
	{
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL)
		return;

	prev->next = temp->next;
	free(temp);
}


void delete_at_pos(struct Node **head, int pos)
{
	if(*head == NULL)
	{
		printf("Linked list is empty. Please insert some elements first\n");
		return;
	}

	struct Node *temp = *head, *prev;

	if(pos == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while(temp != NULL && pos>0)
	{
		prev = temp;
		temp = temp->next;
		pos--;
	}

	if(temp == NULL)
	{
		printf("Position is beyond the size of linked list\n");
		return;
	}

	prev->next = temp->next;

	free(temp);
}


int swap_nodes(struct Node **head, int val1, int val2)
{
	struct Node *node1 = *head, *node2 = *head, *prev_node1 = node1, *prev_node2 = node2;

	if(val1 == val2)
		return 1;

	while(node1 != NULL && node1->data != val1)
	{
		prev_node1 = node1;
		node1 = node1->next;
	}
	
	while(node2 != NULL && node2->data != val2)
	{
		prev_node2 = node2;
		node2 = node2->next;
	}

	if(node1==NULL || node2 == NULL)
	{
		printf("One or more values provided not present in the linked list\n");
		return 0;
	}


	if(prev_node1 == node1)
	{	
		*head = node2;
		prev_node2->next = node1;
	}

	else if(prev_node2 == node2)
	{
		*head =node1;
		prev_node1->next = node2;
	}

	else
	{
		prev_node1->next = node2;
		prev_node2->next = node1;
	}

	struct Node *temp = node2->next;
	node2->next = node1->next;
	node1->next = temp;

	return 1;
}


void reverse(struct Node **head)
{
	if(*head == NULL)
		return;

	struct Node *next = *head, *prev = NULL, *curr = *head;

	while(curr != NULL)
	{
		next = next->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*head = prev;
}


struct Node *reverse_group(struct Node *head, int k)
{
    struct Node* current = head;
    struct Node* next = NULL;
    struct Node* prev = NULL;
    int count = 0;   
     
    /*reverse first k nodes of the linked list */
    while (current != NULL && count < k)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
     
    /* next is now a pointer to (k+1)th node 
       Recursively call for the list starting from current.
       And make rest of the list as next of first node */
    if (next !=  NULL)
       head->next = reverse_group(next, k); 
 
    /* prev is new head of the input list */
    return prev;
}


struct Node *merge(struct Node **head1, struct Node **head2)
{
	struct Node *head = NULL, *temp = NULL, dummy;
	head = &dummy;
	int c=0;

	if(*head1 == NULL)
		return *head2;
	if(*head2 == NULL)
		return *head1;

	while((*head1) != NULL && (*head2) != NULL)
	{
		if((*head1)->data <= (*head2)->data)
		{
			head->next = *head1;
			*head1 = (*head1)->next;
		}

		else if((*head1)->data > (*head2)->data)
		{
			head->next = *head2;
			*head2 = (*head2)->next;
		}


		head = head->next;
		head->next = NULL;

		if(!c)
		{
			temp = head;
			c++;
		}
	}

	if((*head1) != NULL)
		head->next = *head1;

	if((*head2) != NULL)
		head->next = *head2;

	return temp;
}


int get_count(struct Node **head)
{
	struct Node *current = *head;
	int count = 0;

	while(current != NULL)
	{
		current = current->next;
		count++;
	}
	return count;
}


void split_list(struct Node **head, struct Node **list1, struct Node **list2)
{
	struct Node *temp = NULL;
	*list1 = *head;
	int count = get_count(head);
	while(count--)
	{
		temp = *head;
		*head = (*head)->next;
	}

	temp->next = NULL;
	*list2 = *head;
	printf("%d %d", (*list1)->data, (*list2)->data);
}


void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef)
{
	struct Node* fast;
	struct Node* slow;
	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
	fast = fast->next;
	if (fast != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
	}


void MergeSort(struct Node **head)
{
	if((*head) == NULL || (*head)->next == NULL)
		return;
	
	struct Node *a = NULL, *b = NULL;
	FrontBackSplit(*head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	*head = merge(&a, &b);
}


void counter_rotation(struct Node **headref, int n)
{
	struct Node *head = *headref, *prev = NULL, *tail = *headref;

	while(n)
	{
		prev = head;
		head = head->next;
		n--;
	}

	prev->next = NULL;
	*headref = head;

	while(head->next != NULL)
		head = head->next;

	head->next = tail;


}


int detect_loop(struct Node *head)
{
	// Loop detection using Floyd's method
	struct Node *slow_pointer = head, *fast_pointer = head;

	while(slow_pointer != NULL && fast_pointer != NULL && fast_pointer->next != NULL)
	{
		slow_pointer = slow_pointer->next;
		fast_pointer = fast_pointer->next->next;

		if(slow_pointer == fast_pointer)
			return 1;
	}

	return 0;
}


struct Node *add_lists(struct Node *first, struct Node *second)
{
	struct Node *result = NULL, *temp = NULL, *result_head = NULL;
	int carry = 0, sum;

	while(first != NULL || second != NULL)
	{
		sum = carry + (first ? first->data : 0) + (second ? second->data : 0);

		carry = (sum>9 ? 1 : 0);
		sum = sum % 10;

		temp = create_node(sum);

		if(result == NULL)
		{
			result = temp;
			result_head = result;
		}
 		else
 		{
			result->next = temp;
			result = result->next;
		}

		if(first != NULL)
			first = first->next;
		if(second != NULL)
			second = second->next;
	}

	if(carry>0)
		temp = create_node(carry);
	result->next = temp;

	return result_head;
}


void print_list(struct Node *head)
{
	int c=0;

	if(head == NULL)
	{
		printf("There are no elements in the current linked list. Please put some elements onto the linked list by using Insertion menu");
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
			printf("->%d", head->data);

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
		loop1: printf("\n1. Insertion\n2. Deletion\n3. Count the number of elements in the current linked list\n4. Swap nodes in current linked list\n5. Reverse the elements in the current linked list\n6. Reverse the current linked list in groups\n7. Sort the current linked list\n8. Counter clockwise node rotation in current linked list\n9. Merge two sorted lists\n10. Add numbers stored in two linked lists\n11. Quit\n");
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
											insert_after(&head, prev_node_data, ele);
											printf("Current Linked list:\t");
											print_list(head);
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
							printf("\n1. Delete a specific element\n2. Delete an element from a specific position\n3. Stop Deletion\n");
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

								case 2: 	printf("Enter the position from where the element is to be deleted: ");
											scanf("%d", &pos);
											delete_at_pos(&head, pos);
											if(head != NULL)
											{
												printf("Current Linked list\t");
												print_list(head);
											}
											break;

								case 3: 	if(head != NULL)
											{
												printf("Current Linked list:\t");
												print_list(head);
											}
											goto loop1;

								default:	printf("Wrong option inserted, Choose again\n");
							}	
						}

			case 3: 	count = get_count(&head);
						printf("\nNumber of elements in the current linked list: %d", count);
						break;

			case 4:		printf("\nEnter the values of nodes to be swapped: ");
						scanf("%d %d", &val1, &val2);
						if(swap_nodes(&head, val1, val2))
						{
							printf("Linked list after swapped nodes:\t");
							print_list(head);
						}
						break;

			case 5:		printf("\nCurrent List:\t");
						print_list(head);
						reverse(&head);
						printf("\nReversed list:\t");
						print_list(head);
						break;

			case 6:		printf("Enter the group size for carrying out group reversal:\t");
						scanf("%d", &ele);
						printf("Current linked list:\t");
						print_list(head);
						struct Node *reversed = reverse_group(head, ele);
						printf("Linked list after group reversal:\t");
						print_list(reversed);
						break;

			case 7: 	printf("Current linked list:\t");
						print_list(head);
						MergeSort(&head);
						printf("Sorted linked list:\t");
						print_list(head);
						break;

			case 8: 	printf("Current linked list is\t");
						print_list(head);
						printf("Enter the number of nodes you want to be rotated counter-clockwise:\t");
						scanf("%d", &ele);
						counter_rotation(&head, ele);
						printf("Linked list after counter rotation:\t");
						print_list(head);
						break;


			case 9: 	printf("Enter 1st list in sorted order (enter -1 to stop insertion):\t");
						while(1)
						{
							scanf("%d", &ele);
							if(ele == -1)
								break;
							append(&head1, ele);
						}

						printf("Enter 2nd list in sorted order (enter -1 to stop insertion):\t");
						while(1)
						{
							scanf("%d", &ele);
							if(ele == -1)
								break;
							append(&head2, ele);
						}

						printf("List 1:\t");
						print_list(head1);
						printf("\nList 2:\t");
						print_list(head2);

						struct Node* merged = merge(&head1, &head2);
						printf("\nMerged list:\t");
						print_list(merged);
						break;

			case 10: 	printf("Enter 1st list (enter -1 to stop insertion):\t");
						while(1)
						{
							scanf("%d", &ele);
							if(ele == -1)
								break;
							append(&head1, ele);
						}

						printf("Enter 2nd list (enter -1 to stop insertion):\t");
						while(1)
						{
							scanf("%d", &ele);
							if(ele == -1)
								break;
							append(&head2, ele);
						}

						printf("List 1:\t");
						print_list(head1);
						printf("\nList 2:\t");
						print_list(head2);

						struct Node *result = add_lists(head1, head2);
						printf("Sum of two lists:\t");
						print_list(result);
						break;


			case 11:	exit(1);

			default : 	printf("You have entered a wrong number. Please choose again\n");
		}
	}

	return 0;
}