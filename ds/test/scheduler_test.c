/*******************************************************************************
*Author: Yael 
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcpy*/
#include <stdlib.h> /*system*/
#include <assert.h> /*assert*/



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
	int ret_val = 0;
	
	sprintf(command, "cowsay \"%s\"", message);
	ret_val = system(command);
	if (0 != ret_val)
	{
		printf("Command failed with return value: %d\n", ret_val);
	}
	
	return NO_REPEAT;
}

int RepeatCowsayOperation(void *params)
{
	char *message = (char *)params;
	char command[256];
	int ret_val = 0;
	
	sprintf(command, "cowsay -f tux  \"%s\"", message);
	ret_val = system(command);
	if (0 != ret_val)
	{
		printf("Command failed with return value: %d\n", ret_val);
	}
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

