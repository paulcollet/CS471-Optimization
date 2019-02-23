
/* 
 * Project: Project1
 * File:    Benchmark.cpp
 * Author:  Paul O. Collet
 *          cs471001_18
 *
 * Created on March 28, 2018, 11:45 AM
 * Edited / cleaned up on 2/22/2019
 * 
 * requires C++ 11 compiler.
 */

#include "std_includes.h"
#include "Functions.h"
#include "Tests.h"


//primary action and printing function. Normally, I would make a class for this, but since I used those default parameters....
void printFun(ofstream& file, int dim, double min, double max, double (*fun)(int,int), 
			   int nMod = 0, int preS = 0, int preP = 1) // optional parameters
{  
	time_point<high_resolution_clock> start, end;
    double sum		= 0.0;
	double totalSum = 0.0; 

	vector <double> psdoRand, totalRand;

	//each row represents a dimension of a function		
	if (dim > 10)	file << ",";// skip cell

	file << dim << ",";	//dimension (col 2)

	start = high_resolution_clock::now();
		
	for (int k = 0; k < MINSTAT; k++)
	{	
		psdoRand = genRand(min, max, dim); 

		if (nMod == 0) //sequences with just x
		{
			for (int i = 1; i <= psdoRand.size(); i++)
			{
				sum += fun(psdoRand[i-1], 0); //call element of sequence				
			}
		}
		else if (nMod == -1) // sequences with x and x+1
		{
			for (int i = 1; i < psdoRand.size(); i++)
			{
				sum += fun(psdoRand[i-1], psdoRand[i]); 				
			}
		}
		else if (nMod == 6) // Michalewicz code
		{
			for (int i = 1; i <= psdoRand.size(); i++)
			{
				sum += fun(psdoRand[i-1], i); 				
			}
		}	
		else if (nMod == -9) // Griewangk code
		{
			double product = 1.0;

			for (int i = 1; i <= psdoRand.size(); i++)
			{
				sum		+=		 fun(psdoRand[i-1], 0); //call griewaSum
				product *= griewaPro(psdoRand[i-1], i);
			}
			sum -= product;
		}	
		else // Shekel's Foxholes
		{
			double sum2 = 0.0;

			for (int i = 1; i <= nMod; i++)
			{
				for (int j = 1; j <= dim; j++)
				{
					sum2 += shekelFH2(psdoRand[j-1], A[i][j]); 				
				}								
			}

			for (int i = 1; i <= nMod; i++)
			{
					sum += fun(i, sum2); //call shekelFH1
			}

		}

		sum = preS + preP * sum; // for anything done to the sum

		file << sum << ","; // if with a dimension in list
		totalSum += sum;
		sum = 0.0;

		//add current random numbers to total numbers generated
		totalRand.insert(totalRand.end(), psdoRand.begin(), psdoRand.end());
	}

	end = high_resolution_clock::now();

	//A second is 1:1 period
	duration<double> elapsed_seconds = end - start;	

	// for median and range
	std::sort(totalRand.begin(), totalRand.end()); 

	//last 5 columns	
	file << totalSum/MINSTAT << ","; //average
	file << staDev(totalRand,totalSum,totalRand.size()) << ","; //standard deviation
	file << totalRand[totalRand.size()-1] - totalRand[0] <<",";	//range
	file << median(totalRand) << ","; //median
	file << elapsed_seconds.count() << "s\n";	//time

}

