/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_object.hpp"

srbObject::srbObject(srbObjectConf *conf, srbSimulation *simulation)
{
	m_simulation = simulation;
	worldPosition = conf->position;
	worldAngle = conf->angle;
	m_mainBody = nullptr;
	m_componentList = nullptr;
	m_prev = nullptr;
	m_next = nullptr;
}

srbObject::~srbObject()
{
	/// Destroy all components.
	srbComponent *cp = m_componentList;
	while (cp)
	{
		srbComponent *t = cp;
		cp = cp->m_next;
		delete t;
	}
}

void srbObject::Update()
{
	srbComponent *cp = m_componentList;
	while (cp)
	{
		cp->Update();
		cp = cp->m_next;
	}
}

void srbObject::Refresh()
{
	srbComponent *cp = m_componentList;
	while (cp)
	{
		cp->Refresh();
		cp = cp->m_next;
	}
}

srbComponent* srbObject::CreateComponent(srbComponentConf *conf)
{
	srbComponent *component = conf->createFcn(conf, this);
	component->m_prev = nullptr;
	component->m_next = m_componentList;
	if (m_componentList)
	{
		m_componentList->m_prev = component;
	}
	m_componentList = component;

	Refresh();

	return component;
}

void srbObject::DestroyComponent(srbComponent *component)
{
	if (component->m_prev)
	{
		component->m_prev->m_next = component->m_next;
	}
	if (component->m_next)
	{
		component->m_next->m_prev = component->m_prev;
	}
	if (component == m_componentList)
	{
		m_componentList = component->m_next;
	}

	Refresh();

	delete component;
}

float srbObject::GetMass() const
{
	float weight = 0;
	srbComponent *cp = m_componentList;
	while (cp)
	{
		weight += cp->GetMass();
		cp = cp->m_next;
	}

	return weight;
}

