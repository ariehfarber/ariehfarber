/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov  
*Date: 07/01/2024
*******************************************************************************/
#include <stdlib.h> /*strtod */
#include <string.h> /*strlen */
#include <assert.h> /*assert */
#include <math.h>   /*pow    */
#include <ctype.h>  /*isspace*/

#include "calculator.h"
#include "stack.h"
#include "ds_utils.h" /*TRUE, FALSE*/

#define FINAL_STACK_SIZE 1
#define ERROR_RESULT 	 0

typedef enum 
{
    WAITING_FOR_OPERAND = 0,
    WAITING_FOR_OPERATOR,
    NUM_OF_STATES
}state_t;

typedef enum 
{
    OTHER = 0,
    NUM,
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
	EXPONENT,
    SPACE,
	NULL_TERMINATOR,
    ACCEPTED,
    NUM_OF_EVENTS
}events_t;

typedef struct manager
{
	state_t state;
	events_t event;
	stack_t *operand_stack;
	stack_t *operator_stack;
}manager_t;

typedef status_t operator_handler_t(double *, double, double);
typedef status_t transition_handler_t(char **, manager_t *);

static events_t event_lut[ASCII_SIZE] = {OTHER};
static operator_handler_t *operator_lut[NUM_OF_EVENTS] = {OTHER};
static transition_handler_t *transition_matrix[NUM_OF_STATES][NUM_OF_EVENTS];

static status_t ErrorInSyntax(char **expression, manager_t *manager);						 
static status_t PushOperand(char **expression, manager_t *manager);		 
static status_t PushBracket(char **expression, manager_t *manager);	
static status_t PushOperator(char **expression, manager_t *manager);	
static status_t CloseBrackets(char **expression, manager_t *manager);	
static status_t SkipSpaces(char **expression, manager_t *manager);	
static status_t FinalOperation(char **expression, manager_t *manager);	
static void SetManager(char **expression, manager_t *manager, state_t state);

static status_t InitALL(const char **expression, manager_t **manager);					 
static void InitlizeEventLUT();
static void InitlizeOperatorLUT();
static void InitlizeMatrixOfFunctions();
static void DestroyAll(manager_t *manager);

static status_t ApplyOperation(manager_t *manager);
static status_t Addition(double *current_res, double val1, double val2);
static status_t Subtraction(double *current_res, double val1, double val2);
static status_t Divide(double *current_res, double val1, double val2);
static status_t Multiply(double *current_res, double val1, double val2);
static status_t Pow(double *current_res, double val1, double val2);

status_t Calculate(const char *expression, double *res)
{
	status_t status = SUCCESS;
	manager_t *manager = NULL;
    
	assert(NULL != expression);

	status = InitALL(&expression, &manager);

	while (ACCEPTED != manager->event && SUCCESS == status)
	{
		status = transition_matrix[manager->state][manager->event]\
		((char **)&expression, manager); 
	}

	/*allocation error? res needs to be 0*/
	*res = *(double *)StackPeek(manager->operand_stack);
	DestroyAll(manager);
	
	return (status);
}

static status_t ErrorInSyntax(char **expression, manager_t *manager)
{
	double error_res = ERROR_RESULT;
	(void)expression;

	StackPush(manager->operand_stack, &error_res);
	
	return (SYNTAX_ERROR);
}

static status_t PushOperand(char **expression, manager_t *manager)
{
	double data = 0;
	char *endptr = NULL;
	
	data = strtod(*expression ,&endptr);
	if (*expression == endptr)
	{
		return (ErrorInSyntax(expression, manager));
	}

	*expression = endptr;
	SetManager(expression, manager, WAITING_FOR_OPERATOR);	
	StackPush(manager->operand_stack, &data);	

	return (SUCCESS);
}

static status_t PushBracket(char **expression, manager_t *manager)
{
	char multiplication = '*';

	if (manager->state == WAITING_FOR_OPERATOR)
	{
		StackPush(manager->operator_stack, &multiplication);
	}
	
	StackPush(manager->operator_stack, (void *)*expression);
	
	++*expression;
	
	SetManager(expression, manager, WAITING_FOR_OPERAND);	
	
	return (SUCCESS);
}

