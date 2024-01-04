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
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    SPACE,
    TAB,
    END,
    NUM_OF_EVENTS
}events_t;

static int status = SUCCESS;
static int e_state = WAITING_FOR_OPERAND;

typedef double operator_handler_t(double, double);
typedef char *expression_handler_t(char *, stack_t *, stack_t *);

static int event_lut[ASCII_SIZE] = {OTHER};
static operator_handler_t *operator_lut[NUM_OF_EVENTS] = {0};
static expression_handler_t *function_matrix[NUM_OF_STATES][NUM_OF_EVENTS];

static char *SyntaxError(char *str, stack_t *num_stack, stack_t *oper_stack);						 
static char *PushOperand(char *str, stack_t *num_stack, stack_t *oper_stack);	 
static char *OpenBracket(char *str, stack_t *num_stack, stack_t *oper_stack);
static char *PushOperator(char *str, stack_t *num_stack, stack_t *oper_stack);
static char *CloseBrackets(char *str, stack_t *num_stack, stack_t *oper_stack);
static char *SkipSpaces(char *str, stack_t *num_stack, stack_t *oper_stack);
static char *FinalCalculate(char *str, stack_t *num_stack, stack_t *oper_stack);
						 
static void InitlizeEventLUT();
static void InitlizeOperatorLUT();
static void InitlizeMatrixOfFunctions();

static void ApplyOperation(stack_t *num_stack, stack_t *oper_stack);

static double Addition(double value1, double value2);
static double Subtraction(double value1, double value2);
static double Divide(double value1, double value2);
static double Multiply(double value1, double value2);

status_t Calculate(const char *expression, double *res)
{
	int event = 0;
	char *runner = NULL;
	stack_t *num_stack = NULL;
	stack_t *oper_stack = NULL;
	
    assert(NULL != expression);
    
    runner = (char *)expression;
     
    num_stack = StackCreate(strlen(expression), sizeof(double));
    if (NULL == num_stack)
    {
		return (ALLOCATION_ERROR);
    }
    oper_stack = StackCreate(strlen(expression), sizeof(char));
    if (NULL == num_stack)
    {
		StackDestroy(num_stack);
		
		return (ALLOCATION_ERROR);
    }
    
    InitlizeEventLUT();
    InitlizeOperatorLUT();
    InitlizeMatrixOfFunctions();

	while (END != event && SUCCESS == status)
	{
		event = event_lut[(size_t)(*runner)];
				 
		runner = function_matrix[e_state][event](runner, num_stack, oper_stack); 
	}
	    
   	*res = *(double *)StackPeek(num_stack);
	
	StackDestroy(num_stack);
	StackDestroy(oper_stack);
	
	return (status);
}

static char *SyntaxError(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	double error_result = 0;
	(void)oper_stack;
	
	status = SYNTAX_ERROR;
	
	StackPush(num_stack, &error_result);
	
	return ((char *)str);
}

static char *PushOperand(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	double data = 0;
	char *endptr = NULL;
	(void)oper_stack;
	
	data = strtod(str ,&endptr);
	
	StackPush(num_stack, &data);
			
	e_state = WAITING_FOR_OPERATOR;
	
	return (endptr);
}

static char *OpenBracket(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	char *runner = (char *)str ;
	(void)num_stack;
	
	StackPush(oper_stack, (void *)str);
	
	++runner;
	
	e_state = WAITING_FOR_OPERAND;
	
	return (runner);
}

static char *PushOperator(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	char top_operator = 0;
	char *runner = (char *)str;

	if (TRUE != StackIsEmpty(oper_stack))
	{
		top_operator = *(char *)StackPeek(oper_stack);
		if (event_lut[(size_t)top_operator] >= event_lut[(size_t)*str] && \
			SUCCESS == status)
		{
			ApplyOperation(num_stack, oper_stack);	
		}
	}
	
	StackPush(oper_stack, (void *)str);
	
	++runner;
	
	e_state = WAITING_FOR_OPERAND;
	
	return (runner);
}

static char *CloseBrackets(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	char *runner = (char *)str;
	(void)num_stack;
	(void)oper_stack;
	
	while ('(' != *(char *)StackPeek(oper_stack) && SUCCESS == status)
	{
		ApplyOperation(num_stack, oper_stack);
	}
	StackPop(oper_stack);
	
	++runner;
	
	e_state = WAITING_FOR_OPERATOR;
	
	return (runner);
}

static char *SkipSpaces(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	char *runner = (char *)str;
	(void)num_stack;
	(void)oper_stack;
	
	while (' ' == *runner && '\t' == *runner)
	{
		++runner;
	}

	return (runner);
}

static char *FinalCalculate(char *str, stack_t *num_stack, stack_t *oper_stack)
{
	while (FINAL_RESULT != StackSize(num_stack) && SUCCESS == status)
	{
		ApplyOperation(num_stack, oper_stack);	
	}
	
	return ((char *)str);
}

static void ApplyOperation(stack_t *num_stack, stack_t *oper_stack)
{
	double value1 = 0;
	double value2 = 0;
	double current_result = 0;
	char current_operator = '\0';

	value1 = *(double *)StackPeek(num_stack);
	StackPop(num_stack);

	value2 = *(double *)StackPeek(num_stack);
	StackPop(num_stack);

	current_operator = *(char *)StackPeek(oper_stack);
	StackPop(oper_stack);
	
	if (0 == value1 && '/' == current_operator)
	{
		status = MATH_ERROR;
		return;
	}

	current_result = operator_lut[event_lut[(size_t)current_operator]](value1, value2);

	StackPush(num_stack, &current_result);
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
	operator_lut[PLUS] = Addition;
	operator_lut[MINUS] = Subtraction;
	operator_lut[MULTIPLY] = Multiply;
	operator_lut[DIVIDE] = Divide;
}

static void InitlizeMatrixOfFunctions()
{
    function_matrix[WAITING_FOR_OPERAND][OTHER] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][NUM] = PushOperand;
    function_matrix[WAITING_FOR_OPERAND][PLUS] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][MINUS] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][MULTIPLY] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][DIVIDE] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][OPEN_ROUND_BRACKET] = OpenBracket;
    function_matrix[WAITING_FOR_OPERAND][CLOSE_ROUND_BRACKET] = SyntaxError;
    function_matrix[WAITING_FOR_OPERAND][SPACE] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERAND][TAB] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERAND][END] = SyntaxError;
    
    function_matrix[WAITING_FOR_OPERATOR][OTHER] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][NUM] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][PLUS] = PushOperator;
    function_matrix[WAITING_FOR_OPERATOR][MINUS] = PushOperator;
    function_matrix[WAITING_FOR_OPERATOR][MULTIPLY] = PushOperator;
    function_matrix[WAITING_FOR_OPERATOR][DIVIDE] = PushOperator;
    function_matrix[WAITING_FOR_OPERATOR][OPEN_ROUND_BRACKET] = SyntaxError;
    function_matrix[WAITING_FOR_OPERATOR][CLOSE_ROUND_BRACKET] = CloseBrackets;
    function_matrix[WAITING_FOR_OPERATOR][SPACE] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERATOR][TAB] = SkipSpaces;
    function_matrix[WAITING_FOR_OPERATOR][END] = FinalCalculate;
}