int main(int argc, char** argv) 
{
	ofstream file("database.csv"); 
	int d1 = 10, d2 = 20, d3 = 30; //dimensions

    //column headers
    file << "Function," << "dimension,";

	//30 tries
	for(int i = 1; i <= MINSTAT; i++)
		file << "try " << i << ",";

	file << "average," << "staDev," << "range," << "median," << "time\n";

	//printFun(file, dimension, min, max, &sequenceElement,		//must have
	//			nModify = 0, (add to sum) = 0, (multiply to sum) = 1)	//optional

	file << "Schwefels,";
	printFun(file, d1, -512, 512, &schwefels);
	printFun(file, d2, -512, 512, &schwefels);
	printFun(file, d3, -512, 512, &schwefels);

	file << "1st DeJong,";
	printFun(file, d1, -100, 100, &deJong1);
	printFun(file, d2, -100, 100, &deJong1);
	printFun(file, d3, -100, 100, &deJong1);
	
	file << "Rosenbrock,";
	printFun(file, d1, -100, 100, &rosenbrock, -1);
	printFun(file, d2, -100, 100, &rosenbrock, -1);
	printFun(file, d3, -100, 100, &rosenbrock, -1);
   
	file << "Rastrigin,";
    printFun(file, d1,  -30,  30, &rastrigin,	0, 0,  2*d1);
	printFun(file, d2,  -30,  30, &rastrigin,	0, 0,  2*d2);
	printFun(file, d3,  -30,  30, &rastrigin,	0, 0,  2*d3);
	
	file << "Griewangk,"; // unique key:-9
	printFun(file, d1, -500, 500, &griewaSum,  -9, 1);
	printFun(file, d2, -500, 500, &griewaSum,  -9, 1);
	printFun(file, d3, -500, 500, &griewaSum,  -9, 1);

	file << "SESW,";
	printFun(file, d1,	-30,  30, &sesw,	   -1, 0, -1);
	printFun(file, d2,	-30,  30, &sesw,	   -1, 0, -1);
	printFun(file, d3,	-30,  30, &sesw,	   -1, 0, -1);
    
	file << "SVSW,";
	printFun(file, d1,	-30,  30, &svsw,	   -1);
	printFun(file, d2,	-30,  30, &svsw,	   -1);
	printFun(file, d3,	-30,  30, &svsw,	   -1);

	file << "Ackley's 1,";
	printFun(file, d1,	-32,  32, &ackley1,	   -1);
	printFun(file, d2,	-32,  32, &ackley1,	   -1);
	printFun(file, d3,	-32,  32, &ackley1,	   -1);

	file << "Ackley's 2,";
	printFun(file, d1,	-32,  32, &ackley2,	   -1);
	printFun(file, d2,	-32,  32, &ackley2,	   -1);
	printFun(file, d3,	-32,  32, &ackley2,	   -1);

	file << "Egg Holder,";
	printFun(file, d1, -500, 500, &eggHolder,  -1);
	printFun(file, d2, -500, 500, &eggHolder,  -1);
	printFun(file, d3, -500, 500, &eggHolder,  -1);

	file << "Rana,";
	printFun(file, d1, -500, 500, &rana,	   -1);
	printFun(file, d2, -500, 500, &rana,	   -1);
	printFun(file, d3, -500, 500, &rana,	   -1);

	file << "Pathological,";
	printFun(file, d1, -100, 100, &patho,	   -1);
	printFun(file, d2, -100, 100, &patho,	   -1);
	printFun(file, d3, -100, 100, &patho,	   -1);

	file << "Michalewicz,"; // unique key: 6
	printFun(file, d1,	  0,  pi, &michalewicz, 6, 0, -1);
	printFun(file, d2,	  0,  pi, &michalewicz, 6, 0, -1);
	printFun(file, d3,	  0,  pi, &michalewicz, 6, 0, -1);


	file << "MCW,"; // unique key: 3
	printFun(file, d1,	-30,  30, &mcw,		   -1, 0, -1);
	printFun(file, d2,	-30,  30, &mcw,		   -1, 0, -1);
	printFun(file, d3,	-30,  30, &mcw,		   -1, 0, -1);

	
	file << "Shekel's FH,"; // n becomes m == 30
	printFun(file, d1,	  0,  10, &shekelFH1,   30, 0, -1);

 
    file.close();
    return 0;
}

