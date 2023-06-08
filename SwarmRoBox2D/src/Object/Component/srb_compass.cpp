/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_compass.hpp"

srbCompass::srbCompass(srbCompassConf *conf, srbObject *object) :
		srbComponent(conf, object)
{
	randomTools = conf->randomTools;
	isNoiseAdded = conf->isNoiseAdded;
	noiseLevel = conf->noiseLevel;
}

void srbCompass::Update()
{
	float angle = m_parentMainBody->GetAngle();
	if (isNoiseAdded)
	{
		angle += randomTools->GetUnif(-noiseLevel, noiseLevel);
	}
	io_buffer->push_back(cosf(angle) * 0.5f + 0.5f);
	io_buffer->push_back(sinf(angle) * 0.5f + 0.5f);
}
