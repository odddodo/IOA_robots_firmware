#ifndef fuzzyLogic_h
#define fuzzyLogic_h
#include <math.h>

double fuzzyGrade(double val, double x0, double x1)
{
    double result = 0;
    double x = val;
    if (x <= x0)
    {
        result = 0;
    }
    else if (x > x1)
    {
        result = 1;
    }
    else
    {
        result = (x / (x1 - x0)) - (x0 / (x1 - x0));
    }
    return result;
}

double fuzzyRevGrade(double val, double x0, double x1)
{
    double result = 0;
    double x = val;
    if (x <= 0)
    {
        result = 1;
    }
    else if (x >= x1)
    {
        result = 0;
    }
    else
    {
        result = (-x / (x1 - x0)) + (x1 / (x1 - x0));
    }
    return result;
}

double fuzzyTriangle(double val, double x0, double x1, double x2)
{
    double result = 0;
    double x = val;
    if (x <= x0)
    {
        result = 0;
    }
    else if (x == x1)
    {
        result = 1;
    }
    else if ((x > x0) && (x < x1))
    {
        result = (x / (x1 - x0)) - (x0 / (x1 - x0));
    }
    else
    {
        result = (x / (x2 - x1)) + (x2 / (x2 - x1));
    }
}

double fuzzyAND(double a, double b)
{
    return fmin(a, b);
}
double fuzzyOR(double a, double b)
{
    return fmax(a, b);
}
double fuzzyNOT(double a)
{
    return 1.0 - a;
}

#endif