#include "rpncalc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct rpn_stack_element *rpn_stack_element_create_number(double number)
{
    struct rpn_stack_element *ne = malloc(sizeof(struct rpn_stack_element));
    
    if(ne == NULL)
        return NULL;
        
   ne->e_type = ET_NUMBER;
   
   ne->value.number = number;
   
   return ne;
}

struct rpn_stack_element *rpn_stack_element_create_string(char *str)
{
    if(str == NULL)
        return NULL;
    
    struct rpn_stack_element *ne = malloc(sizeof(struct rpn_stack_element));
    
    if(ne == NULL)
        return NULL;
        
   ne->e_type = ET_STRING;
   
   /* Make a copy of the string */
   ne->value.str = malloc(strlen(str) + 1);
   
   if(ne->value.str == NULL)
        return NULL;
   
   strcpy(ne->value.str, str);
   
   return ne;
}

struct rpn_stack_element *rpn_stack_element_create_mark(void)
{
    struct rpn_stack_element *ne = malloc(sizeof(struct rpn_stack_element));
    
    if(ne == NULL)
        return NULL;
        
   ne->e_type = ET_MARK;
     
   return ne;
}

struct rpn_stack *rpn_stack_init(size_t max_size)
{
    struct rpn_stack *ns = malloc(sizeof(struct rpn_stack));
    
    if(ns == NULL)
        return NULL;
        
    ns->contents = malloc(sizeof(struct rpn_stack_element *) * max_size);
    
    if(ns->contents == NULL)
        return NULL;
    
    ns->max_size = max_size;
    
    ns->top = -1;
    
    return ns;
}

int rpn_stack_destroy(struct rpn_stack *stack)
{
    if(stack == NULL)
        return -1;
    
    free(stack->contents);
    
    free(stack);
    
    return 0;
}

int rpn_stack_is_empty(struct rpn_stack *stack)
{
    if(stack == NULL)
        return -1;
    
    return stack->top < 0;
}

int rpn_stack_is_full(struct rpn_stack *stack)
{
    if(stack == NULL)
        return -1;
    
    return stack->top >= (stack->max_size - 1);
}

int rpn_stack_push(struct rpn_stack *stack, struct rpn_stack_element *element)
{
    if(stack == NULL || element == NULL)
        return -1;
    
    if(rpn_stack_is_full(stack))
        return 1;
    
    stack->contents[++stack->top] = element;
    
    return 0;
}

struct rpn_stack_element *rpn_stack_pop(struct rpn_stack *stack)
{
    if(stack == NULL)
        return NULL;
    
    if(rpn_stack_is_empty(stack))
        return NULL;
    
    return stack->contents[stack->top--];
}

struct rpn_stack_element *rpn_stack_peek(struct rpn_stack *stack)
{
    if(stack == NULL)
        return NULL;
    
    if(rpn_stack_is_empty(stack))
        return NULL;
    
    return stack->contents[stack->top];
}



