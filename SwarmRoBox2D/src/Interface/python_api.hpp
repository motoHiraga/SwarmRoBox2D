/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef INTERFACE_PYTHON_API_HPP_
#define INTERFACE_PYTHON_API_HPP_

#include "../SwarmRoBox2D.hpp"

extern "C"
{
double evalFuncs(double individual[], int func_index, int seed);
}

#endif /* INTERFACE_PYTHON_API_HPP_ */
