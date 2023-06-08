/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include <iostream>

#include "srb_simulation_sandbox.hpp"

srbSimulationSandbox::srbSimulationSandbox(srbSettings *settings) :
		srbSimulation(settings)
{
	{
		srbArenaConf ac;
		arena = (srbArena*) CreateObject(&ac);
	}

	{
		b2CircleShape shape;
		srbItemConf ic;
		ic.mainBodyConf.shape = &shape;
		ic.mainBodyConf.circleShape.m_radius = 2.0f;
		ic.position.Set(10.0f, 10.0f);
		item[0] = (srbItem*) CreateObject(&ic);
	}

	{
		b2PolygonShape shape;
		srbItemConf ic;
		ic.mainBodyConf.shape = &shape;
		ic.mainBodyConf.polygonShape.SetAsBox(2.0f, 3.0f);
		ic.position.Set(-10.0f, 10.0f);
		ic.angle = b2_pi / 4.0f;
		item[1] = (srbItem*) CreateObject(&ic);
	}

	{
		srbRobotSBConf rc;
		rc.position.Set(0.0f, 0.0f);
		robot[0] = (srbRobotSB*) CreateObject(&rc);

		rc.position.Set(0.0f, -4.0f);
		robot[1] = (srbRobotSB*) CreateObject(&rc);
	}

	{
		b2PolygonShape shape;
		shape.SetAsBox(1.5f, 1.5f);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(10.0f, 4.0f);
		object[0] = m_world->CreateBody(&bd);
		object[0]->CreateFixture(&shape, 1.0f);
	}

	{
		b2PolygonShape shape;
		shape.SetAsBox(1.5f, 1.5f);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(-10.0f, 4.0f);

		object[1] = m_world->CreateBody(&bd);
		object[1]->CreateFixture(&shape, 1.0f);
		object[1]->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
	}
}

b2Vec2 tmp_r0 = b2Vec2(0.0f, 0.0f);

/*
 *  Default srbSimulation::Step() will execute srbObject::Update()
 *  for all srbObject generated with srbSimulation::CreateObject().
 *
 *  srbObject::Update() will execute srbComponent::Update()
 *  for all srbComponent within the srbObject.
 *
 *  Use the following to set manual actions.
 */
void srbSimulationSandbox::Step()
{
	object[0]->ApplyForceToCenter(b2Vec2(0.0f, -10.0f), true);
	object[1]->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -10.0f), true);

	for (int32 i = 0; i < 2; i++)
	{
		/// Push back outputs for tires.
		for (int32 j = 0; j < 2; j++)
		{
			robot[i]->GetIOBuffer()->push_back(1.0f);
		}

		/// Execute robot actions.
		robot[i]->Update();
	}

	/// Testing the speed of the robot.
	if (m_stepCount % 60 == 0)
	{
		b2Vec2 dist = tmp_r0 - robot[0]->GetPosition();
		std::cout << dist.Length() << std::endl;
		tmp_r0 = robot[0]->GetPosition();
	}

	if (!renderMode)
	{
		m_world->Step(timeStep, velocityIterations, positionIterations);
	}

	if (timeStep > 0.0f)
	{
		++m_stepCount;
	}
}

