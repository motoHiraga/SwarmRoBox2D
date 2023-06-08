/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_robot_sandbox.hpp"

srbRobotSB::srbRobotSB(srbRobotSBConf *conf, srbSimulation *simulation) :
		srbObject(conf, simulation)
{
	/// Buffer size should be larger than input or output sizes.
	m_io_buffer.reserve(50);

	{
		srbMainBodyConf mbc;
		b2CircleShape shape;
		mbc.m_componentFixtureType = 1;
		mbc.shape = &shape;
		mbc.density = 0.5f;
		mbc.friction = 0.7f;
		mbc.circleShape.m_radius = conf->robot_radius;
		mainBody = (srbMainBody*) CreateComponent(&mbc);
	}

	{
		srbTireConf tc;
		tc.m_componentFixtureType = 0;
		tc.m_parentMainBody = GetMainBody();
		tc.io_buffer = &m_io_buffer;

		tc.position.Set(0.75f, 0.0f);
		tire[0] = (srbTire*) CreateComponent(&tc);

		tc.position.Set(-0.75f, 0.0f);
		tire[1] = (srbTire*) CreateComponent(&tc);
	}
}

