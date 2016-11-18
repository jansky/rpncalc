#pragma once
#include <stddef.h>
/* Stack Functions */

#define RPN_STACK_MAXSIZE 1000
#define RPN_PI 3.14159265359
#define RPN_E 2.7182818284

typedef enum { ET_NUMBER, ET_STRING, ET_MARK } rpn_element_type;

struct rpn_stack_element
{
    union
    {
        double number;
        char *str;
    } value;
    
    rpn_element_type e_type;
};

struct rpn_stack
{
    struct rpn_stack_element **contents;
    
    int top;
    
    int max_size;
};

struct rpn_stack_element *rpn_stack_element_create_number(double number);

struct rpn_stack_element *rpn_stack_element_create_string(char *str);

struct rpn_stack_element *rpn_stack_element_create_mark(void);

struct rpn_stack *rpn_stack_init(size_t max_size);

int rpn_stack_destroy(struct rpn_stack *stack);

int rpn_stack_push(struct rpn_stack *stack, struct rpn_stack_element *element);

int rpn_stack_is_empty(struct rpn_stack *stack);

int rpn_stack_is_full(struct rpn_stack *stack);

struct rpn_stack_element *rpn_stack_pop(struct rpn_stack *stack);

struct rpn_stack_element *rpn_stack_peek(struct rpn_stack *stack);

/* Trig Functions */

typedef enum { TM_RAD, TM_DEG, TM_GRAD } rpn_trig_mode;

double angle_to_rad(rpn_trig_mode mode, double value);
double rad_to_angle(rpn_trig_mode mode, double value);

double rpn_sin(rpn_trig_mode mode, double value);
double rpn_asin(rpn_trig_mode mode, double value);

double rpn_cos(rpn_trig_mode mode, double value);
double rpn_acos(rpn_trig_mode mode, double value);

double rpn_tan(rpn_trig_mode mode, double value);
double rpn_atan(rpn_trig_mode mode, double value);

/* Math Functions */

double rpn_factorial(double number);

double rpn_choose(double n, double r);

double rpn_permute(double n, double r);

/* Calculator Functions */

struct rpn_mode
{
	rpn_trig_mode trig_mode;
	
	int mark_on;
	
	int silent;
	
	double *variables;
	
	double x;
};

struct rpn_mode *rpn_mode_create(rpn_trig_mode trig_mode);

int rpn_evaluate_token(char *token, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode);

double eval_for_x(struct rpn_stack *func, struct rpn_stack *stat_stack, struct rpn_mode *mode, double x);

/* Variable Functions */

double rpn_get_variable(char name, double *variables);

int rpn_set_variable(char name, double value, double *variables);

/* Stat Functions */

double rpn_mean(struct rpn_stack *stat_stack);

double rpn_variance(struct rpn_stack *stat_stack, int sample);

double rpn_sum(struct rpn_stack *stat_stack);

double rpn_sum_squared(struct rpn_stack *stat_stack);

double rpn_product(struct rpn_stack *stat_stack);

/* Calculus Functions */

//double rpn_nderiv(struct rpn_stack *func, struct rpn_stack *stack, struct rpn_stack *stat_stack, struct rpn_mode *mode, double x, double dv);



