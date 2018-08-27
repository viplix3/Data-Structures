#include<stdio.h>
#include<stdlib.h>


struct Stack
{
	int top;
	unsigned capacity;
	int *arr;
};


struct Stack *createStack(unsigned capacity)
{
	struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->arr = (int*)malloc(stack->capacity * sizeof(int));

	return stack;
}


int isFull(struct Stack *stack)
{
	return (stack->top == stack->capacity-1);
}


int isEmpty(struct Stack *stack)
{
	return (stack->top == -1);
}


void push(struct Stack *stack, int ele)
{
	if(isFull(stack))
	{
		printf("Stack is already full, cannot insert any more items\n");
		return;
	}

	stack->arr[++stack->top] = ele;
	printf("%d pushed into the stack\n", ele);
}


int peek(struct Stack *stack)
{
	if(isEmpty(stack))
	{
		printf("Stack is empty");
		return -1;
	}

	return stack->arr[stack->top];
}


int pop(struct Stack *stack)
{
	if(isEmpty(stack))
	{
		printf("Stack is already empty, push some elements first");
		return -1;
	}

	return stack->arr[stack->top--];
}


int main()
{
	unsigned capacity;
	int ele, ch;
	printf("Array Stack\n");
	printf("\nEnter the size of the stack to be created: ");
	scanf("%u", &capacity);
	struct Stack *stack = createStack(capacity);

	do
	{
		printf("\n\n1. Push elements\n2. Pop Elements\n3. Peek the element at top of the stack without popping any elements\n4. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1: 	printf("\nEnter the elements to be pushed into the stack, enter -1 to stop:\n");
						while(1)
						{
							scanf("%d", &ele);
							if(ele == -1)
								break;
							push(stack, ele);
						}
						break;

			case 2:		ele = pop(stack);
						if(ele != -1)
							printf("\nElement popped from the stack is: %d\n", ele);
						break;

			case 3:		printf("\nTop of the stack is: %d", peek(stack));
						break;

			case 4: 	exit(1);

			default: 	printf("Wrong choice entered. Please choose again\n");

		}
	}
	while(1);


	return 0;
}