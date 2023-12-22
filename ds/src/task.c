/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
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

