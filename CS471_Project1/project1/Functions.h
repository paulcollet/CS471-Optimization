/*
 * Project: Project1: Benchmark
 * File:    Functions.h
 * Author:  Paul O. Collet
 *          cs471001_18
 *
 */


#include "std_includes.h"

#pragma once

// generate random doubles
vector<double> genRand(double a, double b, int num)
{
	random_device rd;
	mt19937 gen(rd());

	//reason why I didn't use type T
	uniform_real_distribution<double> dis(a, b);

	vector <double> temp;

	for (int i = 0; i < num; i++)
		temp.push_back(dis(gen));

	return temp;
}

// standard deviation
template<class T>
double staDev(vector<T> list, double sum, int range)
{
	double sd = 0.0;

	for (int i = 0; i < range; i++)
		sd += pow(list[i] - (sum / range), 2);

	return sqrt(sd / range);
}

// get median 
template <class T>
T median(vector<T> list)
{
	int half = list.size() / 2;

	if (list.size() % 2 == 0)
	{
		return (list[half] + list[half + 1]) / 2;
	}
	else
	{
		return list[half + 1];
	}
}