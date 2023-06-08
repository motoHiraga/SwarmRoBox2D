/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_CONTROLLER_SRB_NEURAL_NETWORK_HPP_
#define OBJECT_CONTROLLER_SRB_NEURAL_NETWORK_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbNeuralNetworkConf;

struct srbNetworkParams
{
	srbNetworkParams(int32 in, int32 hid, int32 out)
	{
		inNodeCount = in;
		hidNodeCount = hid;
		outNodeCount = out;
	}

	int32 inNodeCount;
	int32 hidNodeCount;
	int32 outNodeCount;

	/// Maximum number of elements to be reserved.
	static const int32 maxInNodeCount = 30;
	static const int32 maxHidNodeCount = 100;
	static const int32 maxOutNodeCount = 10;

	float weights[maxInNodeCount * maxHidNodeCount
			+ maxHidNodeCount * maxHidNodeCount
			+ maxHidNodeCount * maxOutNodeCount
			+ maxInNodeCount * maxHidNodeCount];
	float weightInHid[maxInNodeCount][maxHidNodeCount];
	float weightHidHid[maxHidNodeCount][maxHidNodeCount];
	float weightHidOut[maxHidNodeCount][maxOutNodeCount];
	float weightInOut[maxInNodeCount][maxOutNodeCount];
};

class srbNeuralNetwork: public srbComponent
{
public:

	srbNeuralNetwork(srbNeuralNetworkConf *conf, srbObject *object);
	~srbNeuralNetwork()
	{
	}

	void Update();

	void SetNetworkParams(srbNetworkParams *params);
	void SetRobotID(int32 id);

	float ActivationFunctionSigmoid(float sum);
	float ActivationFunctionTanh(float sum);

protected:

	srbNetworkParams *params;

	int32 network_time_step;
	int32 robot_id;

	float inValues[srbNetworkParams::maxInNodeCount];
	float hidValues[srbNetworkParams::maxHidNodeCount];
	float hidValues_prev[srbNetworkParams::maxHidNodeCount];
	float outValues[srbNetworkParams::maxOutNodeCount];
};

struct srbNeuralNetworkConf: srbComponentConf
{
	srbNeuralNetworkConf()
	{
	}

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbNeuralNetwork((srbNeuralNetworkConf*) conf, object);
	}
};

inline void srbNeuralNetwork::SetRobotID(int32 id)
{
	robot_id = id;
}

inline float srbNeuralNetwork::ActivationFunctionSigmoid(float sum)
{
	return 1.0f / (1.0f + expf(-sum));
}

inline float srbNeuralNetwork::ActivationFunctionTanh(float sum)
{
	return tanhf(sum);
}

#endif /* OBJECT_CONTROLLER_SRB_NEURAL_NETWORK_HPP_ */
