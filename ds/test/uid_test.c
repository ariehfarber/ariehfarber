/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Elinor Fuchs
*Date: 20/12/2023
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "uid.h"

#define TRUE 1
#define FALSE 0

static void TestUID();

int main()
{
	TestUID();

	return (0);
}

static void TestInt(int control, int test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestUID()
{	
	ilrd_uid_t test_uid_1 = {0};
	ilrd_uid_t test_uid_2 = {0};
	int state = TRUE;
		
	test_uid_1 = UIDCreate();
	test_uid_2 = UIDCreate();
	
	printf("Counter: %lu\n", test_uid_2.counter);
	printf("PID: %lu\n", (size_t)test_uid_2.pid);
	printf("Time: %s", ctime(&test_uid_2.time));
	printf("IP: %s\n", test_uid_2.ip);
	
	state = UIDIsEqual(test_uid_1, test_uid_1);
	TestInt(TRUE, state, __LINE__);
	state = UIDIsEqual(test_uid_1, bad_uid);
	TestInt(FALSE, state, __LINE__);
	state = UIDIsEqual(test_uid_1, test_uid_2);
	TestInt(FALSE, state, __LINE__);
}
