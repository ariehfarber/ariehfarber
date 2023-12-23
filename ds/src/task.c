/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free  */
#include <assert.h> /*assert	    */
#include <time.h>   /*time_t, size_t*/

#include "uid.h"	/*ilrd_uid_t    */
#include "task.h"

struct task
{
	ilrd_uid_t uid;
	op_func_t op_func;
	void *params;
	clean_up_t clean_up_func;
	void *clean_up_params;
	time_t time_to_run;
	size_t interval;
};

task_t *TaskCreate(op_func_t op_func, void* params,
				   clean_up_t clean_up_func, void *clean_up_params,
				   time_t time_to_run, size_t intervals)
{
	task_t *task = NULL;
	
	assert(NULL != op_func);
	assert(NULL != clean_up_func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return (NULL);
	}
	
	task->uid = UIDCreate();
	task->op_func = op_func;
	task->params = params;
	task->clean_up_func = clean_up_func;
	task->clean_up_params = clean_up_params;
	task->time_to_run = time_to_run;
	task->interval = intervals;
	
	return (task);
}

void TaskDestroy(task_t *task)
{
	free(task);
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	return (task->uid);
}

/*int TaskRun(task_t *task)*/
/*{*/

/*}*/

time_t TaskGetTimeToRun(const task_t *task)
{
	return (task->time_to_run);
}

/*int TaskIsBefore(const task_t *task1,const task_t *task2)*/
/*{*/

/*}*/

/*int TaskIsMatch(const task_t *task,const ilrd_uid_t uid)*/
/*{*/

/*}*/

/*void TaskUpdateTimeToRun(task_t *task)*/
/*{*/

/*}*/





