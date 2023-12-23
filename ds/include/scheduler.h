/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h> /*time_t, size_t*/

#include "uid.h"  /*ilrd_uid_t    */
#include "task.h" 

typedef struct scheduler scheduler_t;

enum return_values
{
	FAIL = -1,
	SUCCESS = 0,
	STOPPED = 1
};

/*******************************************************************************
*Description: Creates a new scheduler.
*Return Value: Pointer to the created scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
*******************************************************************************/
scheduler_t *SchedulerCreate(void);

/*******************************************************************************
*Description: Destroys the given scheduler.
*Parameters: Pointer to a scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler);

/*******************************************************************************
*Description: Checks whether a scheduler is empty.
*Parameters: Pointer to a scheduler.
*Return Value: 1 - If scheduler Is Empty
*              0 - Otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int SchedulerIsEmpty(const scheduler_t *scheduler);

/*******************************************************************************
*Description: Gets the number of tasks in the scheduler 
*             (indcluding running task).
*Parameters: Pointer to the scheduler.
*Return Value: Number of tasks.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
size_t SchedulerSize(const scheduler_t *scheduler);

/*******************************************************************************
*Description: Adds a task to the scheduler.
*Parameters: Scheduler, 
*            op_func - pointer to the operation function,
*            params -  params for the operation function,
*            time_to_run - the scheduled time of the new task,
*            intervals - seconds between tasks repeatitions,
*            clean_up_func - pointer to the cleaning function,
*            clean_up_params - params for the cleaning function.
*Return Value: UID of the added task.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, 
							op_func_t op_func, 
							void* params, 
							clean_up_t clean_up_func, 
							void *clean_up_params,
							time_t time_to_run, 
							size_t intervals);

/*******************************************************************************
*Description: Remove task that matches the given UID.
*Parameters: Pointer to the scheduler and UID.
*Return Value: Status (FAIL,SUCCESS)
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid);

/*******************************************************************************
*Description: Runs all the tasks in the scheduler.
*Parameters: None.
*Return Value: Status (FAIL, SUCCESS, STOPPED).
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int SchedulerRun(scheduler_t *scheduler);

/*******************************************************************************
*Description: Stops the schedulers execution.
*Parameters: Pointer to a scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
void SchedulerStop(scheduler_t *scheduler);

/*******************************************************************************
*Description: Clears the tasks of the scheduler.
*Parameters: Pointer to the Scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
void SchedulerClear(scheduler_t *scheduler);

#endif /*__SCHEDULER_H__*/
