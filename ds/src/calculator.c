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

typedef char *handler_t(const char *, int *, stack_t *, stack_t *);

static handler_t *handler_lut[NUM_OF_STATES][NUM_OF_EVENTS];
static int character_table[ASCII_SIZE] = {0};

static char *SyntaxError(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *CheckStack(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack); 							 
static char *OperandPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack); 	 
static char *BracketPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *ArithmeticPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *FactorizationPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *CloseBrackets(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack); 
static char *SkipSpaces(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static char *CalculateFinalResult(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack);
static void InitlizeEventLUT();
static void InitlizeHandlerLUT();
static double add(double value1, double value2);
static double subtract(double value1, double value2);
static double divide(double value1, double value2);
static double multiply(double value1, double value2);

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
    operator_stack = StackCreate(strlen(expression), sizeof(char));
    
    InitlizeEventLUT();
    InitlizeHandlerLUT();
    
    event = character_table[(int)*expression];
    if (NUM != event)
    {
    	return (SYNTAX_ERROR);
    }

	while (END != event && SUCCESS == status)
	{
		event = character_table[(int)*runner];
				 
		runner = handler_lut[current_state][event](runner, &status, \
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
	*status = SYNTAX_ERROR;
	(void)operand_stack;
	(void)operator_stack;
	
	return ((char *)str);
}

static char *CheckStack(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	(void)status;
	(void)operand_stack;
	(void)operator_stack;
	
	return ((char *)str);
}

static char *OperandPush(const char *str, int *status, \
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

static char *BracketPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = NULL;
	(void)status;
	(void)operator_stack;
	
	StackPush(operand_stack, (void *)str);
	
	runner = (char *)str + 1;
	
	return (runner);
}

static char *ArithmeticPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	char *runner = NULL;
	(void)status;
	(void)operand_stack;
	
	StackPush(operator_stack, (void *)str);
	
	runner = (char *)str + 1;
	
	return (runner);
}

static char *FactorizationPush(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	(void)status;
	(void)operand_stack;
	(void)operator_stack;
	
	return ((char *)str);
}

static char *CloseBrackets(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	(void)status;
	(void)operand_stack;
	(void)operator_stack;
	
	return ((char *)str);
}

static char *SkipSpaces(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	(void)status;
	(void)operand_stack;
	(void)operator_stack;

	return ((char *)str);
}

static char *CalculateFinalResult(const char *str, int *status, \
						 stack_t *operand_stack, stack_t *operator_stack)
{
	double value1 = 0;
	double value2 = 0;
	double current_result = 0;
	char current_operator = '\0';
	(void)status;

	while (FINAL_RESULT != StackSize(operand_stack))
	{
		value1 = *(double *)StackPeek(operand_stack);
		StackPop(operand_stack);
		
		value2 = *(double *)StackPeek(operand_stack);
		StackPop(operand_stack);

		current_operator = *(char *)StackPeek(operator_stack);
		StackPop(operator_stack);
		
		current_result = add(value1, value2); /*create lut for operations*/
		
		StackPush(operand_stack, &current_result);
	}
	
	return ((char *)str);
}

static double add(double value1, double value2)
{
	return (value1 + value2);
}

static double subtract(double value1, double value2)
{
	return (value1 - value2);
}

static double divide(double value1, double value2)
{
	return (value1 / value2);
}

static double multiply(double value1, double value2)
{
	return (value1 * value2);
}

static void InitlizeEventLUT()
{
	size_t i = 0;
	char num_runner = '0';
	
	for (i = 0; i <= 9; ++i)
	{
		character_table[(int)num_runner] = NUM;
		++num_runner;
	}
	
	character_table['+'] = PLUS;
	character_table['-'] = MINUS;
	character_table['*'] = MULTIPLY;
	character_table[ '/'] = DIVIDE;
	character_table['('] = OPEN_ROUND_BRACKET;
	character_table[')'] = CLOSE_ROUND_BRACKET;
	character_table[' '] = SPACE;
	character_table['\t'] = TAB;
	character_table['\0'] = END;
}

static void InitlizeHandlerLUT()
{
    handler_lut[WAITING_FOR_OPERAND][OTHER] = SyntaxError;
    handler_lut[WAITING_FOR_OPERAND][NUM] = OperandPush;
    handler_lut[WAITING_FOR_OPERAND][PLUS] = CheckStack;
    handler_lut[WAITING_FOR_OPERAND][MINUS] = CheckStack;
    handler_lut[WAITING_FOR_OPERAND][MULTIPLY] = SyntaxError;
    handler_lut[WAITING_FOR_OPERAND][DIVIDE] = SyntaxError;
    handler_lut[WAITING_FOR_OPERAND][OPEN_ROUND_BRACKET] = BracketPush;
    handler_lut[WAITING_FOR_OPERAND][CLOSE_ROUND_BRACKET] = SyntaxError;
    handler_lut[WAITING_FOR_OPERAND][SPACE] = SkipSpaces;
    handler_lut[WAITING_FOR_OPERAND][TAB] = SkipSpaces;
    handler_lut[WAITING_FOR_OPERAND][END] = SyntaxError;
    
    handler_lut[WAITING_FOR_OPERATOR][OTHER] = SyntaxError;
    handler_lut[WAITING_FOR_OPERATOR][NUM] = SyntaxError;
    handler_lut[WAITING_FOR_OPERATOR][PLUS] = ArithmeticPush;
    handler_lut[WAITING_FOR_OPERATOR][MINUS] = ArithmeticPush;
    handler_lut[WAITING_FOR_OPERATOR][MULTIPLY] = FactorizationPush;
    handler_lut[WAITING_FOR_OPERATOR][DIVIDE] = FactorizationPush;
    handler_lut[WAITING_FOR_OPERATOR][OPEN_ROUND_BRACKET] = SyntaxError;
    handler_lut[WAITING_FOR_OPERATOR][CLOSE_ROUND_BRACKET] = CloseBrackets;
    handler_lut[WAITING_FOR_OPERATOR][SPACE] = SkipSpaces;
    handler_lut[WAITING_FOR_OPERATOR][TAB] = SkipSpaces;
    handler_lut[WAITING_FOR_OPERATOR][END] = CalculateFinalResult;
}
