/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stddef.h> /*size_t         */
#include <string.h> /*strlen, strncmp*/

#include "recursion.h"
#include "ds_utils.h"

static void SortInserted(stack_t *stack, int value);

int IterativeFibonacci(int element_index)
{
    int fibonacci = 0;
    int prev = 1;

    while (0 < element_index)
    {
        fibonacci = fibonacci + prev;
        prev = fibonacci - prev;
        --element_index;
    }

    return (fibonacci);
}

int RecursiveFibonacci(int element_index)
{
    if (1 >= element_index)
    {
        return (element_index);
    }

    return (RecursiveFibonacci(element_index - 2) + \
            RecursiveFibonacci(element_index - 1));
}

node_t *RecursiveFlipList(node_t *node)
{
    node_t *head = NULL;

    if (NULL == node->next)
    {
        return (node);
    }

    head = RecursiveFlipList(node->next);
    node->next->next = node;
    node->next = NULL;

    return (head);
}

void RecursiveSortStack(stack_t *stack)
{
    int *value = NULL;
 
    if (FALSE == StackIsEmpty(stack))
    {
        value = (int *)StackPeek(stack);
        StackPop(stack);
        RecursiveSortStack(stack);
        SortInserted(stack, *value);
    }
}

size_t RecursiveStrLen(const char *s)
{ 
    if ('\0' == *s)
    {
        return (0);
    }
    
    return (1 + RecursiveStrLen((char *)s + 1));
}

int RecursiveStrcmp(const char *s1, const char *s2)
{
    if ('\0'  == *s1 && '\0'  == *s2)
    {
        return (0);
    }
    else if (*s1 != *s2)
    {
        return (s1 - s2);
    }

    return (RecursiveStrcmp((char *)s1 + 1, (char *)s2 + 1));
}

char *RecursiveStrcpy(char *dest, const char *src)
{
    *dest = *src;
    
    if ('\0' != *src)
    {
        RecursiveStrcpy(dest + 1, (char *)src + 1);
    }

    return (dest);
}

char *RecursiveStrcat(char *dest, const char *src)
{
    if ('\0' == *dest)
    {
        return (RecursiveStrcpy(dest, (char *)src));
    }

    RecursiveStrcat(dest + 1, (char *)src);

    return (dest);
} 

char *RecursiveStrstr(const char *haystack, const char *needle)
{
    if (0 == strncmp(haystack, needle, strlen(needle)))
    {
        return ((char *)haystack);        
    }   
    
    if ('\0' == *haystack)
    {
        return (NULL);
    }

    return (RecursiveStrstr((char *)haystack + 1, needle));
}

static void SortInserted(stack_t *stack, int value)
{
    int temp = 0;
    
    if (StackIsEmpty(stack) || value > *(int *)StackPeek(stack)) 
    {
        StackPush(stack, &value);
        
        return;
    }

    temp = *(int *)StackPeek(stack);
    StackPop(stack);
    SortInserted(stack, value);
   
    StackPush(stack, &temp);
}