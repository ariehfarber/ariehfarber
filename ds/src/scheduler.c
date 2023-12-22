/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */


#include "pq.h"
#include "task.h"
#include "scheduler.h"

struct scheduler
{
	pq_t *pq;
	int is_running;
};

static int CompFuncTimeT(void *existing_time, void *insert_time);
static pq_t *FetchPQ(scheduler_t *scheduler);

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

	PQDestroy(FetchPQ(scheduler));
}

/*int SchedulerIsEmpty(const scheduler_t *scheduler)*/
/*{*/

/*}*/

/*size_t SchedulerSize(const scheduler_t *scheduler)*/
/*{*/

/*}*/

/*ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, */
/*							op_func_t op_func, */
/*							void* params, */
/*							time_t time_to_run, */
/*							size_t intervals, */
/*							clean_up_t clean_up_func, */
/*							void *clean_up_params)*/
/*{*/

/*}*/

/*int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)*/
/*{*/

/*}*/

/*int SchedulerRun(scheduler_t *scheduler)*/
/*{*/

/*}*/

/*void SchedulerStop(const scheduler_t *scheduler)*/
/*{*/

/*}*/

/*void SchedulerClear(scheduler_t *scheduler)*/
/*{*/

/*}*/

static int CompFuncTimeT(void *existing_time, void *insert_time)
{
	return (*(time_t *)existing_time - *(time_t *)insert_time);
}

static pq_t *FetchPQ(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (scheduler->pq);
}
