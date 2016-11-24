#include "rpncalc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct rpn_mode *rpn_mode_create(rpn_trig_mode trig_mode)
{
    struct rpn_mode *nm = malloc(sizeof(struct rpn_mode));
    
    if(nm == NULL)
        return NULL;
    
    nm->trig_mode = trig_mode;
    nm->mark_on = 0;
    nm->x = 0;
    
    nm->silent = 0;
    
    /* Create variable array */
    
    nm->variables = calloc(52, sizeof(double)); // 52 upper and lowercase letters
    
    if(nm->variables == NULL)
        return NULL;    
    
    return nm;
}

int rpn_evaluate_token(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode)
{

    if(token == NULL || stack == NULL)
        return -1;
    
    /* Instructions */
    
    if(strcmp(token, "quit") == 0 || strcmp(token, "exit") == 0)
    	exit(0);
    
    if(strcmp(token, "\'") == 0) // Turn the mark on or off
    {
        if(mode->mark_on == 1)
        {
            // Let's return to normal
            struct rpn_stack_element *e_new = rpn_stack_element_create_mark();
            
            if(e_new == NULL)
                return -1;
            
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
            
            mode->mark_on = 0;
        }
        else
        {
            // Let's turn the mark on
            struct rpn_stack_element *e_new = rpn_stack_element_create_mark();
            
            if(e_new == NULL)
                return -1;
            
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
            
            mode->mark_on = 1;
        }
        
        return 0;
    }
    
    if(mode->mark_on == 1) // If the mark is on, simply push expression to the stack as a string
    {
        struct rpn_stack_element *e_new = rpn_stack_element_create_string(token);
        
        if(e_new == NULL)
            return -1;
            
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    // If the expression begins with ', then push the single token to the string without markers
    
    if(token[0] == '\'')
    {
        struct rpn_stack_element *e_new = rpn_stack_element_create_string((char*)(token + 1));
        
        if(e_new == NULL)
            return -1;
            
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
        
    
    if(strcmp(token, "+") == 0) // Addition
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(num1+num2);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "-") == 0) // Subtraction
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(num2-num1);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "*") == 0) // Multiplication
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(num1*num2);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "/") == 0) // Division
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(num2/num1);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "^") == 0) // Exponent
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(pow(num2, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "rt") == 0) // nth root
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(pow(num2, 1/num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "sq") == 0) // square root
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(sqrt(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "!") == 0) // factorial
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_factorial(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "ncr") == 0) // choose
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_choose(num2, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "npr") == 0) // permutation
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_permute(num2, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "abs") == 0) // absolute value
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(fabs(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "inv") == 0) // 1/x
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(1/num1);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "tmode") == 0) // trig mode
    {
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_STRING)
        {
            fprintf(stderr, "Error: Expected, but did not get, one string.\n");
            return 1;
        }
        
       
        if(strcmp(e1->value.str, "rad") == 0)
            mode->trig_mode = TM_RAD;
        else if(strcmp(e1->value.str, "deg") == 0)
            mode->trig_mode = TM_DEG;
        else if(strcmp(e1->value.str, "grad") == 0)
            mode->trig_mode = TM_GRAD;
        else
        {
            fprintf(stderr, "Error: Invalid trignonometry mode specified (valid ones are rad, deg, and grad).\n");
            return 1;
        }
        
        mode->silent = 1;
       
        
        return 0;
    }
    
    if(strcmp(token, "sin") == 0) // sine
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_sin(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "asin") == 0) // arcsine
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_asin(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "cos") == 0) // cosine
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_cos(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "acos") == 0) // arccosine
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_acos(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "tan") == 0) // tangent
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_tan(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "atan") == 0) // arctangent
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_atan(mode->trig_mode, num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "pi") == 0) // pi
    {
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(RPN_PI);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "e") == 0) // e
    {
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(RPN_E);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "inspect") == 0) // inspect (list stack contents)
    {
        if(rpn_stack_is_empty(stack))
            printf("Stack is empty.\n");
        else
        {
            int usernum = 1;
            int count = stack->top;
            
            for(; count >= 0; count--)
            {
                struct rpn_stack_element *e = stack->contents[count];
                
                if(e == NULL)
                    printf("%d: Null element.\n", usernum);
                else
                {
                    if(e->e_type == ET_NUMBER)
                        printf("%d: %f\n", usernum, e->value.number);
                    if(e->e_type == ET_STRING)
                        printf("%d: \"%s\"\n", usernum, e->value.str);
                    if(e->e_type == ET_MARK)
                        printf("%d: MARK\n", usernum);
                }
                
                usernum++;
            }
        }
        
        mode->silent = 1;
        
        return 0;
    }
    
    if(strcmp(token, "log") == 0) // base 10 logarithm
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(log10(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "ln") == 0) // natural logarithm
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(log(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "log2") == 0) // base 2 logarithm
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(log2(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "logb") == 0) // logarithm with custom base
    {
        double num1;
        double num2;
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, two numbers.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        num2 = e2->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(log(num2)/log(num1));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "clear") == 0) // clear the stack
    {
        while(!rpn_stack_is_empty(stack))
            rpn_stack_pop(stack);
        
        printf("Stack cleared.\n");
        
        return 0;
    }
    
    if(strcmp(token, "pop") == 0) // pop 1 item off stack
    {
        if(!rpn_stack_is_empty(stack))
            rpn_stack_pop(stack);
        else
        {
            fprintf(stderr, "Error: Stack is empty.\n");
            return 1;
        }
        
        return 0;
    }
    
    if(strcmp(token, "spush") == 0) // push value to stat stack
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(num1);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stat_stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strcmp(token, "spushm") == 0) // push multiple values to stat stack
    {
        double num1;
        
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one number.\n");
            return 1;
        }
        
        num1 = e1->value.number;
        
        int count = (int)round(num1);
        
        int i = 0;
        
        for(; i < count; i++)
        {
            struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        
            if(e2 == NULL)
            {
                fprintf(stderr, "Error: Expected more stack elements.\n");
                return 1;
            }
            
            if(e2->e_type != ET_NUMBER)
            {
                fprintf(stderr, "Error: Expected, but did not get, one number.\n");
                return 1;
            }
            
            struct rpn_stack_element *e2_new = rpn_stack_element_create_number(e2->value.number);
        
            if(e2_new == NULL)
                return -1;
            
            if(rpn_stack_push(stat_stack, e2_new) != 0)
                return -2;
        }
               
        return 0;
    }
    
    if(strcmp(token, "sclear") == 0) // clear the stat stack
    {
        while(!rpn_stack_is_empty(stat_stack))
            rpn_stack_pop(stat_stack);
        
        printf("Stat stack cleared.\n");
        
        mode->silent = 1;
        
        return 0;
    }
    
    if(strcmp(token, "spop") == 0) // pop 1 item off stat stack
    {
        if(!rpn_stack_is_empty(stat_stack))
            rpn_stack_pop(stat_stack);
        else
        {
            fprintf(stderr, "Error: Stat stack is empty.\n");
            return 1;
        }
        
        return 0;
    }
    
    if(strcmp(token, "sinspect") == 0) // sinspect (list stat stack contents)
    {
        if(rpn_stack_is_empty(stat_stack))
            printf("Stat stack is empty.\n");
        else
        {
            int usernum = 1;
            int count = stat_stack->top;
            
            for(; count >= 0; count--)
            {
                struct rpn_stack_element *e = stat_stack->contents[count];
                
                if(e == NULL)
                    printf("%d: Null element.\n", usernum);
                else
                {
                    if(e->e_type == ET_NUMBER)
                        printf("%d: %f\n", usernum, e->value.number);
                    if(e->e_type == ET_STRING)
                        printf("%d: \"%s\"\n", usernum, e->value.str);
                    if(e->e_type == ET_MARK)
                        printf("%d: MARK\n", usernum);
                }
                
                usernum++;
            }
        }
        
        mode->silent = 1;
        
        return 0;
    }
    
    if(strcmp(token, "mean") == 0) // arithmetic mean on numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_mean(stat_stack);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "sum") == 0) // sum of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_sum(stat_stack);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "sumsq") == 0) // sum of numbers^2 in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_sum_squared(stat_stack);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "prod") == 0) // product of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_product(stat_stack);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "vrnce") == 0) // population variance of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_variance(stat_stack, 0);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "svrnce") == 0) // sample variance of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_variance(stat_stack, 1);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "stddev") == 0) // population standard deviation of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_variance(stat_stack, 0);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(sqrt(result));
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "sstddev") == 0) // sample standard deviation of numbers in stat stack
    {
        if(rpn_stack_is_empty(stat_stack))
            fprintf(stderr, "Error: Stat stack is empty.\n");
        else
        {
            double result = rpn_variance(stat_stack, 1);
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(sqrt(result));
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        }
        
        
        
        return 0;
    }
    
    if(strcmp(token, "sn") == 0) // number of numbers in stat stack
    {
        
            double result = stat_stack->top + 1;
            
            struct rpn_stack_element *e_new = rpn_stack_element_create_number(result);
            
            if(e_new == NULL)
                return -1;
            if(rpn_stack_push(stack, e_new) != 0)
                return -2;
        
        
        
        
        return 0;
    }
    
    if(strcmp(token, ":") == 0) // print number at top of stack
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
            
        return 0;
    }
    
    if(strcmp(token, ";") == 0) // print number at top of stack, then pop it
    {

            struct rpn_stack_element *e_to_print = rpn_stack_pop(stack);
            
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
            
        return 0;
    }
    
    if(strcmp(token, "asn") == 0) // Assign value to variable
    {
        // Get variable name and value
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        struct rpn_stack_element *e2 = rpn_stack_pop(stack);
        
        if(e1 == NULL || e2 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_STRING || e2->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get, one string and one number.\n");
            return 1;
        }
        
        char vn = e1->value.str[0];
        
        if(((int)vn >= 65 && (int)vn <= 90) || ((int)vn >= 97 && (int)vn <= 122)) // Verify that we have a valid variable name
        {
            if(rpn_set_variable(vn, e2->value.number, mode->variables) != 0)
            {
                fprintf(stderr, "Error: Unable to set variable.\n");
                return -3;
            }
        }
        else
        {
            fprintf(stderr, "Error: Expected, but did not get a single upper or lowercase letter as a variable name.\n");
            return 1;
        }
        
        return 0;
    }
    
    if(strcmp(token, "eval") == 0) // Evaluate function for x
    {
        // Get value for x
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get one number.\n");
            return 1;
        }
        
        struct rpn_stack *func = rpn_create_function_stack(stack);
        
        if(func == NULL)
        {
            fprintf(stderr, "Error: Unable to evaluate expression.\n");
            return 1;
        }
        
        mode->x = e1->value.number;
        
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_eval_stack(func, stack, stat_stack, mode));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        rpn_stack_free(func);
        
        mode->x = 0;
       
        return 0;
    }
    
    if(strcmp(token, "nderv") == 0) // Numerical derivative
    {
        // Get value for x
        
        struct rpn_stack_element *e1 = rpn_stack_pop(stack);
        
        if(e1 == NULL)
        {
            fprintf(stderr, "Error: Expected more stack elements.\n");
            return 1;
        }
        
        if(e1->e_type != ET_NUMBER)
        {
            fprintf(stderr, "Error: Expected, but did not get one number.\n");
            return 1;
        }
        
        struct rpn_stack *func = rpn_create_function_stack(stack);
        
        if(func == NULL)
        {
            fprintf(stderr, "Error: Unable to evaluate expression.\n");
            return 1;
        }      
   
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_nderiv(func, stack, stat_stack, mode, e1->value.number, 0.001));
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        rpn_stack_free(func);
        
        mode->x = 0;
       
        return 0;
    } 
    
    /* Numbers */
    
    double new_number;
    
    if(sscanf(token, "%lf", &new_number) == 1)
    {
        // Token is a number
        
       struct rpn_stack_element *e_new = rpn_stack_element_create_number(new_number);
       
       if(e_new == NULL)
            return -1;
        
       if(rpn_stack_push(stack, e_new) != 0)
            return -2;
       
       return 0;
    }
    
    /* Variables */
    
    if(strcmp(token, "x") == 0)
    {
        struct rpn_stack_element *e_new = rpn_stack_element_create_number(mode->x);
        
        if(e_new == NULL)
            return -1;
        
        if(rpn_stack_push(stack, e_new) != 0)
            return -2;
        
        return 0;
    }
    
    if(strlen(token) == 1)
    {
        if(((int)token[0] >= 65 && (int)token[0] <= 90) || ((int)token[0] >= 97 && (int)token[0] <= 122)) // Verify that we have a valid variable name
        {
           struct rpn_stack_element *e_new = rpn_stack_element_create_number(rpn_get_variable(token[0], mode->variables));
       
           if(e_new == NULL)
                return -1;
            
           if(rpn_stack_push(stack, e_new) != 0)
                return -2;
           
           return 0;
         }
    }
    
    /* Strings (i.e. anything else) */
    
    struct rpn_stack_element *e_new = rpn_stack_element_create_string(token);
    
    if(e_new == NULL)
        return -1;
        
    if(rpn_stack_push(stack, e_new) != 0)
        return -2;
       
    return 0;
}
       
        
    
    
    
    
        
