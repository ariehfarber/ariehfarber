/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:   
*Date: 
*******************************************************************************/
#include <stdlib.h> /*strtod*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/

#include "calculator.h"
#include "stack.h"

#define ASCII_SIZE   256
#define FINAL_RESULT 1
#define TRUE 		 1

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
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    SPACE,
    TAB,
    END,
    NUM_OF_EVENTS
}events_t;

typedef enum 
{
    ADDITION_OPERATOR = PLUS,
    SUBTRACTION_OPERATOR = MINUS,
    MULTIPLY_OPERATOR = MULTIPLY,
    DIVIDE_OPERATOR = DIVIDE,
    NUM_OF_OPERATORS
}operator_t;

typedef double operator_handler_t(double, double);
typedef char *expression_handler_t(const char *, int *, stack_t *, stack_t *);

static int event_lut[ASCII_SIZE] = {OTHER};
static operator_handler_t *operator_lut[NUM_OF_OPERATORS] = {0};
static expression_handler_t *function_matrix[NUM_OF_STATES][NUM_OF_EVENTS];

static char *SyntaxError(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);						 
static char *PushOperand(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack); 	 
static char *PushOpenBracket(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *PushArithmeticOperator(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *PushFactorizationOperator(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *CloseBrackets(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack); 
static char *SkipSpaces(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *CalculateFinalResult(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
						 
static void InitlizeEventLUT();
static void InitlizeOperatorLUT();
static void InitlizeMatrixOfFunctions();

static void ApplyTopOperation(int *status, stack_t *operand_stack, \
							  stack_t *operator_stack);

static double Addition(double value1, double value2);
static double Subtraction(double value1, double value2);
static double Divide(double value1, double value2);
static double Multiply(double value1, double value2);

status_t Calculate(const char *expression, double *res)
{
	static int status = SUCCESS;
	int current_state = WAITING_FOR_OPERAND;
	int event = 0;
	char *runner = NULL;
	stack_t *operand_stack = NULL;
	stack_t *operator_stack = NULL;
	
    assert(NULL != expression);
    
    runner = (char *)expression;
     
    operand_stack = StackCreate(strlen(expression), sizeof(double));
    if (NULL == operand_stack)
    {
		return (ALLOCATION_ERROR);
    }
    operator_stack = StackCreate(strlen(expression), sizeof(char));
    if (NULL == operand_stack)
    {
		StackDestroy(operand_stack);
		
		return (ALLOCATION_ERROR);
    }
    
    InitlizeEventLUT();
    InitlizeOperatorLUT();
    InitlizeMatrixOfFunctions();

	while (END != event && SUCCESS == status)
	{
		event = event_lut[(int)*runner];
				 
		runner = function_matrix[current_state][event](runner, &status, \
										   operand_stack, operator_stack); 
		
		current_state ^= WAITING_FOR_OPERAND ^ WAITING_FOR_OPERATOR;
	}
	    
   	*res = *(double *)StackPeek(operand_stack);
	
	StackDestroy(operand_stack);
	StackDestroy(operator_stack);
	
	return (status);
}

static char *SyntaxError(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	double error_result = 0;
	(void)operator_stack;
	
	*status = SYNTAX_ERROR;
	
	StackPush(operand_stack, &error_result);
	
	return ((char *)str);
}

static char *PushOperand(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	double data = 0;
	char *endptr = NULL;
	(void)status;
	(void)operator_stack;
	
	data = strtod(str ,&endptr);
	
	StackPush(operand_stack, &data);
	
	return (endptr);
}

static char *PushOpenBracket(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = (char *)str ;
	(void)status;
	(void)operator_stack;
	
	StackPush(operand_stack, (void *)str);
	
	++runner;
	
	return (runner);
}

static char *PushArithmeticOperator(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char top_operator = 0;
	char *runner = (char *)str;
	(void)status;
	
	if (TRUE != StackIsEmpty(operator_stack))
	{
		top_operator = *(char *)StackPeek(operator_stack);
		if (event_lut[(size_t)top_operator] >= MULTIPLY_OPERATOR && \
			SUCCESS == status)
		{
			ApplyTopOperation(status, operand_stack, operator_stack);	
		}
	}
	
	StackPush(operator_stack, (void *)str);
	
	++runner;
	
	return (runner);
}

static char *PushFactorizationOperator(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = (char *)str;
	(void)status;
	(void)operand_stack;
	
	StackPush(operator_stack, (void *)str);
	
	++runner;
	
	return (runner);
}

static char *CloseBrackets(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = (char *)str;
	(void)status;
	(void)operand_stack;
	(void)operator_stack;
	
	while ('(' != *(char *)StackPeek(operand_stack) && SUCCESS == status)
	{
		ApplyTopOperation(status, operand_stack, operator_stack);
	}
	StackPop(operand_stack);
	
	++runner;
	
	return (runner);
}

static char *SkipSpaces(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = (char *)str;
	(void)status;
	(void)operand_stack;
	(void)operator_stack;
	
	while (' ' == *runner && '\t' == *runner)
	{
		++runner;
	}

	return (runner);
}

static char *CalculateFinalResult(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	(void)status;

	while (FINAL_RESULT != StackSize(operand_stack) && SUCCESS == status)
	{
		ApplyTopOperation(status, operand_stack, operator_stack);	
	}
	
	return ((char *)str);
}

static void ApplyTopOperation(int *status, stack_t *operand_stack, \
							  stack_t *operator_stack)
{
	double value1 = 0;
	double value2 = 0;
	double current_result = 0;
	char current_operator = '\0';

	value1 = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);

	value2 = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);

	current_operator = *(char *)StackPeek(operator_stack);
	StackPop(operator_stack);
	
	if (0 == value1 && '/' == current_operator)
	{
		*status = MATH_ERROR;
		return;
	}

	current_result = operator_lut[event_lut[(size_t)current_operator]](value1, value2);

	StackPush(operand_stack, &current_result);
}	

static double Addition(double value1, double value2)
{
	return (value2 + value1);
}

static double Subtraction(double value1, double value2)
{
	return (value2 - value1);
}

static double Divide(double value1, double value2)
{
	return (value2 / value1);
}

static double Multiply(double value1, double value2)
{
	return (value2 * value1);
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
	event_lut['+'] = PLUS;
	event_lut['-'] = MINUS;
	event_lut['*'] = MULTIPLY;
	event_lut[ '/'] = DIVIDE;
	event_lut['('] = OPEN_ROUND_BRACKET;
	event_lut[')'] = CLOSE_ROUND_BRACKET;
	event_lut[' '] = SPACE;
	event_lut['\t'] = TAB;
	event_lut['\0'] = END;
}

static void InitlizeOperatorLUT()
{
	operator_lut[ADDITION_OPERATOR] = Addition;
	operator_lut[SUBTRACTION_OPERATOR] = Subtraction;
	operator_lut[MULTIPLY_OPERATOR] = Multiply;
	operator_lut[DIVIDE_OPERATOR] = Divide;
}

static void InitlizeMatrixOfFunctions()
{
    function_matrix[WAITING_FOR_OPERAND][OTHER] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][NUM] = PushOperand;
    function_matrix[WAITING_FOR_OPERAND][PLUS] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][MINUS] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][MULTIPLY] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][DIVIDE] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][OPEN_ROUND_BRACKET] = PushOpenBracket;
    function_matrix[WAITING_FOR_OPERAND][CLOSE_ROUND_BRACKET] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][SPACE] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERAND][TAB] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERAND][END] = SyntaxError;
    
    function_matrix[WAITING_FOR_OPERATOR][OTHER] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][NUM] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][PLUS] = PushArithmeticOperator;
    function_matrix[WAITING_FOR_OPERATOR][MINUS] = PushArithmeticOperator;
    function_matrix[WAITING_FOR_OPERATOR][MULTIPLY] = PushFactorizationOperator;
    function_matrix[WAITING_FOR_OPERATOR][DIVIDE] = PushFactorizationOperator;
    function_matrix[WAITING_FOR_OPERATOR][OPEN_ROUND_BRACKET] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][CLOSE_ROUND_BRACKET] = CloseBrackets;
    function_matrix[WAITING_FOR_OPERATOR][SPACE] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERATOR][TAB] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERATOR][END] = CalculateFinalResult;
}
