/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_COMPONENT_SRB_COMPASS_HPP_
#define OBJECT_COMPONENT_SRB_COMPASS_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbCompassConf;

class srbCompass: public srbComponent
{
public:

	srbCompass(srbCompassConf *conf, srbObject *object);
	~srbCompass()
	{
	}

	void Update();

protected:

	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float noiseLevel;
};

struct srbCompassConf: srbComponentConf
{
	srbCompassConf()
	{
		randomTools = nullptr;
		isNoiseAdded = false;
		noiseLevel = 0.0f;
	}

	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float noiseLevel;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbCompass((srbCompassConf*) conf, object);
	}
};

#endif /* OBJECT_COMPONENT_SRB_COMPASS_HPP_ */
