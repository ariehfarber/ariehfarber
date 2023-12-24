/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Alon Sitman 
*Date: 24/12/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/

/*#include "pq.h"*/
/*#include "task.h"*/
/*#include "scheduler.h"*/

/*#define TRUE 1*/
/*#define FALSE 0*/

/*static void TestScheduler();*/

/*int main()*/
/*{*/
/*	TestScheduler();*/
/*	*/
/*	return (0);*/
/*}*/

/*static void TestAdd(scheduler_t *test_scheduler);*/
/*static void TestRun(scheduler_t *test_scheduler);*/

/*static int PrintInt(void *params);*/
/*static void VoidCleanUp(void *params);*/

/*static void TestInt(int control, int test, int line);*/
/*static void TestSizeT(size_t control, size_t test, int line);*/

/*static void TestScheduler()*/
/*{*/
/*	scheduler_t *test_scheduler = NULL;*/
/*	size_t size = -1;*/

/*	test_scheduler = SchedulerCreate();*/
/*	assert(NULL != test_scheduler);*/
/*	*/
/*	TestAdd(test_scheduler);*/
/*	size = SchedulerSize(test_scheduler);*/
/*	TestSizeT(1, size, __LINE__);*/
/*	*/
/*	TestRun(test_scheduler);*/
/*	*/
/*	SchedulerDestroy(test_scheduler);*/
/*}*/

/*static void TestAdd(scheduler_t *test_scheduler)*/
/*{*/
/*	ilrd_uid_t uid = {0};*/
/*	static int params = 123;*/
/*	void *clean_up_params = NULL;*/
/*	time_t time_to_run = 2;*/
/*	size_t interval = 0;*/
/*	int state = TRUE;*/

/*	uid = SchedulerAdd(test_scheduler, PrintInt, &params, \*/
/*					   time_to_run, interval VoidCleanUp, clean_up_params);*/
/*	state = UIDIsEqual(uid, bad_uid);*/
/*	TestInt(FALSE, state, __LINE__);*/
/*}*/

/*static void TestRun(scheduler_t *test_scheduler)*/
/*{*/
/*	int state = SUCCESS;*/
/*	*/
/*	state = SchedulerRun(test_scheduler);*/
/*	TestInt(SUCCESS, state, __LINE__);*/
/*}*/

/*static int PrintInt(void *params)*/
/*{*/
/*	printf("%d \n", *(int *)params);*/
/*	*/
/*	return (NO_REPEAT);*/
/*}*/

/*static void VoidCleanUp(void *params)*/
/*{*/
/*	(void)params;*/
/*}*/

/*static void TestSizeT(size_t control, size_t test, int line)*/
/*{*/
/*	if (control != test)*/
/*	{*/
/*		printf("\033[0;31m");*/
/*		printf("Error. failed at line %d\n", line);*/
/*		printf("\033[0m"); */
/*	}*/
/*	else*/
/*	{*/
/*		printf("\033[1;32m");*/
/*		printf("Success!\n");*/
/*		printf("\033[0m"); */
/*	}*/
/*}*/

/*static void TestInt(int control, int test, int line)*/
/*{*/
/*	if (control != test)*/
/*	{*/
/*		printf("\033[0;31m");*/
/*		printf("Error. failed at line %d\n", line);*/
/*		printf("\033[0m"); */
/*	}*/
/*	else*/
/*	{*/
/*		printf("\033[1;32m");*/
/*		printf("Success!\n");*/
/*		printf("\033[0m"); */
/*	}*/
/*}*/

/*******************************************************************************
*Author: Yael 
*******************************************************************************/
#include <string.h> /* strcpy 				*/
#include <stdlib.h> /* system               */

#include "scheduler.h"

void TestCreateAndDestroy();
void TestSimpleIsEmptySizeAddAndRemove();
void TestRun();
void TestRepeatStopAndClear();

int main()
{
	TestCreateAndDestroy();
	TestSimpleIsEmptySizeAddAndRemove();
	TestRun();
	TestRepeatStopAndClear();
	
	return (0);
}

/******************************************************************************
 * 					typedef int (*op_func_t)(void *);
 ******************************************************************************/

int PrintOperation(void *params)
{
	printf("Executing simple print operation: %s\n", (const char *)params);
	return NO_REPEAT;
}

int RepeatPrintOperation(void *params)
{
	printf("Executing simple print operation: %s\n", (const char *)params);
	return REPEAT;
}

