#include "rpncalc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct rpn_stack *stack;
    struct rpn_stack *stat_stack;
    struct rpn_mode *mode;
    struct rpn_plugin *plugin_root = NULL;
    struct rpn_plugin_functions *functions = NULL;
    char *buffer;
    
    int num_plugins = 0;
    
    stack = rpn_stack_init(RPN_STACK_MAXSIZE);
    
    
    if(stack == NULL)
    {
        fprintf(stderr, "Error: Unable to initialize stack.\n");
        return 1;
    }
    
    stat_stack = rpn_stack_init(RPN_STACK_MAXSIZE);
    
    if(stat_stack == NULL)
    {
        fprintf(stderr, "Error: Unable to initialize stat stack.\n");
        return 1;
    }
    
    
    mode = rpn_mode_create(TM_RAD);
    
    if(mode == NULL)
    {
        fprintf(stderr, "Error: Unable to initialize calculator settings.\n");
        return 1;
    }
    
    printf("rpnCalc\n\n");
    
    /* Load Plugins */
    
    if(argc > 1)
    {
    	int i = 1;
    	
    	for(; i < argc; i++)
    	{
    		struct rpn_plugin *np;
    		
    		np = plugin_init(argv[i]);
    		
    		if(np != NULL)
    		{
    			// If we successfully initialized the plugin, add it to the list
    			if(plugin_root == NULL)
    				plugin_root = np;
    			else
    			{
    				struct rpn_plugin *next = plugin_root;
    				
    				while(1)
    				{
    					if(next->next == NULL)
    					{
    						next->next = np;
    						break;
    					}
    					else
    					{
    						next = next->next;
    					}
    				}
    			}
    			
    			num_plugins++;
    		}
    	}
    }
    
    if(num_plugins > 0)
    {
    	// If we have plugins, then we need to generate the function interface
    	
    	functions = malloc(sizeof(struct rpn_plugin_functions));
    	
    	if(functions == NULL)
    	{
    		fprintf(stderr, "Error: Could not create plugin interface.\n");
    		return 1;
    	}
    	
    	functions->stack_element_create_number = &rpn_stack_element_create_number;
		functions->stack_element_create_string = &rpn_stack_element_create_string;
		functions->stack_element_create_mark = &rpn_stack_element_create_mark;
		functions->stack_push = &rpn_stack_push;
		functions->stack_pop = &rpn_stack_pop;
		functions->stack_peek = &rpn_stack_peek;
		functions->stack_is_full = &rpn_stack_is_full;
		functions->stack_is_empty = &rpn_stack_is_empty;
	}
    
    printf("Initialized stack with %d maximum entries.\n", stack->max_size);
    printf("Initialized stat stack with %d maximum entries.\n", stat_stack->max_size);
    printf("Loaded %d plugins.\n\n", num_plugins);
    
    while(1)
    {
        buffer = malloc(501);
        
        if(buffer == NULL)
        {
            fprintf(stderr, "Error: Unable to allocate buffer.\n");
            return 1;
        }
        
        
        
        printf("> ");
        
        fgets(buffer, 500, stdin);
        
        buffer = strtok(buffer, "\n");
        
        char *first_token = strtok(buffer, " ");
        
        if(first_token == NULL)
            ;
        else
        {
            switch(rpn_evaluate_token(first_token, stack, stat_stack, mode, plugin_root, functions))
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    break;
                }
                case -1:
                {
                    fprintf(stderr, "Error: Memory allocation error.\n");
                    return 1;
                }
                case -2:
                {
                    fprintf(stderr, "Error: Stack error.\n");
                    return 1;
                }
                case -3:
                    return 1;
                default:
                {
                    fprintf(stderr, "Error: error.\n");
                    return 1;
                }
            }
            
            char *current_token = strtok(NULL, " ");
            
            while(current_token != NULL)
            {
                switch(rpn_evaluate_token(current_token, stack, stat_stack, mode, plugin_root, functions))
                {
                    case 0:
                    {
                        break;
                    }
                    case 1:
                    {
                        break;
                    }
                    case -1:
                    {
                        fprintf(stderr, "Error: Memory allocation error.\n");
                        return 1;
                    }
                    case -2:
                    {
                        fprintf(stderr, "Error: Stack error.\n");
                        return 1;
                    }
                    case -3:
                        return 1;
                    default:
                    {
                        fprintf(stderr, "Error: error.\n");
                        return 1;
                    }
                }
                
                current_token = strtok(NULL, " ");
            }
            
        }
        
        if(mode->silent == 0)
        {
            struct rpn_stack_element *e_to_print = rpn_stack_peek(stack);
            
            if(e_to_print != NULL)
            {
                switch(e_to_print->e_type)
                {
                    case ET_NUMBER:
                    {
                        printf("%f\n", e_to_print->value.number);
                        break;
                    }
                    case ET_STRING:
                    {
                        printf("\"%s\"\n", e_to_print->value.str);
                        break;
                    }
                    case ET_MARK:
                    {
                        printf("MARK\n");
                        break;
                    }
                }
            }
            
            
        }
        
        mode->silent = 0;
        
        free(buffer);
    }
    
    return 0;
}
        
        
    
    
