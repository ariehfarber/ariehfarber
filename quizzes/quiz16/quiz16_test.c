/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/

#include "quiz16.h"

static void TestFindNumInArr();

int main()
{
	TestFindNumInArr();
	
	return (0);
}

static void TestFindNumInArr()
{
	int arr[] = {-9, 15, -88, -9, 3, 798, 3, 59, 0};
	int n = 1;
	int size = 0;
	int state = 0;
	
	size = sizeof(arr) / sizeof(arr[0]);
	
	state = FindNumInArr(arr,  n,  size);
	
	printf("state %d\n", state);
}


