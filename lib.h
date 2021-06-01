#ifndef BD2_P1_LIB_H
#define BD2_P1_LIB_H
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cstring>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#endif //BD2_P1_LIB_H

float roundf(float var)
{
    char str[40]; 

    sprintf(str, "%.2f", var);
  
    sscanf(str, "%f", &var); 
  
    return var; 
}