#include "rpncalc.h"
#include <stdlib.h>

struct rpn_num_stack *rpn_num_stack_init(size_t max_size)
{
	struct rpn_num_stack *ns = malloc(sizeof(struct rpn_num_stack));
    
    if(ns == NULL)
        return NULL;
        
    ns->contents = malloc(sizeof(int) * max_size);
    
    if(ns->contents == NULL)
        return NULL;
    
    ns->max_size = max_size;
    
    ns->top = -1;
    
    return ns;
}

int rpn_num_stack_destroy(struct rpn_num_stack *stack)
{
	if(stack == NULL)
        return -1;
    
    free(stack->contents);
    
    free(stack);
    
    return 0;
}

int rpn_num_stack_push(struct rpn_num_stack *stack, int element)
{
	if(stack == NULL)
        return -1;
    
    if(rpn_num_stack_is_full(stack))
        return 1;
    
    stack->contents[++stack->top] = element;
    
    return 0;
}

int rpn_num_stack_is_empty(struct rpn_num_stack *stack)
{
	if(stack == NULL)
        return -1;
    
    return stack->top < 0;
}

int rpn_num_stack_is_full(struct rpn_num_stack *stack)
{
	if(stack == NULL)
        return -1;
    
    return stack->top >= (stack->max_size - 1);
}

int rpn_num_stack_pop(struct rpn_num_stack *stack)
{
	if(stack == NULL)
        return -1;
    
    if(rpn_num_stack_is_empty(stack))
        return -1;
    
    return stack->contents[stack->top--];
}

int rpn_num_stack_peek(struct rpn_num_stack *stack)
{
	
	if(stack == NULL)
        return -1;
    
    if(rpn_num_stack_is_empty(stack))
        return -1;
    
    return stack->contents[stack->top];
}
