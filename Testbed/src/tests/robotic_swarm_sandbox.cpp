/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include <iostream>
#include "../test.h"

class RoboticSwarmSandbox: public Test
{
public:

	RoboticSwarmSandbox()
	{
		m_world->SetGravity(b2Vec2(0.0f, 0.0f));
		m_world->SetContactListener(this);
		m_simulation = new srbSimulationSandbox(&m_simSettings);
//    m_simManager = new srbEvaluationTest;
//    m_world->SetContactListener(m_simManager);
//    m_simManager->SetSimulation(m_simulation);
	}

	void Step(Settings &settings) override
	{
		if (m_stepCount == 0)
		{
			//reset camera
			g_camera.m_center = b2Vec2(0.0f, 0.0f);
			g_camera.m_zoom = 1.5f;
		}
		//run the default physics and rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Timestep : %d", m_stepCount);
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new RoboticSwarmSandbox;
	}
};

static int testIndex = RegisterTest("SwarmRoBox2D", "Sandbox",
		RoboticSwarmSandbox::Create);
