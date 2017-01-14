#include "rpncalc.h"
#include <string.h>
#include <stdio.h>

extern int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link);
struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ));

struct rpn_plugin_info *rpn_plugin_info(struct rpn_plugin_info *(*info_link)(char *, char *, char *, double ))
{
	return info_link("Extended Mean Support", "Ian Duncan", "Provides support for harmonic and geometric means.", 1.0);
}

int rpn_plugin_main(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, struct rpn_plugin_functions *link)
{
	if(strcmp(token, "hmean") == 0)
	{
		if(link->stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
        	double sumrecip = 0;
        	
        	int count = stat_stack->top;
    
			for(; count >= 0; count--)
			{
				struct rpn_stack_element *e = stat_stack->contents[count];
				
				if(e == NULL)
				    return -1;
				
				sumrecip += 1/(e->value.number);
			}
			
			double hmean = stat_stack->top + 1;
			
			hmean = hmean / sumrecip;
			
			struct rpn_stack_element *e_new = link->stack_element_create_number(hmean);
            
            if(e_new == NULL)
                return -1;
            if(link->stack_push(stack, e_new) != 0)
                return -2;
            
        }
        
        return 0;
    }
    
    return 1;
}
