#include "rpncalc.h"
#include <math.h>

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
