/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */
#include <string.h> /*memcmp	  */

#include "scheduler.h"
#include "pq.h"
#include "task.h"

#define TRUE 1
#define FALSE 0

struct scheduler
{
	pq_t *pq;
	size_t is_running;
};

static int CompFuncTimeT(void *existing_time, void *insert_time);
static pq_t *FetchPQ(scheduler_t *scheduler);
static int IsMatchTask(void *task, void *task_uid);

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = {0};
	
	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->pq = PQCreate(CompFuncTimeT);
	if (NULL == scheduler->pq)
	{
		free(scheduler);
		return (NULL);
	}
	
	scheduler->is_running = 0;
	
	return(scheduler);
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	SchedulerClear(scheduler);
	
	assert(NULL != scheduler);

	PQDestroy(FetchPQ(scheduler));
}

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQIsEmpty(FetchPQ((scheduler_t *)scheduler)));
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
	assert(NULL != clean_up_func);
	
	new_task = TaskCreate(op_func, params, time_to_run, intervals, \
						  clean_up_func, clean_up_params);
	if (NULL == new_task)
	{
		return (bad_uid);
	}
	
	state = PQEnqueue(FetchPQ(scheduler), &new_task);
	if (FAIL == state)
	{
		return (bad_uid);
	}
	
	return (TaskGetUid(new_task));				  
}

int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{	
	int state = SUCCESS;
	void *task_holder = NULL;
		
	assert(NULL != scheduler);
	
	task_holder = PQErase(FetchPQ(scheduler), IsMatchTask, &uid);
	if (NULL == task_holder)
	{
		state = FAIL;
	}
	
	TaskDestroy((task_t *)task_holder);
	
	return (state);
}

int SchedulerRun(scheduler_t *scheduler)
{
	void *task_holder = NULL;
	time_t run_time = time(0);
	
	assert(NULL != scheduler);
	
	task_holder = PQPeek(FetchPQ(scheduler));
	
	run_time = TaskGetTimeToRun((task_t *)task_holder);
}

/*void SchedulerStop(scheduler_t *scheduler)*/
/*{*/

/*}*/

void SchedulerClear(scheduler_t *scheduler)
{
	TaskDestroy(PQDequeue(FetchPQ(scheduler)));
}

static int CompFuncTimeT(void *existing_time, void *insert_time)
{
	return (*(time_t *)existing_time - *(time_t *)insert_time);
}

static pq_t *FetchPQ(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (scheduler->pq);
}

static int IsMatchTask(void *existing_task, void *task_uid)
{
    ilrd_uid_t existing_uid = TaskGetUid((task_t *)existing_task);
    
    return (SUCCESS == memcmp(&existing_uid, task_uid, sizeof(ilrd_uid_t)));
}








