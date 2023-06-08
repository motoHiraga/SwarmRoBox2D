/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "python_api.hpp"

double example_func(double ind[]);
double simulation_test(double ind[], int seed);

double evalFuncs(double individual[], int func_index, int seed)
{
	double fitness = 0.0;
	switch (func_index)
	{
	case 0:
		fitness = simulation_test(individual, seed);
		break;
	case 99:
		fitness = example_func(individual);
		break;
	default:
		break;
	}
	return fitness;
}

double simulation_test(double ind[], int seed)
{
	static const int32 InNodeCount = 17;
	static const int32 HidNodeCount = 8;
	static const int32 OutNodeCount = 2;
	static const int32 genotypeLength = InNodeCount * HidNodeCount
			+ HidNodeCount * HidNodeCount + HidNodeCount * OutNodeCount
			+ InNodeCount * OutNodeCount;

	srbNetworkParams *params = new srbNetworkParams(InNodeCount, HidNodeCount,
			OutNodeCount);

	for (int32 i = 0; i < genotypeLength; i++)
		params->weights[i] = (float) ind[i];

	srbSettings settings;
	settings.maxStepCount = 3000;
	srbEvaluationTest evaluation;
	srbSimulation *simulation = new srbSimulationTest(&settings, params,
			(int32) seed);
	double fitness = *((float*) (simulation->Run(&evaluation)));

	delete params;
	delete simulation;

	return fitness;
}

double example_func(double ind[])
{
	double fitness = 0.0;

	for (int i = 0; i < 3; i++)
	{
		fitness += ind[i];
	}
	return fitness;
}
