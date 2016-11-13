#include "rpncalc.h"

#include <math.h>

double rpn_sum(struct rpn_stack *stat_stack)
{
    if(stat_stack == NULL)
        return -1;
    
    int count = stat_stack->top;
    
    double sum = 0;
    
    for(; count >= 0; count--)
    {
        struct rpn_stack_element *e = stat_stack->contents[count];
        
        if(e == NULL)
            return -1;
        
        sum += e->value.number;
    }
    
    return sum;
}

double rpn_sum_squared(struct rpn_stack *stat_stack)
{
    if(stat_stack == NULL)
        return -1;
    
    int count = stat_stack->top;
    
    double sum = 0;
    
    for(; count >= 0; count--)
    {
        struct rpn_stack_element *e = stat_stack->contents[count];
        
        if(e == NULL)
            return -1;
        
        sum += ((e->value.number) * (e->value.number));
    }
    
    return sum;
}

double rpn_product(struct rpn_stack *stat_stack)
{
    if(stat_stack == NULL)
        return -1;
    
    int count = stat_stack->top;
    
    double sum = 1;
    
    for(; count >= 0; count--)
    {
        struct rpn_stack_element *e = stat_stack->contents[count];
        
        if(e == NULL)
            return -1;
        
        sum = sum * e->value.number;
    }
    
    return sum;
}

double rpn_mean(struct rpn_stack *stat_stack)
{
    if(stat_stack == NULL)
        return -1;
    
    return rpn_sum(stat_stack) / (stat_stack->top + 1);
}

double rpn_variance(struct rpn_stack *stat_stack, int sample)
{
    if(stat_stack == NULL)
        return -1;
    
    int count = stat_stack->top;
    
    double sum = 0;
    double mean = rpn_mean(stat_stack);
    
    for(; count >= 0; count--)
    {
        struct rpn_stack_element *e = stat_stack->contents[count];
        
        if(e == NULL)
            return -1;
        
        double next_value = e->value.number - mean;
        
        sum += next_value * next_value;
    }
    
    if(sample)
        return sum / stat_stack->top;
    else
        return sum / (stat_stack->top + 1);
}


    
    




    
    
