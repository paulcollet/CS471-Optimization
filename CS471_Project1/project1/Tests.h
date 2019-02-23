/*
 * Project: Project1: Benchmark
 * File:    Test.h
 * Author:  Paul O. Collet
 *          cs471001_18
 *
 */


#include "std_includes.h"

#pragma once


//****** elements of sequences *******
// with x1 = x and x2 = (y or notUsed)

double schwefels(int x, int notUsed)
{
	return (-1) * x * sin(sqrt(abs(x)));
}


double deJong1(int x, int notUsed)
{
	return pow(x, 2);
}


double rosenbrock(int x, int y)
{
	return 100 * pow((pow(x, 2) - y), 2) + pow((1 - x), 2);
}


double rastrigin(int x, int notUsed)
{
	return pow(x, 2) - 10 * cos(2 * pi*x);
}


double griewaSum(int x, int notUsed)
{
	return pow(x, 2) / 4000;
}

double griewaPro(int x, int y)
{
	return cos(x / sqrt(y)); // y for i
}


double sesw(int x, int y)
{
	return 0.5 + pow(sin(pow(x, 2) + pow(y, 2) - 0.5), 2)
		/ pow(1 + 0.001*(pow(x, 2) + pow(y, 2)), 2);
}


double svsw(int x, int y)
{
	return pow(pow(x, 2) + pow(y, 2), 1 / 4)
		* pow(sin(50 * pow(pow(x, 2) + pow(y, 2), 1 / 10)), 2) + 1;
}


double ackley1(int x, int y)
{
	return 1 / pow(e, 0.2) * sqrt(pow(x, 2)
		+ pow(y, 2)) + 3 * (cos(2 * x) + sin(2 * y));
}


double ackley2(int x, int y)
{
	return 20 + e - 20 /
		(pow(e, 0.2) * sqrt((pow(x, 2) + pow(y, 2)) / 2));
}


double eggHolder(int x, int y)
{
	return (-1) * x * sin(sqrt(abs(x - y - 47)))
		- (y + 47) * sin(sqrt(abs(y + 47 + x / 2)));
}


double rana(int x, int y)
{
	return	 x * sin(sqrt(abs(y - x + 1))) * cos(sqrt(abs(y + x + 1)))
		+ (y + 1)* cos(sqrt(abs(y - x + 1))) * sin(sqrt(abs(y + x + 1)));
}


double patho(int x, int y)
{
	return 0.5 + (pow(sin(sqrt(100 * pow(x, 2) + pow(y, 2))), 2) - 5)
		/ (1 + 0.001*pow(pow(x, 2) - 2 * x *y + pow(y, 2), 2));
}


double michalewicz(int x, int y)
{
	return sin(x) * pow(sin(y*pow(x, 2) / pi), 20); // y for i
}


double mcw(int x, int y)
{
	return pow(e, (-1 / 8 * (pow(x, 2) + pow(y, 2) + 0.5*y*x)))
		* cos(4 * (sqrt(pow(x, 2) + pow(y, 2) + 0.5*x*y)));
}

//****
double shekelFH1(int i, int A)
{
	return 1 / (C[i] + A);		// A as inner sum
}

double shekelFH2(int x, int y)	// y as A[i][j]
{
	return pow(x - y, 2);
}
//****
