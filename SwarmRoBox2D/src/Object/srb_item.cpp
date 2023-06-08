/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_item.hpp"

srbItem::srbItem(srbItemConf *conf, srbSimulation *simulation) :
		srbObject(conf, simulation)
{
//	b2PolygonShape shape;
//	def->mainBodyDef.shape = &shape;
//	def->mainBodyDef.polygonShape.SetAsBox(2.0f, 3.0f);

//	b2CircleShape shape;
//	def->mainBodyDef.shape = &shape;
//	def->mainBodyDef.circleShape.m_radius = 1.0f;

	item = (srbMainBody*) CreateComponent(&conf->mainBodyConf);
}

