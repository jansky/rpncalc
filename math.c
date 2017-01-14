#include "rpncalc.h"
#include <math.h>
#include <stdio.h>

double rpn_factorial(double number)
{
    int num = (int)round(number);
    
    if(num == 1)
        return num;
    else
        return num * rpn_factorial(num - 1);
}

double rpn_choose(double n, double r)
{
	int ni = (int)round(n);
	int ri = (int)round(r);
	
	if(ni - ri < ri)
		return rpn_choose(ni, ni - ri);
	
	int top = 1;
	
	
	int i = 0;
	
	int top_next_multiplier = ni;
	
	for(; i < ri; i++)
	{
	    top = top * top_next_multiplier;
	    
	    top_next_multiplier--;
	}
	
	return top / rpn_factorial(ri);
}

double rpn_permute(double n, double r)
{
    int start = 1;
    
    int ri = (int)round(r);
    int ni = (int)round(n);
    
    int i = 0;
    
    for(; i < ri; i++)
    {
        start = start * ni;
        ni--;
    }
    
    return start;
}

double rpn_nderiv(struct rpn_stack *func, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin *plugin_root, struct rpn_plugin_functions *functions, double x, double dv)
{
    if(func == NULL || stack == NULL || stat_stack == NULL || mode == NULL)
        return 0;
    
    double rise = 0;
    
    mode->x = x + dv;
    
    
    
    rise = rpn_eval_stack(func, stack, stat_stack, mode, plugin_root, functions);
    
    
    
    mode->x = x;
    
   
    
    rise = rise - rpn_eval_stack(func, stack, stat_stack, mode, plugin_root, functions);
    
   
    
    return (rise/dv);
}
