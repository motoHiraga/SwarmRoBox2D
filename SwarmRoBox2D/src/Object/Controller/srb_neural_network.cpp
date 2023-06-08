/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_neural_network.hpp"

srbNeuralNetwork::srbNeuralNetwork(srbNeuralNetworkConf *conf,
		srbObject *object) :
		srbComponent(conf, object)
{
	params = nullptr;
	network_time_step = 0;
	robot_id = 0;
}

void srbNeuralNetwork::SetNetworkParams(srbNetworkParams *params)
{
	this->params = params;

	for (int32 i = 0; i < params->inNodeCount; i++)
	{
		inValues[i] = 0.0f;
	}

	for (int32 i = 0; i < params->hidNodeCount; i++)
	{
		hidValues[i] = 0.0f;
		hidValues_prev[i] = 0.0f;
	}

	for (int32 i = 0; i < params->outNodeCount; i++)
	{
		outValues[i] = 0.0f;
	}

	/// Set weight values.
	for (int i = 0; i < params->inNodeCount; i++)
	{
		for (int j = 0; j < params->hidNodeCount; j++)
		{
			this->params->weightInHid[i][j] = params->weights[i
					* params->hidNodeCount + j];
		}
	}

	for (int i = 0; i < params->hidNodeCount; i++)
	{
		for (int j = 0; j < params->hidNodeCount; j++)
		{
			this->params->weightHidHid[i][j] = params->weights[i
					* params->hidNodeCount + j
					+ params->inNodeCount * params->hidNodeCount];
		}
	}

	for (int i = 0; i < params->hidNodeCount; i++)
	{
		for (int j = 0; j < params->outNodeCount; j++)
		{
			this->params->weightHidOut[i][j] = params->weights[i
					* params->outNodeCount + j
					+ params->inNodeCount * params->hidNodeCount
					+ params->hidNodeCount * params->hidNodeCount];
		}
	}

	for (int i = 0; i < params->inNodeCount; i++)
	{
		for (int j = 0; j < params->outNodeCount; j++)
		{
			this->params->weightInOut[i][j] = params->weights[i
					* params->outNodeCount + j
					+ params->inNodeCount * params->hidNodeCount
					+ params->hidNodeCount * params->hidNodeCount
					+ params->hidNodeCount * params->outNodeCount];
		}
	}
}

void srbNeuralNetwork::Update()
{
	/// Get inputs.
	for (int32 i = 0; i < params->inNodeCount; i++)
	{
		inValues[i] = io_buffer->back();
		io_buffer->pop_back();
	}

	/// Calculate outputs for every 20 time steps.
	if ((network_time_step + robot_id) % 20 == 0)
	{

		/// Reserve previous hidden node values.
		for (int32 i = 0; i < params->hidNodeCount; i++)
		{
			hidValues_prev[i] = hidValues[i];
			hidValues[i] = 0.0f;
		}

		/// Initialize output node values.
		for (int32 i = 0; i < params->outNodeCount; i++)
		{
			outValues[i] = 0.0f;
		}

		/// Calculate hidden node values.
		for (int32 i = 0; i < params->hidNodeCount; i++)
		{
			for (int32 j = 0; j < params->inNodeCount; j++)
			{
				hidValues[i] += inValues[j] * params->weightInHid[j][i];
			}

			for (int32 j = 0; j < params->hidNodeCount; j++)
			{
				hidValues[i] += hidValues_prev[j] * params->weightHidHid[j][i];
			}

			hidValues[i] = ActivationFunctionTanh(hidValues[i]);
		}

		/// Calculate output node values.
		for (int32 i = 0; i < params->outNodeCount; i++)
		{
			for (int32 j = 0; j < params->hidNodeCount; j++)
			{
				outValues[i] += hidValues[j] * params->weightHidOut[j][i];
			}

			for (int32 j = 0; j < params->inNodeCount; j++)
			{
				outValues[i] += inValues[j] * params->weightInOut[j][i];
			}

			outValues[i] = ActivationFunctionSigmoid(outValues[i]);

			io_buffer->push_back(outValues[i]);
		}
	}
	else
	{
		/// Push back the same outputs as the previous ones.
		for (int32 i = 0; i < params->outNodeCount; i++)
		{
			io_buffer->push_back(outValues[i]);
		}
	}

	network_time_step++;
}
