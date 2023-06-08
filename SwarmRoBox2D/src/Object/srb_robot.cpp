/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_robot.hpp"

#include "../Simulation/srb_simulation_test.hpp"

srbRobot::srbRobot(srbRobotConf *conf, srbSimulation *simulation) :
		srbObject(conf, simulation)
{
	/// Buffer size should be larger than input or output sizes.
	if (srbNetworkParams::maxInNodeCount > srbNetworkParams::maxOutNodeCount)
	{
		m_io_buffer.reserve(srbNetworkParams::maxInNodeCount);
	}
	else
	{
		m_io_buffer.reserve(srbNetworkParams::maxOutNodeCount);
	}

	random_tools = conf->random_tools;

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

		tc.randomTools = random_tools;
		tc.isNoiseAdded = true;

		tc.position.Set(0.75f, 0.0f);
		tire[0] = (srbTire*) CreateComponent(&tc);

		tc.position.Set(-0.75f, 0.0f);
		tire[1] = (srbTire*) CreateComponent(&tc);
	}

	{
		srbNeuralNetworkConf nnc;
		nnc.io_buffer = &m_io_buffer;
		network = (srbNeuralNetwork*) CreateComponent(&nnc);
	}

	{
		srbRayCastSensorConf rcsc;
		rcsc.m_parentMainBody = GetMainBody();
		rcsc.range = conf->ray_cast_range;
		rcsc.io_buffer = &m_io_buffer;

		rcsc.randomTools = random_tools;
		rcsc.noiseType = 1;
		rcsc.noiseLevel = 0.1f;

		/// Set the offset little smaller than the surface to avoid
		/// the starting point of the sensor gets buried into other objects when it collides.
		rcsc.offset = conf->robot_radius * 0.99;

		float angle_interval = b2_pi / 6.0f;

		for (int32 i = 0; i < conf->ray_cast_sensor_count; i++)
		{
			rcsc.angle = angle_interval * i;
			rayCastSensor[i] = (srbRayCastSensor*) CreateComponent(&rcsc);
		}
	}

	{
		srbOmniCameraConf occ;
		occ.range = conf->omni_camera_range;
		occ.partitionCount = conf->omni_camera_partition_count;
		occ.io_buffer = &m_io_buffer;

		occ.randomTools = random_tools;
		occ.isNoiseAdded = true;
		occ.angularNoiseLevel = b2_pi / 180.0f; // plus-minus 1 degree noise

		/// Make sure to assign the corresponding objects in m_simulation by using srbOmniCamera::AddTarget.
		occ.targetObjectCount = ((srbSimulationTest*) m_simulation)->robot_count
				- 1;
		omniCamera[0] = (srbOmniCamera*) CreateComponent(&occ);

		occ.targetObjectCount = ((srbSimulationTest*) m_simulation)->item_count;
		omniCamera[1] = (srbOmniCamera*) CreateComponent(&occ);
	}

	{
		srbCompassConf cc;
		cc.m_parentMainBody = GetMainBody();
		cc.io_buffer = &m_io_buffer;

		cc.randomTools = random_tools;
		cc.isNoiseAdded = true;
		cc.noiseLevel = b2_pi / 180.0f; // plus-minus 1 degree noise

		compass = (srbCompass*) CreateComponent(&cc);
	}
}
