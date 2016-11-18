#include "rpncalc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    struct rpn_stack *stack;
    struct rpn_stack *stat_stack;
    struct rpn_mode *mode;
    char *buffer;
    
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
    
    printf("Initialized stack with %d maximum entries.\n", stack->max_size);
    printf("Initialized stat stack with %d maximum entries.\n\n", stat_stack->max_size);
    
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
            switch(rpn_evaluate_token(first_token, stack, stat_stack, mode))
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
                switch(rpn_evaluate_token(current_token, stack, stat_stack, mode))
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
        
        
    
    