static status_t PushOperator(char **expression, manager_t *manager)
{
	status_t status = SUCCESS;
	
	while (FALSE == StackIsEmpty(manager->operator_stack) && \
	SUCCESS == status &&  \
	event_lut[(events_t)*(char *)StackPeek(manager->operator_stack)] >= \
	event_lut[(size_t)**expression])
	{
		status = ApplyOperation(manager);	
	}

	StackPush(manager->operator_stack, (void *)*expression);
	
	++*expression;
	
	SetManager(expression, manager, WAITING_FOR_OPERAND);	
	
	return (status);
}

static status_t CloseBrackets(char **expression, manager_t *manager)
{
	char multiplication = '*';
	status_t status = SUCCESS;

	while (FALSE == StackIsEmpty(manager->operator_stack) && \
		   SUCCESS == status && \
		   '(' != *(char *)StackPeek(manager->operator_stack))
    {
        status = ApplyOperation(manager);
    }

	if (TRUE == StackIsEmpty(manager->operator_stack))
	{
        return (ErrorInSyntax(expression, manager));
	}
    StackPop(manager->operator_stack);
 
	++*expression;

	if ('0' <= **expression && '9' >= **expression)
	{
		StackPush(manager->operator_stack, &multiplication);
		SetManager(expression, manager, WAITING_FOR_OPERAND);	
	}
	else
	{
		SetManager(expression, manager, WAITING_FOR_OPERATOR);	
	}

	return (status);
}

static status_t SkipSpaces(char **expression, manager_t *manager)
{
	while (FALSE != isspace((int)**expression))
	{
		++*expression;
	}

	manager->event = event_lut[(size_t)**expression];

	return (SUCCESS);
}

static status_t FinalOperation(char **expression, manager_t *manager)
{
	status_t status = SUCCESS;
	
	while (SUCCESS == status && \
		   FINAL_STACK_SIZE != StackSize(manager->operand_stack))
	{
		if ('(' == *(char *)StackPeek(manager->operator_stack))
		{
			return (ErrorInSyntax(expression, manager));
		}
		status = ApplyOperation(manager);	
	}

	manager->event = ACCEPTED;
	
	return (status);
}

static void SetManager(char **expression, manager_t *manager, state_t state)
{
	manager->state = state;
	manager->event = event_lut[(size_t)**expression];
}

static status_t ApplyOperation(manager_t *manager)
{
	double val1 = 0;
	double val2 = 0;
	double current_res = 0;
	char operator = '\0';
	status_t status = SUCCESS;

	val2 = *(double *)StackPeek(manager->operand_stack);
	StackPop(manager->operand_stack);

	operator = *(char *)StackPeek(manager->operator_stack);
	StackPop(manager->operator_stack);

	val1 = *(double *)StackPeek(manager->operand_stack);
	StackPop(manager->operand_stack);

	status = operator_lut[event_lut[(size_t)operator]](&current_res, val1, val2);

	StackPush(manager->operand_stack, &current_res);

	return (status);
}

static status_t Addition(double *current_res, double val1, double val2)
{
	*current_res = val1 + val2;
	
	return (SUCCESS);
}

static status_t Subtraction(double *current_res, double val1, double val2)
{
	*current_res = val1 - val2;
	
	return (SUCCESS);
}

static status_t Divide(double *current_res, double val1, double val2)
{
	if (0 == val2)
	{
		return (MATH_ERROR);
	}

	*current_res = val1 / val2;

	return (SUCCESS);
}

static status_t Multiply(double *current_res, double val1, double val2)
{
	*current_res = val1 * val2;

	return (SUCCESS);
}

static status_t Pow(double *current_res, double val1, double val2)
{
	if (val1 < 0 && fmod(val2, 1) != 0)
	{
		return (MATH_ERROR);
	}
	if (0 == val1 && 0 >= val2)
	{
		return (MATH_ERROR);
	}

	*current_res = pow(val1, val2);
	
	return (SUCCESS);
}

static void DestroyAll(manager_t *manager)
{
	StackDestroy(manager->operand_stack);
	StackDestroy(manager->operator_stack);

	free(manager);
}

