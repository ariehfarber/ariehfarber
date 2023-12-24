/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> 	/*malloc, free  */
#include <assert.h> 	/*assert	    */
#include <unistd.h> 	/*sleep		    */
#include <time.h>   	/*time_t, size_t*/

#include "scheduler.h"
#include "pq.h"
#include "task.h"		/*task_t	    */
#include "uid.h"		/*ilrd_uid_t    */

#define TRUE 1
#define FALSE 0
#define ONE_SECOND 1
#define ZERO 0
#define POSITIVE 1
#define NEGATIVE -1
#define RUNNING 1
#define NOT_RUNNING 0


struct scheduler
{
	pq_t *pq;
	size_t is_running;
};

static int CompFunc(void *task1, void *task2);
static pq_t *FetchPQ(scheduler_t *scheduler);
static int WrapperTaskIsMatch(void *task, void *task_uid);

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = {0};
	
	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->pq = PQCreate(CompFunc);
	if (NULL == scheduler->pq)
	{
		free(scheduler);
		return (NULL);
	}
	
	scheduler->is_running = NOT_RUNNING;
	
	return(scheduler);
}

void SchedulerDestroy(scheduler_t *scheduler)
{	
	assert(NULL != scheduler);

	SchedulerClear(scheduler);

	PQDestroy(FetchPQ(scheduler));
	
	free(scheduler);
}

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQIsEmpty(FetchPQ((scheduler_t *)scheduler)) && \
			NOT_RUNNING == scheduler->is_running);
}

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQSize(FetchPQ((scheduler_t *)scheduler)) + scheduler->is_running);
}

ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, 
							op_func_t op_func, 
							void* params, 
							time_t time_to_run, 
							size_t intervals, 
							clean_up_t clean_up_func, 
							void *clean_up_params)
{
	task_t *new_task = NULL;
	int state = SUCCESS;
	
	assert(NULL != scheduler);
	assert(NULL != op_func);
	
	new_task = TaskCreate(op_func, params, time_to_run, intervals, \
						  clean_up_func, clean_up_params);
	if (NULL == new_task)
	{
		return (bad_uid);
	}
	
	state = PQEnqueue(FetchPQ(scheduler), (void *)new_task);
	if (FAIL == state)
	{
		TaskDestroy(new_task);
		return (bad_uid);
	}
	
	return (TaskGetUid(new_task));				  
}

int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{	
	int state = SUCCESS;
	void *task_holder = NULL;
		
	assert(NULL != scheduler);
	
	task_holder = PQErase(FetchPQ(scheduler), WrapperTaskIsMatch, &uid);
	if (NULL == task_holder)
	{
		state = FAIL;
	}
	else
	{
		TaskDestroy((task_t *)task_holder);
	}

	return (state);
}

int SchedulerRun(scheduler_t *scheduler)
{
	void *task_holder = NULL;
	time_t time_to_run;
	int repeat_state = NO_REPEAT;
	int enqueue_state = SUCCESS;
	
	assert(NULL != scheduler);
	
	scheduler->is_running = RUNNING;
	
	while (RUNNING == scheduler->is_running && \
		   TRUE != PQIsEmpty(FetchPQ(scheduler)))
	{
		task_holder = PQPeek(FetchPQ(scheduler));
		if (NULL == task_holder)
		{
			return (FAIL);
		}
		
		time_to_run = TaskGetTimeToRun((task_t *)task_holder);
		
		while (time(NULL) < time_to_run)
		{
			sleep(ONE_SECOND);
		}
		
		task_holder = PQDequeue(FetchPQ(scheduler));
		
		repeat_state = TaskRun((task_t *)task_holder);
		if (REPEAT == repeat_state)
		{
			TaskUpdateTimeToRun((task_t *)task_holder);
			enqueue_state = PQEnqueue(FetchPQ(scheduler), task_holder);
			if (FAIL == enqueue_state)
			{
				scheduler->is_running = NOT_RUNNING;
				return (FAIL);
			}
		}
		else
		{
			TaskDestroy((task_t *)task_holder);
		}
		
		if (NOT_RUNNING == scheduler->is_running)
		{
			return (STOPPED);
		}	
	}
	
	scheduler->is_running = NOT_RUNNING;
	
	return (SUCCESS);
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);	
	
	scheduler->is_running = NOT_RUNNING;
}

void SchedulerClear(scheduler_t *scheduler)
{
	task_t *head_task = NULL;
	
	assert(NULL != scheduler);	
	
	while (TRUE != SchedulerIsEmpty(scheduler))
	{
		head_task = (task_t *)PQPeek(FetchPQ(scheduler));
		SchedulerRemove(scheduler, TaskGetUid(head_task));
	}
}

static int CompFunc(void *task1, void *task2)
{
	if (TRUE == TaskIsBefore((task_t *)task1, (task_t *)task2))
	{
		return (NEGATIVE);
	}
	else if (TRUE == TaskIsBefore((task_t *)task2, (task_t *)task1))
	{
		return (POSITIVE);
	}

	return (ZERO);
}

static pq_t *FetchPQ(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (scheduler->pq);
}

static int WrapperTaskIsMatch(void *existing_task, void *task_uid)
{   
    return (TaskIsMatch((task_t *)existing_task, *(ilrd_uid_t *)task_uid));
}






