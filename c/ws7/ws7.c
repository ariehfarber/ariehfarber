/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
***********************************************************************************/

#include <stdio.h>  /*printf		*/
#include <stdlib.h> /*size_t,malloc,free*/
#include <assert.h> /*assert		*/
#include <string.h> /*strlen,strcat	*/

#include "ws7.h"

#define ELEMENT_NUM 5

typedef enum data_type
{
	INT = 1,
	FLOAT = 2,
	STRING = 3
} data_type_t;

typedef struct element
{
	size_t *data;
	data_type_t type;
} element_t;

void SetInt(element_t *target, int int_number) 
{
	target->data = malloc(sizeof(int));
	assert(target->data);

	*(int *)(target->data) = int_number; 
	target->type = INT;
}

void SetFloat(element_t *target, float float_number) 
{
	target->data = malloc(sizeof(float));
	assert(target->data);

	*(float *)(target->data) = float_number; 
	target->type = FLOAT;
}

void SetString(element_t *target, char *str) 
{
	size_t length = 0;
	length = strlen(str) + 1;
	
	target->data = malloc(length);
	assert(target->data);

	strcpy((char *)(target->data), str); 
	target->type = STRING;
}


void PrintElement(element_t *target)
{
	switch (target->type)
	{
		case INT:
			printf("%d, ", *(int *)target->data);
			break;
		case FLOAT:
			printf("%.6f, ", *(float *)target->data);
			break;
		case STRING:
			printf("%s ", (char *)target->data);
			break;
	}
}

void AddInt(element_t *target, int value)
{
	size_t length = 0;
	void *temp_ptr = NULL;
	char buffer[12];

	switch (target->type)
	{
		case INT:
			*(int *)(target->data) += value; 
			break;
		case FLOAT:
			*(float *)(target->data) += (float)value; 
			break;
		case STRING:
			sprintf(buffer, "%d", value);
			length = strlen((char *)(target->data)) + strlen(buffer) + 1;
			temp_ptr = realloc(target->data, length);
			assert(temp_ptr);
			target->data = temp_ptr;
			strcat((char *)target->data, buffer); 
			break;
	}
}

void ListElements()
{		
	int i = 0;
	
	element_t element_array[ELEMENT_NUM]; 

	SetFloat(&element_array[0], 4.2);
	SetFloat(&element_array[1], 6.7);
	SetString(&element_array[2], "chapter");
	SetInt(&element_array[3], 12);
	SetFloat(&element_array[4], 56.32);
	
	for (i = 0; i < ELEMENT_NUM; i++) 
	{
		PrintElement(&element_array[i]);
	}
	printf("\n");
	
	for (i = 0; i < ELEMENT_NUM; i++) 
	{
		AddInt(&element_array[i], 10);
	}

	for (i = 0; i < ELEMENT_NUM; i++) 
	{
		PrintElement(&element_array[i]);
	}
	printf("\n");
	
	for (i = 0; i < ELEMENT_NUM; i++) 
	{
		if (element_array[i].data != NULL) 
		{
			free(element_array[i].data);
		}
	}
}







/*char *StrDup(const char *str)*/
/*{*/
/*	char *duplicated = NULL;*/
/*	*/
/*	assert(NULL != str);*/
/*	*/
/*	duplicated = (char *)malloc(strlen(str) + 1);*/
/*	if(!duplicated)*/
/*	{*/
/*		return (NULL);*/
/*	}*/
/*	*/
/*	return (strcpy(duplicated ,str));*/
/*}*/
