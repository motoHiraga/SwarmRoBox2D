/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */
 
#include "srb_mainbody.hpp"

srbMainBody::srbMainBody(srbMainBodyConf *conf, srbObject *object) :
		srbComponent(conf, object)
{
	b2BodyDef bd;
	bd.position = m_object->GetWorldPosition();
	bd.angle = m_object->GetWorldAngle();

	if (conf->isStatic)
	{
		bd.type = b2_staticBody;
	}
	else
	{
		bd.type = b2_dynamicBody;
	}

	m_body = m_object->GetSimulation()->GetWorld()->CreateBody(&bd);

	b2FixtureDef fd;
	fd.userData.pointer = conf->m_componentFixtureType;

	shape = nullptr;
	/// e_circle = 0, e_edge = 1, e_polygon = 2, e_chain = 3, e_typeCount = 4
	switch (conf->shape->GetType())
	{
	case 0:
		fd.shape = &conf->circleShape;
		break;
	case 1:
		fd.shape = &conf->edgeShape;
		break;
	case 2:
		fd.shape = &conf->polygonShape;
		break;
	case 3:
		fd.shape = &conf->chainShape;
		break;
	default:
		break;
	}

	fd.density = conf->density;
	fd.friction = conf->friction;
	fd.restitution = conf->restitution;

	if (conf->isTouchable == false)
	{
		fd.filter.maskBits = 0x0000;
	}

	m_body->CreateFixture(&fd);

	if (conf->isGroundFricition)
	{
		float gravity = 10.0f;

		/// For a circle: I = 0.5 * m * r * r ==> r = sqrt(2 * I / m)
		float radius = b2Sqrt(2.0f * m_body->GetInertia() / m_body->GetMass());

		b2FrictionJointDef fjd;
		fjd.localAnchorA = m_body->GetLocalCenter();
		fjd.localAnchorB.SetZero();
		fjd.bodyA = m_body;
		fjd.bodyB = m_object->GetSimulation()->GetGroundBody();
		fjd.collideConnected = true;
		fjd.maxForce = m_body->GetMass() * gravity;
		fjd.maxTorque = m_body->GetMass() * radius * gravity;

		m_object->GetSimulation()->GetWorld()->CreateJoint(&fjd);
	}

	m_object->SetMainBody(m_body);
}

srbMainBody::~srbMainBody()
{
	m_object->GetSimulation()->GetWorld()->DestroyBody(m_body);
}
