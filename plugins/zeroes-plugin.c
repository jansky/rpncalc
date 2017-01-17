#include "../rpncalc.h"
#include <string.h>
#include <stdio.h>

extern int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link);
struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ));

struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ))
{
	return info_link("Zeroes Finder", "Ian Duncan", "Provides support for finding the zeroes of a function on a given interval.", 1.0);
}

int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link)
{
	if(strcmp(token, "zeroes") == 0)
	{
		// Get min and max of interval
		
		double min = 0;
		double max = 0;
		double step = 0.00001;
		int num_zeroes = 0;
        
        struct rpn_stack_element *e1 = link->stack_pop(stack);
        struct rpn_stack_element *e2 = link->stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 2;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get two numbers.\n");
            return 2;
        }
        
        min = e2->value.number;
        max = e1->value.number;
        
        if(min == max || max - min <= (2*step) || max < min)
        {
        	fprintf(stderr, "Error: Given interval invalid.\n");
        	return 2;
        }
        
        struct rpn_stack *func = link->create_function_stack(stack);
        
        if(func == NULL)
        {
            fprintf(stderr, "Error: Unable to evaluate expression.\n");
            return 2;
        }
        
        double i = min;
        
        for(; i <= max; i += step)
        {
        	mode->x = i;
        	
        	double value = link->eval_stack(func, stack, stat_stack, mode);
        	
        	if((int)value == 0) // We've found a zero
        	{
        		struct rpn_stack_element *e_new = link->stack_element_create_number(i);
        
				if(e_new == NULL)
				    return -1;
				
				if(link->stack_push(stack, e_new) != 0)
				    return -2;
				
				num_zeroes++;
			}
		}        
        
        if(num_zeroes == 0)
        	printf("No zeroes found on the given interval.\n");
        else
        {
        	int j = 0;
        	
        	for(; j < num_zeroes; j++)
        	{
        		struct rpn_stack_element *e = stack->contents[stack->top - j];
                
                if(e == NULL)
                    printf("Null element.\n");
                else
                {
                    if(e->e_type == ET_NUMBER)
                        printf("%f\n", e->value.number);
                    if(e->e_type == ET_STRING)
                        printf("\"%s\"\n", e->value.str);
                    if(e->e_type == ET_MARK)
                        printf("MARK\n");
                }
            }
        } 	 
        
        link->stack_free(func);
        
        mode->x = 0;
        mode->silent = 1;
		
		return 0;
	}
	
	return 1;
}
