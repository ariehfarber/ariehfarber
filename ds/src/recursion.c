/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stddef.h> /*size_t*/


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

node_t *FlipList(node_t *node)
{
    node_t *current = node;
    
}

void SortStack(stack_t *stack)
{
    int *value = NULL;
 
    if (FALSE == StackIsEmpty(stack))
    {
        value = (int *)StackPeek(stack);
        StackPop(stack);
        SortStack(stack);
        SortInserted(stack, *value);
    }
}

/* size_t RecursiveStrLen(const char *s)
{
    
} */

/* int RecursiveStrcmp(const char *s1, const char *s2)
{
    
} */

/* char RecursiveStrcpy(char *dest, const char *src)
{
    
}
 */
/* char RecursiveStrcat(char *dest, const char *src)
{
    
} */

/* char RecursiveStrstr(const char *haystack, const char *needle)
{
    
} */

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