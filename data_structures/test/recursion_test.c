/*******************************************************************************
*Author: Bar Gonen
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recursion.h"
#include "stack.h"

#define SUCCESS (0)
#define FAIL (-1)
#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

void TestRecursion(void);
int FibonacciTest(void);
int TestFlipList(void);
int TestSortedStack(void);
int TestStrLen(void);
int TestStrCmp(void);
int TestStrCpy(void);
int TestStrCat(void);
int TestStrStr(void);

int main(void)
{
    TestRecursion();

    return (0);
}

void TestRecursion(void)
{
    if(FAIL == FibonacciTest())
    {
        printf("FibonacciTest() failed!\n");
        return;
    }
	else
	{
		printf("FibonacciTest() Succeded!\n");
	}

    if(FAIL == TestFlipList())
    {
        printf("TestFlipList() failed!\n");
        return;
    }
	else
	{
		printf("TestFlipList() Succeded!\n");
	}

    if(FAIL == TestSortedStack())
    {
        printf("TestSortedStack() failed!\n");
        return;
    }
	else
	{
		printf("TestSortedStack() Succeded!\n");
	}

	if(FAIL == TestStrLen())
    {
        printf("TestStrLen() failed!\n");
        return;
    }
	else
	{
		printf("TestStrLen() Succeded!\n");
	}

    if(FAIL == TestStrCmp())
    {
        printf("TestStrCmp() failed!\n");
        return;
    }
	else
	{
		printf("TestStrCmp() Succeded!\n");
	}

	if(FAIL == TestStrCpy())
    {
        printf("TestStrCpy() failed!\n");
        return;
    }
	else
	{
		printf("TestStrCpy() Succeded!\n");
	}

    if(FAIL == TestStrCat())
    {
        printf("TestStrCat() failed!\n");
        return;
    }
	else
	{
		printf("TestStrCat() Succeded!\n");
	}

   if(FAIL == TestStrStr())
    {
        printf("TestStrStr() failed!\n");
        return;
    }
 	else
	{
		printf("TestStrStr() Succeded!\n");
	}

    printf("\nAll tests are successful!\n\n");
}

int FibonacciTest(void)
{
    int indexes[] = {1, 9, 10};
    int res[] = {1, 34, 55};
    size_t i = 0;

    for(i = 0; i < ARR_SIZE(res); ++i)
    {
        if(res[i] != RecursiveFibonacci(indexes[i]) || res[i] != \
										IterativeFibonacci(indexes[i]))
        {
            return (FAIL);
        }
    }

    return (SUCCESS);
}

static node_t *NodeCreate(void *data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->data = data;
    node->next = NULL;

    return (node);
}

static void NodeDestroy(node_t *head)
{
    node_t *temp = NULL;

    while(NULL != head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

static void PrintList(node_t *head)
{
    printf("\n\n");
    while(NULL != head)
    {
        printf("%d ", *(int *)head->data);
        head = head->next;
    }
    printf("\n\n");
}

int TestFlipList(void)
{
    int data[] = {0, 1, 2, 3, 4, 5};
    int res[] = {5, 4, 3, 2, 1, 0};
    size_t i = 0;
    node_t *temp = NULL;
    node_t *head = NodeCreate(&data[0]);
    head->next = NodeCreate(&data[1]);
    head->next->next = NodeCreate(&data[2]);
    head->next->next->next = NodeCreate(&data[3]);
    head->next->next->next->next = NodeCreate(&data[4]);
    head->next->next->next->next->next = NodeCreate(&data[5]);
   
    PrintList(head);

    head = RecursiveFlipList(head);
    temp = head;

    PrintList(head);

    for(i = 0; i < ARR_SIZE(res); ++i)
    {
        if(*(int *)head->data != res[i])
        {
            printf("Case %lu, Data is: %d\n", i, *(int *)head->data);
            NodeDestroy(temp);
            return (FAIL);
        }
        head = head->next;
    }

    NodeDestroy(temp);

    return (SUCCESS);
}

int TestSortedStack(void)
{
    int data[] = {30, -5, 12, 4, 55, -3};
    int res[] = {55, 30, 12, 4, -3, -5};
    stack_t *stack = StackCreate(ARR_SIZE(data), sizeof(int));
    size_t i = 0;

    for(i = 0; i < ARR_SIZE(data); ++i)
    {
        StackPush(stack, &data[i]);
    }

    RecursiveSortStack(stack);

    for(i = 0; i < ARR_SIZE(res); ++i)
    {
        if(res[i] != *(int *)StackPeek(stack))
        {
            return (FAIL);
        }

        StackPop(stack);
    }

    StackDestroy(stack);

    return (SUCCESS);
}

int TestStrLen(void)
{
    char *str = "My StrLen is better than yours!";

    if(strlen(str) == RecursiveStrLen(str))
    {
        return (SUCCESS);
    }

    return (FAIL);
}

 int TestStrCmp(void)
{
    char *s1 = "This will be zero";
    char *s2 = "This will be zero";
    char *s3 = "This will be";
    char *s4 = "This will be minus";
    char *s5 = "This will be plus";
    char *s6 = "This will be";

    if(0 != RecursiveStrcmp(s1, s2))
    {
        return (FAIL);
    }

    if(0 <= RecursiveStrcmp(s3, s4))
    {
        return (FAIL);
    }

    if(0 >= RecursiveStrcmp(s5, s6))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

int TestStrCpy(void)
{
    char *src = "Lets copy this string";
    char *dest = (char *)malloc(sizeof(char) * (strlen(src) + 1));
    char *str = RecursiveStrcpy(dest, src);

    while ('\0' != *str)
    {
        if(*str != *src)
        {
            free(dest);
            return (FAIL);
        }

        ++str;
        ++src;
    }

    free(dest);

    return (SUCCESS);
}

int TestStrCat(void)
{
    char *temp = "The rest of the string";
    char *src = " will be catted here";
    char *res = "The rest of the string will be catted here";
    char *dest = (char *)malloc((sizeof(char) * (strlen(res) + 1)));
	char *start = dest;

    dest = RecursiveStrcpy(dest, temp);
    dest = RecursiveStrcat(dest, src);
    while('\0' != *dest)
    {
        if(*dest != *res)
        {
            free(dest);
            return(FAIL);
        }

        ++dest;
        ++res;
    }

    free(start);

    return(SUCCESS);
}

int TestStrStr(void)
{
    char *haystack = "This string shall be found";
    char *needle1 = "shall be";
    char *needle2 = "This will not";
    char *needle3 = "";

    if(NULL == RecursiveStrstr(haystack, needle1))
    {
        return (FAIL);
    }

    if(NULL != RecursiveStrstr(haystack, needle2))
    {
        return (FAIL);
    }

    if(haystack != RecursiveStrstr(haystack, needle3))
    {
        return (FAIL);
    }

    return (SUCCESS);
}