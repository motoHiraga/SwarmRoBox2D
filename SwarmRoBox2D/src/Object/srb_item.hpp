/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_SRB_ITEM_HPP_
#define OBJECT_SRB_ITEM_HPP_

#include "Component/srb_mainbody.hpp"

struct srbItemConf;

class srbItem: public srbObject
{
public:
	srbItem(srbItemConf *conf, srbSimulation *simulation);
	virtual ~srbItem()
	{
	}

	srbMainBody *item;
};

struct srbItemConf: public srbObjectConf
{
	srbItemConf()
	{
		mainBodyConf.shape = nullptr;
		mainBodyConf.density = 0.4f;
		mainBodyConf.isGroundFricition = true;
		mainBodyConf.m_componentFixtureType = 2;
	}

	srbMainBodyConf mainBodyConf;

	srbObject* createFcn(srbObjectConf *conf, srbSimulation *simulation)
	{
		return new srbItem((srbItemConf*) conf, simulation);
	}
};

#endif /* OBJECT_SRB_ITEM_HPP_ */
