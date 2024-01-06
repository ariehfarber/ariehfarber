/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 22/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf					*/
#include <stdlib.h> /*size_t,realloc,free		*/
#include <assert.h> /*assert					*/
#include <string.h> /*strlen,strcat				*/

#include "ws8.h"

#define ELEMENT_NUM 5

static void PrintInt(size_t value);
static void PrintFloat(size_t value);
static void PrintString(size_t value);
static void AddInt(size_t *target, int int_value);
static void AddFloat(size_t *target, int float_value);
static void AddString(size_t *target, int value);
static void CleanInt(size_t *target);
static void CleanFloat(size_t *target);
static void CleanString(size_t *target);

void SetInt(element_t *target, int int_number) 
{
	target->data = *(size_t *)&int_number; 
	target->PrintValue = PrintInt;
	target->AddNumber = AddInt;
	target->CleanValue = CleanInt;
}

void SetFloat(element_t *target, float float_number) 
{
	target->data = *(size_t *)&float_number;
	target->PrintValue = PrintFloat;
	target->AddNumber = AddFloat;
	target->CleanValue = CleanFloat;
}

void SetString(element_t *target, char *str) 
{
	target->data = (size_t)str; 
	target->PrintValue = PrintString;
	target->AddNumber = AddString;
	target->CleanValue = CleanString;
}

void PrintElements(element_t *my_elements)
{	
	int i = 0;
				
	for (i = 0; i < ELEMENT_NUM; ++i)
	{
		my_elements[i].PrintValue(my_elements[i].data);
	}
	printf("\n");
}

void AddElements(element_t *my_elements, int int_num)
{	
	int i = 0;
				
	for (i = 0; i < ELEMENT_NUM; ++i)
	{
		my_elements[i].AddNumber(&my_elements[i].data, int_num);
	}
}

void CleanElements(element_t *my_elements)
{	
	int i = 0;
				
	for (i = 0; i < ELEMENT_NUM; ++i)
	{
		my_elements[i].CleanValue(&my_elements[i].data);
	}
}

static void PrintInt(size_t value)
{
	printf("%d, ", *(int *)&value);	
}

static void PrintFloat(size_t value)
{
	printf("%.6f, ", *(float *)&value);	
}

static void PrintString(size_t value)
{
	printf("%s, ", (char *)value);	
}

static void AddInt(size_t *target, int int_value)
{
	int temp_int = 0;
	
	temp_int = *(int *)target;
	temp_int += int_value;
	*target = *(size_t *)&temp_int;	
}

static void AddFloat(size_t *target, int float_value)
{
	float temp_float = 0;
	
	temp_float = *(float *)target;
	temp_float += (float)float_value;
	*target = *(size_t *)&temp_float;	
}

static void AddString(size_t *target, int value)
{
	char temp_buffer[10]; /*the biggest integer is 10 charecters*/
	char *new_str = NULL;
	size_t new_str_length = 0;

	sprintf(temp_buffer, "%d", value);

	new_str_length = strlen((char *)(*target)) + strlen(temp_buffer) + 1;

	new_str = realloc(((char *)(*target)), new_str_length);
	assert(new_str);

	strcat(new_str, temp_buffer);

	*target = (size_t)new_str;
}

static void CleanInt(size_t *target)
{
	(void)target;
}

static void CleanFloat(size_t *target)
{
	(void)target;
}

static void CleanString(size_t *target)
{
	free((char *)(*target));
	*target = 0; 
}
