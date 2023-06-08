/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include <iostream>
#include "../test.h"
#include "SwarmRoBox2D_drawtools.hpp"

class RoboticSwarmTest: public Test
{
public:

	RoboticSwarmTest()
	{
		static const int32 InNodeCount = 17;
		static const int32 HidNodeCount = 8;
		static const int32 OutNodeCount = 2;
		static const int32 genotypeLength = InNodeCount * HidNodeCount
				+ HidNodeCount * HidNodeCount + HidNodeCount * OutNodeCount
				+ InNodeCount * OutNodeCount;

		srbNetworkParams *params = new srbNetworkParams(InNodeCount,
				HidNodeCount, OutNodeCount);

		float genotype[genotypeLength] = {};

		for (int32 i = 0; i < genotypeLength; i++)
			params->weights[i] = genotype[i];
//			params->weights[i] = RandomFloat();

		int32 seed = 0;

		m_world->SetGravity(b2Vec2(0.0f, 0.0f));

		/// Use this if you want to visualize contracts.
		/// Could not use this together m_simManager.
//		m_world->SetContactListener(this);

		/// Example to run simulations without rendering.
//		srbSettings settings;
//		settings.maxStepCount = 3000;
//		srbManager *evaluation = new srbEvaluationTest;
//		srbSimulation *simulation = new srbSimulationTest(&settings, params,
//				seed);
//		double fitness = *((float*) (simulation->Run(evaluation)));
//		std::cout << fitness << std::endl;
//		delete simulation;
//		delete evaluation;

		m_simSettings.maxStepCount = 3000;

		m_simulation = new srbSimulationTest(&m_simSettings, params, seed);
		m_simManager = new srbEvaluationTest;

		m_world->SetContactListener(m_simManager);
		m_simManager->SetSimulation(m_simulation);

		m_simManager->EvaluateInit();

		fitness_value = 0.0f;
	}

	/// Fitness value to render on the main screen.
	float fitness_value;

	void Step(Settings &settings) override
	{
		if (m_stepCount == 0)
		{
			//reset camera
			g_camera.m_center = b2Vec2(0.0f, 0.0f);
			g_camera.m_zoom = 1.5f;
		}

		float wall_length_x =
				static_cast<srbSimulationTest*>(m_simulation)->arena->wall_length_x;
		float wall_length_y =
				static_cast<srbSimulationTest*>(m_simulation)->arena->wall_length_y;

		DrawRectangle(b2Vec2(0.0, 0.0), 0.0, wall_length_x, wall_length_y,
				b2Color(0.9, 0.9, 0.9, 1.0));

		int32 robot_count =
				static_cast<srbSimulationTest*>(m_simulation)->robot_count;
		int32 item_count =
				static_cast<srbSimulationTest*>(m_simulation)->item_count;

		for (int i = 0; i < item_count; i++)
		{
			g_debugDraw.DrawSolidCircleAlpha(
					static_cast<srbSimulationTest*>(m_simulation)->item[i]->GetPosition(),
					static_cast<srbSimulationTest*>(m_simulation)->item[i]->GetMainBody()->GetFixtureList()->GetShape()->m_radius,
					b2Color(0.2, 0.7, 0.7, 1.0));
		}

		for (int i = 0; i < robot_count; i++)
		{
			g_debugDraw.DrawSolidCircleAlpha(
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetPosition(),
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetMainBody()->GetFixtureList()->GetShape()->m_radius,
					b2Color(0.3, 0.7, 0.3, 1.0));
			g_debugDraw.DrawSolidCircleAlpha(
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetPosition(),
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetMainBody()->GetFixtureList()->GetShape()->m_radius
							* 0.7f, b2Color(0.8, 0.8, 0.8, 1.0));
			DrawTriangle(
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetPosition(),
					static_cast<srbSimulationTest*>(m_simulation)->robot[i]->GetAngle(),
					0.6f, b2Color(0.2, 0.2, 0.2, 1.0));
		}

		//run the default physics and rendering
		Test::Step(settings);

		m_simManager->EvaluateStep();

		if (m_stepCount == m_simSettings.maxStepCount)
		{
			m_simManager->EvaluateEnd();
			fitness_value = *((float*) (m_simManager->EvaluationReport()));
		}

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Timestep : %d", m_stepCount);
		m_textLine += 15;

		if (m_stepCount < m_simSettings.maxStepCount)
		{
			g_debugDraw.DrawString(5, m_textLine, "Fitness : %f (tentative)",
					*((float*) (m_simManager->EvaluationReport())));
			m_textLine += 15;
		}
		else
		{
			g_debugDraw.DrawString(5, m_textLine, "Fitness : %f at timestep %d",
					fitness_value, m_simSettings.maxStepCount);
			m_textLine += 15;
		}

//		std::cout << *((float*) (m_simManager->EvaluationReport())) << "     "
//				<< m_simulation->GetStepCount() << std::endl;

	}

	static Test* Create()
	{
		return new RoboticSwarmTest;
	}
};

static int testIndex = RegisterTest("SwarmRoBox2D", "Test",
		RoboticSwarmTest::Create);
