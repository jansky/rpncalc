#include "rpncalc.h"

double rpn_eval_stack(struct rpn_stack *func, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode)
{
    if(func == NULL || stat_stack == NULL || mode == NULL)
        return 0;
    
    int i = func->top;
    
    for(; i >= 0; i--)
    {
        struct rpn_stack_element *e = func->contents[i];
        
        if(e == NULL)
            return 0;
        
        if(e->e_type != ET_STRING || e->value.str == NULL)
            return 0;
        
        if(rpn_evaluate_token(e->value.str, stack, stat_stack, mode) != 0)
            return 0;
    }
    
    // Get the final result
    
    struct rpn_stack_element *result = rpn_stack_pop(stack);
    
    if(result == NULL)
        return 0;
    
    if(result->e_type != ET_NUMBER)
        return 0;
    
    return result->value.number;
}

struct rpn_stack *rpn_create_function_stack(struct rpn_stack *stack)
{
    if(stack == NULL)
        return NULL;
    
    // Check for mark
    
    struct rpn_stack_element *mark = rpn_stack_pop(stack);
    
    if(mark == NULL)
        return NULL;
    
    if(mark->e_type != ET_MARK)
        return NULL;
    
    // See how many elements our function stack will need
    
    int i = stack->top;
    
    int e_count = 0;
    
    int reached_mark = 0;
    
    for(; i >= 0; i--)
    {
        struct rpn_stack_element *e = stack->contents[i];
        
        if(e == NULL)
            return NULL;
        
        if(e->e_type == ET_MARK)
        {
            reached_mark = 1;
            break;
        }
        
        if(e->e_type != ET_STRING || e->value.str == NULL) // Do some data validation
            return NULL;
        
        e_count++;
    }
    
    if(e_count == 0 || reached_mark == 0)
        return NULL;
    
    // Create the new function stack
    
    struct rpn_stack *func = rpn_stack_init(e_count);
    
    if(func == NULL)
        return NULL;
    
    int j = 0;
    
    for(; j < e_count; j++)
    {
        if(rpn_stack_push(func, rpn_stack_pop(stack)) != 0)
            return NULL;
    }
    
    rpn_stack_pop(stack); // Get rid of the last mark
    
    return func;
}
        
    
        
    