int StopSchedule(void *params)
{
	SchedulerStop((scheduler_t *)params);
	return NO_REPEAT;
}

int CowsayOperation(void *params)
{
	char *message = (char *)params;
	char command[256];
	sprintf(command, "cowsay \"%s\"", message);
	system(command);
	return NO_REPEAT;
}

int RepeatCowsayOperation(void *params)
{
	char *message = (char *)params;
	char command[256];
	sprintf(command, "cowsay -f tux  \"%s\"", message);
	system(command);
	return REPEAT;
}

/******************************************************************************
 *					typedef void (*clean_up_t)(void *);
 ******************************************************************************/

void DestroyCowsayTask(void *params)
{
	(void)params;
	printf("deleting cow. goodbye! \n");
}

void NoCleanUp(void *params)
{
	(void)params;
}

/******************************************************************************
 *                       			actual tests
 ******************************************************************************/

void TestCreateAndDestroy()
{
	scheduler_t *scheduler = SchedulerCreate();
	SchedulerDestroy(scheduler);
}

void TestSimpleIsEmptySizeAddAndRemove()
{
	ilrd_uid_t uid = {0};
	void *params = NULL;
	scheduler_t *scheduler = SchedulerCreate();
	assert(SchedulerIsEmpty(scheduler));
	
	params = (void *)"hello!!!";
	uid = SchedulerAdd(scheduler, PrintOperation, params, time(NULL) + 2,
					   0, NoCleanUp, params);
	assert(!UIDIsEqual(uid, bad_uid));
	assert(!SchedulerIsEmpty(scheduler));	
	assert(SchedulerSize(scheduler) == 1);	
	
	assert(SUCCESS == SchedulerRemove(scheduler, uid));
	assert(SchedulerIsEmpty(scheduler));
	
	SchedulerDestroy(scheduler);
}

void TestRun()
{
	ilrd_uid_t uid = {0};
	void *params = NULL;
	scheduler_t *scheduler = SchedulerCreate();
	assert(SchedulerIsEmpty(scheduler));
	
	params = (void *)"hello!!!";
	uid = SchedulerAdd(scheduler, PrintOperation, params, time(NULL) + 2,
					   0, NoCleanUp, params);
	assert(!UIDIsEqual(uid, bad_uid));
	assert(!SchedulerIsEmpty(scheduler));	
	assert(SchedulerSize(scheduler) == 1);	
	
	assert(SUCCESS == SchedulerRun(scheduler));
	
	assert(FAIL == SchedulerRemove(scheduler, uid));
	assert(SchedulerIsEmpty(scheduler));
	
	SchedulerDestroy(scheduler);
}

void TestRepeatStopAndClear()
{
	ilrd_uid_t uid = {0};
	void *params = NULL;
	scheduler_t *scheduler = SchedulerCreate();
	
	params = (void *)"hello!!!";
	uid = SchedulerAdd(scheduler, RepeatPrintOperation, params, time(NULL) + 3,
					   15, NoCleanUp, params);
	assert(!UIDIsEqual(uid, bad_uid));
	
	params = (void *)"there!!!";
	uid = SchedulerAdd(scheduler, RepeatPrintOperation, params, time(NULL),
					   5, NoCleanUp, params);
	assert(!UIDIsEqual(uid, bad_uid));
	
	params = (void *)scheduler;
	uid = SchedulerAdd(scheduler, StopSchedule, params, time(NULL) + 10,
					   0, NoCleanUp, params);
	assert(!UIDIsEqual(uid, bad_uid));
	
	params = (void *)"WAAAK WAAAK WAK This is the best scheduler ever! \n";
	uid = SchedulerAdd(scheduler, RepeatCowsayOperation, params, time(NULL) + 2,
					   20, DestroyCowsayTask, params);
	assert(!UIDIsEqual(uid, bad_uid));
	
	assert(!SchedulerIsEmpty(scheduler));	
	assert(SchedulerSize(scheduler) == 4);	
	
	assert(STOPPED == SchedulerRun(scheduler));
	assert(SchedulerSize(scheduler) == 3);	
	assert(!SchedulerIsEmpty(scheduler));
	
	SchedulerClear(scheduler);
	assert(SchedulerSize(scheduler) == 0);	
	assert(SchedulerIsEmpty(scheduler));
	SchedulerDestroy(scheduler);
}

