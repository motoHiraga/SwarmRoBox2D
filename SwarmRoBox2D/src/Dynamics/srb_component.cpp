/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_component.hpp"

srbComponent::srbComponent(srbComponentConf *conf, srbObject *object)
{
	m_object = object;
	m_body = nullptr;

	worldPosition = conf->position;
	worldAngle = conf->angle;

	m_componentFixtureType = conf->m_componentFixtureType;

	m_parentMainBody = conf->m_parentMainBody;

	io_buffer = conf->io_buffer;

	m_prev = nullptr;
	m_next = nullptr;
}
