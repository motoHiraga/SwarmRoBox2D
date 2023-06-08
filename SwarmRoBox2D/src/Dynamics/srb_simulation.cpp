/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_simulation.hpp"

srbSimulation::srbSimulation(srbSettings *settings)
{
	/// Create new b2World if it does not exist.
	if (settings->world == nullptr)
	{
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		m_world = new b2World(gravity);
	}
	else
	{
		m_world = settings->world;
	}

	m_stepCount = 0;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);
	m_groundBody = m_world->CreateBody(&bodyDef);

	renderMode = settings->renderMode;

	timeStep = settings->timeStep;
	velocityIterations = settings->velocityIterations;
	positionIterations = settings->positionIterations;
	userData = settings->userData;

	maxStepCount = settings->maxStepCount;

	m_objectList = nullptr;
}

srbSimulation::~srbSimulation()
{
	srbObject *op = m_objectList;
	while (op)
	{
		srbObject *o = op;
		op = op->m_next;
		delete o;
	}

	// By deleting the world, we delete the bomb, mouse joint, etc.
	delete m_world;
	m_world = nullptr;
}

void srbSimulation::Step()
{
	srbObject *op = m_objectList;
	while (op)
	{
		op->Update();
		op = op->m_next;
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

void srbSimulation::Refresh()
{
	srbObject *op = m_objectList;
	while (op)
	{
		op->Refresh();
		op = op->m_next;
	}
}

const void* srbSimulation::Run(srbManager *manager)
{
	if (manager)
	{
		manager->SetSimulation(this);
	}

	// Allow manager to track contacts
	m_world->SetContactListener(manager);

	if (manager)
	{
		manager->EvaluateInit();
	}

	while (m_stepCount < maxStepCount)
	{
		Step();

		if (manager)
		{
			manager->EvaluateStep();
		}
	}

	if (manager)
	{
		manager->EvaluateEnd();
	}

	if (manager)
	{
		return manager->EvaluationReport();
	}
	else
	{
		return nullptr;
	}
}

srbObject* srbSimulation::CreateObject(srbObjectConf *conf)
{
	// Create a new object
	srbObject *object = conf->createFcn(conf, this);

	// Set relationships
	object->m_prev = nullptr;
	object->m_next = m_objectList;
	if (m_objectList)
	{
		m_objectList->m_prev = object;
	}
	m_objectList = object;

	return object;
}

void srbSimulation::DestroyObject(srbObject *object)
{
	// Set relationships
	if (object->m_prev)
	{
		object->m_prev->m_next = object->m_next;
	}
	if (object->m_next)
	{
		object->m_next->m_prev = object->m_prev;
	}
	if (object == m_objectList)
	{
		m_objectList = object->m_next;
	}

	// Destroy the object
	delete object;
}
