#include "rpncalc.h"
#include <math.h>

double angle_to_rad(rpn_trig_mode mode, double value)
{
    switch(mode)
    {
        case TM_RAD:
        {
            return value;
        }
        case TM_DEG:
        {
            return value * (RPN_PI/180);
        }
        case TM_GRAD:
        {
            return value * (RPN_PI/200);
        }
    }
    
    return 0;
}

double rad_to_angle(rpn_trig_mode mode, double value)
{
    switch(mode)
    {
        case TM_RAD:
        {
            return value;
        }
        case TM_DEG:
        {
            return value * (180/RPN_PI);
        }
        case TM_GRAD:
        {
            return value * (200/RPN_PI);
        }
    }
    
    return 0;
}

double rpn_sin(rpn_trig_mode mode, double value)
{
    return sin(angle_to_rad(mode, value));
}

double rpn_asin(rpn_trig_mode mode, double value)
{
    return rad_to_angle(mode, asin(value));
}

double rpn_cos(rpn_trig_mode mode, double value)
{
    return cos(angle_to_rad(mode, value));
}

double rpn_acos(rpn_trig_mode mode, double value)
{
    return rad_to_angle(mode, acos(value));
}

double rpn_tan(rpn_trig_mode mode, double value)
{
    return tan(angle_to_rad(mode, value));
}

double rpn_atan(rpn_trig_mode mode, double value)
{
    return rad_to_angle(mode, atan(value));
}


