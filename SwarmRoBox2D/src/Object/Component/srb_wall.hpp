/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_COMPONENT_SRB_WALL_HPP_
#define OBJECT_COMPONENT_SRB_WALL_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbWallConf;

class srbWall: public srbComponent
{
public:

	srbWall(srbWallConf *conf, srbObject *object);
	~srbWall();

	void Update()
	{
	}
};

struct srbWallConf: public srbComponentConf
{
	srbWallConf()
	{
		friction = 0.1f;
		density = 0.0f;
		restitution = 0.3f;

		start_point = b2Vec2(0.0f, 0.0f);
		end_point = b2Vec2(0.0f, 0.0f);

		m_componentFixtureType = 9;
	}

	float friction;
	float density;
	float restitution;
	b2Vec2 start_point, end_point;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbWall((srbWallConf*) conf, object);
	}
};

#endif /* OBJECT_COMPONENT_SRB_WALL_HPP_ */
