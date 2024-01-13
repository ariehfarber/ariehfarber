/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Alon Sitman 
*Date: 24/12/2023
*******************************************************************************/
#include <stdlib.h> /*malloc, free, size_t  */
#include <assert.h> /*assert	    		*/
#include <time.h>   /*time_t				*/

#include "task.h"
#include "ds_utils.h" /*TRUE*/

struct task
{
	ilrd_uid_t uid;
	op_func_t op_func;
	void *params;
	clean_up_t clean_up_func;
	void *clean_up_params;
	time_t time_to_run;
	size_t intervals;
};

task_t *TaskCreate(op_func_t op_func, void* params, 
                   time_t time_to_run, size_t intervals, 
				   clean_up_t clean_up_func, void *clean_up_params)
{
	task_t *task = NULL;
	
	assert(NULL != op_func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return (NULL);
	}
	
	task->uid = UIDCreate();
	if (TRUE == UIDIsEqual(TaskGetUid((task_t *)task), bad_uid))
	{
		free(task);
		
		return (NULL);
	}
	
	task->op_func = op_func;
	task->params = params;
	task->time_to_run = time_to_run;
	task->intervals = intervals;
	task->clean_up_func = clean_up_func;
	task->clean_up_params = clean_up_params;

	return (task);
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	if (NULL != task->clean_up_func)
	{
		task->clean_up_func(task->clean_up_params);
	}

	free(task);
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uid);
}

int TaskRun(task_t *task)
{
	assert(NULL != task);
	
	return (task->op_func(task->params));
}

time_t TaskGetTimeToRun(const task_t *task)
{
	assert(NULL != task);

	return (task->time_to_run);
}

int TaskIsBefore(const task_t *task1, const task_t *task2)
{
	time_t time1;
	time_t time2;
	
	assert(NULL != task1);
	assert(NULL != task2);
	
	time1 = TaskGetTimeToRun(task1); 
	time2 = TaskGetTimeToRun(task2);
	
	return (time1 < time2);
}

int TaskIsMatch(const task_t *task, const ilrd_uid_t uid)
{
	assert(NULL != task);
	
	return (UIDIsEqual(TaskGetUid((task_t *)task), uid));
}

void TaskUpdateTimeToRun(task_t *task)
{
	assert(NULL != task);
	
	task->time_to_run += task->intervals;
}