static status_t InitALL(const char **expression, manager_t **manager)
{
	size_t stack_size = strlen(*expression);

	*manager = (manager_t *)malloc(sizeof(manager_t));
    if (NULL == *manager)
    {
        return (ALLOCATION_ERROR);
    }

	(*manager)->operand_stack = StackCreate(stack_size, sizeof(double));
    if (NULL == (*manager)->operand_stack)
    {
        free (*manager);
		return (ALLOCATION_ERROR);
    }

    (*manager)->operator_stack = StackCreate(stack_size, sizeof(char));
    if (NULL == (*manager)->operator_stack)
    {
        free (*manager);
		StackDestroy((*manager)->operator_stack);
		return (ALLOCATION_ERROR);
    }

	InitlizeEventLUT();
    InitlizeOperatorLUT();
    InitlizeMatrixOfFunctions();

    (*manager)->state = WAITING_FOR_OPERAND;
	(*manager)->event = event_lut[(size_t)**expression];

    return (SUCCESS);
}

static void InitlizeEventLUT()
{
	event_lut['0'] = NUM;
	event_lut['1'] = NUM;
	event_lut['2'] = NUM;
	event_lut['3'] = NUM;
	event_lut['4'] = NUM;
	event_lut['5'] = NUM;
	event_lut['6'] = NUM;
	event_lut['7'] = NUM;
	event_lut['8'] = NUM;
	event_lut['9'] = NUM;
	event_lut['('] = OPEN_ROUND_BRACKET;
	event_lut[')'] = CLOSE_ROUND_BRACKET;
	event_lut['+'] = PLUS;
	event_lut['-'] = MINUS;
	event_lut['*'] = MULTIPLY;
	event_lut[ '/'] = DIVIDE;
	event_lut['^'] = EXPONENT;
	event_lut[' '] = SPACE;
	event_lut['\t'] = SPACE;
	event_lut['\n'] = SPACE;
	event_lut['\0'] = NULL_TERMINATOR;
}

static void InitlizeOperatorLUT()
{
	operator_lut[PLUS] = Addition;
	operator_lut[MINUS] = Subtraction;
	operator_lut[MULTIPLY] = Multiply;
	operator_lut[DIVIDE] = Divide;
	operator_lut[EXPONENT] = Pow;
}

static void InitlizeMatrixOfFunctions()
{
    transition_matrix[WAITING_FOR_OPERAND][OTHER] = ErrorInSyntax;
    transition_matrix[WAITING_FOR_OPERAND][NUM] = PushOperand;
	transition_matrix[WAITING_FOR_OPERAND][OPEN_ROUND_BRACKET] = PushBracket;
    transition_matrix[WAITING_FOR_OPERAND][CLOSE_ROUND_BRACKET] = CloseBrackets;
    transition_matrix[WAITING_FOR_OPERAND][PLUS] = PushOperand;
    transition_matrix[WAITING_FOR_OPERAND][MINUS] = PushOperand;
    transition_matrix[WAITING_FOR_OPERAND][MULTIPLY] = ErrorInSyntax;
    transition_matrix[WAITING_FOR_OPERAND][DIVIDE] = ErrorInSyntax;
	transition_matrix[WAITING_FOR_OPERAND][EXPONENT] = ErrorInSyntax;
    transition_matrix[WAITING_FOR_OPERAND][SPACE] = SkipSpaces;
    transition_matrix[WAITING_FOR_OPERAND][NULL_TERMINATOR] = ErrorInSyntax;
    
    transition_matrix[WAITING_FOR_OPERATOR][OTHER] = ErrorInSyntax;
    transition_matrix[WAITING_FOR_OPERATOR][NUM] = ErrorInSyntax;
    transition_matrix[WAITING_FOR_OPERATOR][OPEN_ROUND_BRACKET] = PushBracket;
    transition_matrix[WAITING_FOR_OPERATOR][CLOSE_ROUND_BRACKET] = CloseBrackets;
    transition_matrix[WAITING_FOR_OPERATOR][PLUS] = PushOperator;
    transition_matrix[WAITING_FOR_OPERATOR][MINUS] = PushOperator;
    transition_matrix[WAITING_FOR_OPERATOR][MULTIPLY] = PushOperator;
    transition_matrix[WAITING_FOR_OPERATOR][DIVIDE] = PushOperator;
	transition_matrix[WAITING_FOR_OPERATOR][EXPONENT] = PushOperator;
    transition_matrix[WAITING_FOR_OPERATOR][SPACE] = SkipSpaces;
    transition_matrix[WAITING_FOR_OPERATOR][NULL_TERMINATOR] = FinalOperation;
}
