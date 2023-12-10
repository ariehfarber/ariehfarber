/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 23/11/2023
*******************************************************************************/
#include <stdio.h>  /*FILE */

#include "ws9.h"

#define SUCCESS 0
#define FAILURE 1

int SaveToBinFile(student *my_student, char *title)
{
	FILE *fp;
	
	fp = fopen(title, "wb");
	if (NULL == fp)
	{
		return (FAILURE);
	}
	
	fwrite(my_student, sizeof(*my_student), 1, fp);
	if (0 != ferror(fp)) 
	{
		return (FAILURE);
	}
	clearerr(fp);
	
	fclose(fp);
	if (NULL == fp)
	{
		return (FAILURE);
	}
	
	return (SUCCESS);
}

int LoadFromBinFile(student *my_student, char *title)
{
	FILE *fp;
	
	fp = fopen(title, "rb");
	if (NULL == fp)
	{
		return (FAILURE);
	}
	
	fread(my_student, sizeof(*my_student), 1, fp);
	if (0 != ferror(fp)) 
	{
		return (FAILURE);
	}
	clearerr(fp);
	
	fclose(fp);
	if (NULL == fp)
	{
		return (FAILURE);
	}
	
	return (SUCCESS);
}
