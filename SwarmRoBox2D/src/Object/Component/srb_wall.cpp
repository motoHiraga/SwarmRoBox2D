/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_wall.hpp"

srbWall::srbWall(srbWallConf *conf, srbObject *object) :
		srbComponent(conf, object)
{
	b2BodyDef bd;
	bd.position.Set(0.0f, 0.0f);

	m_body = m_object->GetSimulation()->GetWorld()->CreateBody(&bd);

	b2EdgeShape shape;
	shape.SetTwoSided(conf->start_point, conf->end_point);

	b2FixtureDef fd;
	fd.userData.pointer = conf->m_componentFixtureType;
	fd.shape = &shape;
	fd.density = conf->density;
	fd.friction = conf->friction;
	fd.restitution = conf->restitution;

	m_body->CreateFixture(&fd);

	m_object->SetMainBody(m_body);
}

srbWall::~srbWall()
{
	m_object->GetSimulation()->GetWorld()->DestroyBody(m_body);
}
