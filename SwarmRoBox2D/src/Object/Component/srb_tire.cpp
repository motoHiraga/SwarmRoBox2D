/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_tire.hpp"

srbTire::srbTire(srbTireConf *conf, srbObject *object) :
		srbComponent(conf, object)
{
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = m_parentMainBody->GetWorldPoint(conf->position);
	bd.angle = m_parentMainBody->GetAngle() + conf->angle;

	m_body = m_object->GetSimulation()->GetWorld()->CreateBody(&bd);

	b2FixtureDef fd;
	fd.userData.pointer = conf->m_componentFixtureType;
	fd.shape = &conf->p_shape;
	fd.friction = conf->friction;
	fd.density = conf->density;
	fd.restitution = conf->restitution;

	m_body->CreateFixture(&fd);

	b2RevoluteJointDef rjd;
	rjd.Initialize(m_body, m_parentMainBody,
			m_body->GetWorldPoint(conf->anchor));
	rjd.enableLimit = true;
	rjd.lowerAngle = conf->lowerAngle;
	rjd.upperAngle = conf->upperAngle;

	m_object->GetSimulation()->GetWorld()->CreateJoint(&rjd);

	maxSpeed = conf->maxSpeed;
	maxDriveForce = conf->maxDriveForce;
	forceScale = conf->forceScale;
	lateralFriction = conf->lateralFriction;

	float gravity = 10.0f;
	float weight = m_object->GetMass();
	maxFriction = weight * gravity * forceScale;
	maxLateralImpulse = maxFriction * lateralFriction
			* m_object->GetSimulation()->GetTimeStep();

	noiseBias = 0.0f;
	randomTools = conf->randomTools;
	isNoiseAdded = conf->isNoiseAdded;
	noiseBiasAvg = conf->noiseBiasAvg;
	noiseBiasStd = conf->noiseBiasStd;
	noiseFactorAvg = conf->noiseFactorAvg;
	noiseFactorStd = conf->noiseFactorStd;

	if (isNoiseAdded)
	{
		noiseBias = randomTools->GetGaussf(noiseBiasAvg, noiseBiasStd);
	}
}

srbTire::~srbTire()
{
	m_object->GetSimulation()->GetWorld()->DestroyBody(m_body);
}

void srbTire::UpdateFriction()
{
	//lateral linear velocity
	b2Vec2 lateralImpulse = m_body->GetMass() * -GetLateralVelocity();
	if (lateralImpulse.Length() > maxLateralImpulse)
		lateralImpulse *= maxLateralImpulse / lateralImpulse.Length();
	m_body->ApplyLinearImpulseToCenter(forceScale * lateralImpulse, true);

	//angular velocity
	m_body->ApplyAngularImpulse(
			forceScale * 0.1f * m_body->GetInertia()
					* -m_body->GetAngularVelocity(), true);

	//forward linear velocity
	b2Vec2 currentForwardNormal = GetForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -2 * currentForwardSpeed;
	m_body->ApplyForceToCenter(
			forceScale * dragForceMagnitude * currentForwardNormal, true);
}

void srbTire::UpdateDrive(float motorOutput)
{
	//find desired speed
	float desiredSpeed;
	if (isNoiseAdded)
	{
		desiredSpeed = randomTools->GetGaussf(noiseFactorAvg, noiseFactorStd)
				* (motorOutput + noiseBias) * maxSpeed;
	}
	else
	{
		desiredSpeed = motorOutput * maxSpeed;
	}

	//find current speed in forward direction
	b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

	//apply necessary force
	float force = 0;
	if (desiredSpeed > currentSpeed)
		force = maxDriveForce;
	else if (desiredSpeed < currentSpeed)
		force = -maxDriveForce;
	else
		return;
	m_body->ApplyForceToCenter(forceScale * force * currentForwardNormal, true);
}

void srbTire::Update()
{
	float output_value = io_buffer->back();
	io_buffer->pop_back();

	UpdateFriction();
	UpdateDrive(output_value);
}

void srbTire::Refresh()
{
	float weight = m_object->GetMass();

	maxFriction = weight * 10.0f * forceScale;
	maxLateralImpulse = maxFriction * lateralFriction
			* m_object->GetSimulation()->GetTimeStep();
}
