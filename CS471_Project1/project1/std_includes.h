/*
 * Project: Project1:Benchmark
 * File:    std_includes.h
 * Author:  Paul O. Collet
 *          cs471001_18

 */

#pragma once

#include <random>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>    // sort
#include <vector>
#include <chrono>
#include "Shekel's_Foxholes_Data.h"

using namespace std;
using namespace std::chrono;

// minimum staticical requirement is 30 but 
// the user may need to increase this on a fast machine
const int MINSTAT = 30;
const float pi = 3.14159265359;
const float e = 2.71828182846;

