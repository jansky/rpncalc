#include "rpncalc.h"

double rpn_get_variable(char name, double *variables)
{
    if(variables == NULL)
        return 0;
    
    
    if((int)name >= 65 && (int)name <= 90) // name is a lowercase letter
        return variables[(int)name - 65];
    else if((int)name >= 97 && (int)name <= 122) // name is an uppercase letter
        return variables[(int)name - 71];
    else
        return 0;
}

int rpn_set_variable(char name, double value, double *variables)
{
    if(variables == NULL)
        return -2;
    
    if((int)name >= 65 && (int)name <= 90) // name is a lowercase letter
    {
        variables[(int)name - 65] = value;
        return 0;
    }
    else if((int)name >= 97 && (int)name <= 122) // name is an uppercase letter
    {
        variables[(int)name - 71] = value;
        return 0;
    }
    else
        return -1;
}
