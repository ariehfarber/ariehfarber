/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 23/11/2023
*******************************************************************************/
#include <stdio.h>  /*FILE */

#include "ws9.h"

int SaveToBinFile(student *my_student, char *title)
{
	FILE *fp;
	
	fp = fopen(title, "wb");
	if (!fp)
	{
		return (1);
	}
	
	fwrite(my_student, sizeof(*my_student), 1, fp);
	if (ferror(fp)) 
	{
		return (1);
	}
	clearerr(fp);
	
	fclose(fp);
	if (!fp)
	{
		return (1);
	}
	
	return (0);
}

int LoadFromBinFile(student *my_student, char *title)
{
	FILE *fp;
	
	fp = fopen(title, "rb");
	if (!fp)
	{
		return (1);
	}
	
	fread(my_student, sizeof(*my_student), 1, fp);
	if (ferror(fp)) 
	{
		return (1);
	}
	clearerr(fp);
	
	fclose(fp);
	if (!fp)
	{
		return (1);
	}
	
	return (0);
}
