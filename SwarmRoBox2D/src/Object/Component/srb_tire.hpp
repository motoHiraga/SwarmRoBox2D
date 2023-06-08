/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */
 
/// Tire for the top-down car physics.
/// See the followings for details.
/// https://www.iforce2d.net/b2dtut/top-down-car
/// https://www.iforce2d.net/src/iforce2d_TopdownCar.h

#ifndef OBJECT_COMPONENT_SRB_TIRE_HPP_
#define OBJECT_COMPONENT_SRB_TIRE_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbTireConf;

class srbTire: public srbComponent
{
public:
	srbTire(srbTireConf *conf, srbObject *object);
	~srbTire();

	void Update();
	void Refresh();

protected:
	b2Vec2 GetLateralVelocity();
	b2Vec2 GetForwardVelocity();

	void UpdateFriction();
	void UpdateDrive(float motorOutput);

	float maxSpeed;
	float maxDriveForce;
	float forceScale;
	float lateralFriction;

	float maxFriction;
	float maxLateralImpulse;

	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float noiseBias;
	float noiseBiasAvg;
	float noiseBiasStd;
	float noiseFactorAvg;
	float noiseFactorStd;
};

struct srbTireConf: public srbComponentConf
{
	srbTireConf()
	{
		p_shape.SetAsBox(0.2f, 0.3f);

		anchor = b2Vec2(0.0f, 0.0f);
		upperAngle = 0.0f;
		lowerAngle = 0.0f;

		density = 1.0f;
		friction = 0.1f;
		restitution = 0.3f;

		maxSpeed = 2.4f;
		maxDriveForce = 5.0f;
		forceScale = 1.0f;
		lateralFriction = 10.0f;

		m_componentFixtureType = 0;

		randomTools = nullptr;
		isNoiseAdded = false;
		noiseBiasAvg = 0.0f;
		noiseBiasStd = 0.05f;
		noiseFactorAvg = 1.0f;
		noiseFactorStd = 0.0f;
	}

	b2PolygonShape p_shape;

	/// Parameters for b2RevoluteJoint.
	b2Vec2 anchor;
	float upperAngle;
	float lowerAngle;

	/// Parameters for b2Fixture.
	float density;
	float friction;
	float restitution;

	/// Parameters for the tire.
	float maxSpeed;
	float maxDriveForce;
	float forceScale;
	float lateralFriction;

	/// Parameters for generating noise.
	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float noiseBiasAvg;
	float noiseBiasStd;
	float noiseFactorAvg;
	float noiseFactorStd;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbTire((srbTireConf*) conf, object);
	}
};

inline b2Vec2 srbTire::GetLateralVelocity()
{
	b2Vec2 currentRightNormal = m_body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, m_body->GetLinearVelocity())
			* currentRightNormal;
}

inline b2Vec2 srbTire::GetForwardVelocity()
{
	b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, m_body->GetLinearVelocity())
			* currentForwardNormal;
}

#endif /* OBJECT_COMPONENT_SRB_TIRE_HPP_ */
