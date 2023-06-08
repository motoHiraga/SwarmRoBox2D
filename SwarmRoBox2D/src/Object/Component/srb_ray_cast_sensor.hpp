/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_COMPONENT_SRB_RAY_CAST_SENSOR_HPP_
#define OBJECT_COMPONENT_SRB_RAY_CAST_SENSOR_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbRayCastSensorConf;

class srbRayCastClosestCallback: public b2RayCastCallback
{
public:
	srbRayCastClosestCallback()
	{
		m_hit = false;
	}

	float ReportFixture(b2Fixture *fixture, const b2Vec2 &point,
			const b2Vec2 &normal, float fraction)
	{
		uintptr_t componentFixtureType = fixture->GetUserData().pointer;

		if (componentFixtureType == 0)
		{
			// By returning -1, we instruct the calling code to ignore this fixture and
			// continue the ray-cast to the next fixture.
			return -1.0f;
		}

		m_hit = true;
		m_point = point;

		// By returning the current fraction, we instruct the calling code to clip the ray and
		// continue the ray-cast to the next fixture. WARNING: do not assume that fixtures
		// are reported in order. However, by clipping, we can always get the closest fixture.
		return fraction;
	}

	bool m_hit;
	b2Vec2 m_point;
};

class srbRayCastSensor: public srbComponent
{
public:

	srbRayCastSensor(srbRayCastSensorConf *conf, srbObject *object);
	~srbRayCastSensor()
	{
	}

	void Update();

protected:

	float range;
	float offset;

	srbRandomTools *randomTools;
	int32 noiseType;
	float noiseLevel;
};

struct srbRayCastSensorConf: public srbComponentConf
{
	srbRayCastSensorConf()
	{
		range = 10.0f;
		offset = 0.0f;

		randomTools = nullptr;
		noiseType = 0;
		noiseLevel = 0.0f;
	}

	float range;

	/// Set the offset little smaller than the surface to avoid
	/// the starting point of the sensor gets buried into other objects when it collides.
	float offset;

	srbRandomTools *randomTools;

	/// noiseType = 0; no sensor noise.
	/// noiseType = 1; add uniform random noise between [-noiseLevel, noiseLevel].
	/// noiseType = 2; add Gaussian noise sampled from noiseLevel * N(0, 1).
	int32 noiseType;
	float noiseLevel;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbRayCastSensor((srbRayCastSensorConf*) conf, object);
	}
};

#endif /* OBJECT_COMPONENT_SRB_RAY_CAST_SENSOR_HPP_ */
