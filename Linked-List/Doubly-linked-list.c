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
	new_node-prev-> = NULL;

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


void insert_after(struct Node *head, int data, int key)
{
	if(head == NULL)
	{
		printf("List is empty, cannot find the key %d", key);
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


void append(struct Node **headref, int data);
{

}